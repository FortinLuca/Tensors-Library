#include "tensors.h"


namespace Tensor_Library{

    // Constructor and methods implementations of the UnknownRankedTensor class
    template <typename T>
    UnknownRankedTensor<T>::UnknownRankedTensor(vector<int> args){
        this->rank = args.size();
        sizeDimensions = vector<int>(rank);
        strides = vector<int>(rank);
        
        // Checking that the rank is greater than zero
        if(rank <= 0)
            throw invalid_argument("The rank must be greater than zero");

        n_total_elements = 1;
        init_position = 0;

        for(int i = rank-1; i >= 0; i--){
            // The dimensions' values of the tensor must be greater than 0
            if(args[i] <= 0)
                throw invalid_argument("A dimensional space cannot be zero or less");
            else{
                // Computation of the strides and the sizeDimensions
                strides[i] = n_total_elements;

                n_total_elements *= args[i];
                sizeDimensions[i] = args[i];
            }
        }
    }
    

    //*****************************************************************************************************************************

    // Getters and setters

    template <typename T>
    int UnknownRankedTensor<T>::getRank(){
        return rank;
    }

    template <typename T>
    vector<int> UnknownRankedTensor<T>::getSizeDimensions(){
        return sizeDimensions;
    }


    template <typename T>
    vector<int> UnknownRankedTensor<T>::getStrides(){
        return strides;
    }

    template <typename T>
    shared_ptr<vector<T>> UnknownRankedTensor<T>::getData(){
        return data;
    }

    template <typename T>
    void UnknownRankedTensor<T>::setData(shared_ptr<vector<T>> newData){
        data = newData;
    }

    template <typename T>
    int UnknownRankedTensor<T>::getInitPosition(){
        return init_position;
    }

    template <typename T>
    void UnknownRankedTensor<T>::setInitPosition(int i){
        init_position = i;
    }

    template <typename T>
    int UnknownRankedTensor<T>::get_n_total_elements() {
        return n_total_elements;
    }

    //******************************************************************************************************************************

    // Methods

    template <typename T>
    T UnknownRankedTensor<T>::get(vector<int> tensorIndexes){
        int index = init_position;
        int i = 0;
        int size_index = tensorIndexes.size();

        if(size_index != rank) throw invalid_argument("The number of indexes' dimensions inserted are not equal to the number of rank");

        //check of the association of tensor index provided and corrispective dimension vector
        for (int tensorIndex : tensorIndexes) {
            if (sizeDimensions[i] <= tensorIndex ) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");
            if (tensorIndex < 0) throw invalid_argument("An index cannot be less than zero");
            i++;
        }

        // Computation of the index of the vector from which we take the value provided
        for(int i=0; i<rank; i++)
            index += strides[i] * tensorIndexes[i];  // Expolitation of the input tensor indexes and the strides concept

        return data->at(index);
    }


    template <typename T>
    template <typename... ints>
    T UnknownRankedTensor<T>::get(ints... tensorIndexes){
        return get(vector<int>({tensorIndexes...}));
    }


    template <typename T>
    T UnknownRankedTensor<T>::operator()(vector<int> tensorIndexes){
        return get(tensorIndexes);
    }


    template <typename T>
    template <typename... ints>
    T UnknownRankedTensor<T>::operator()(ints... tensorIndexes){
        return get(vector<int> ({tensorIndexes...}));
    }



    template <typename T>
    void UnknownRankedTensor<T>::set(T elem, vector<int> tensorIndexes){
        int index = init_position;
        int i = 0;
        int size_indexes = tensorIndexes.size();

        if(size_indexes != rank) throw invalid_argument("The number of indexes' dimensions inserted are not equal to the number of rank");

        // Check of the association of tensor index provided and corrispective dimension vector
        for (int tensorIndex : tensorIndexes) {
            if (sizeDimensions[i] <= tensorIndex ) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");
            if (tensorIndex < 0) throw invalid_argument("An index cannot be less than zero");
            i++;
        }

        // Computation of the index of the vector from which we take the value provided
        for(int i=0; i<rank; i++)
            index += strides[i] * tensorIndexes[i];  // Expolitation of the input tensor indexes and the strides concept

        // Setting the element into the correct position
        data->at(index) = elem;
    }


    template <typename T>
    template <typename... ints>
    void UnknownRankedTensor<T>::set(T elem, ints... tensorIndexes){
        set(elem, vector<int>({tensorIndexes...}));
    }



    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::fix(const int space, const int spaceIndex){
        
        // Checking the exceptions
        if(space < 0 || space >= rank) throw invalid_argument("The dimensional space must exists and it must be lower than total rank");
        if(spaceIndex < 0) throw invalid_argument("An index cannot be less than zero");
        if(sizeDimensions[space] <= spaceIndex) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");

        // Creation of a new SizeDimensions
        vector<int> newSizeDimensions;
        newSizeDimensions.insert(newSizeDimensions.begin(), std::begin(sizeDimensions), std::end(sizeDimensions));
        newSizeDimensions.erase(newSizeDimensions.begin() + space);

        // Creation of a new tensor to return
        UnknownRankedTensor<T> newTensor(newSizeDimensions);
        
        // Computation of the new tensor's strides
        for(int i=0; i<rank; i++){
            if(i < space)
                newTensor.getStrides()[i] = strides[i];
            else if(i > space)
                newTensor.getStrides()[i-1] = strides[i];
        }

        // Copy of the new strides and the original data in the new tensor
        newTensor.setData(data);

        // Computation of the new starting position, initially setted to zero
        newTensor.setInitPosition(newTensor.getInitPosition() + spaceIndex * strides[space]); 

        // It returns the new tensor
        return newTensor;
    }


    
    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::fix_copy(const int space, const int spaceIndex){

        // Checking the exceptions
        if(space < 0 || space >= rank) throw invalid_argument("The dimensional space must exists and it must be lower than total rank");
        if(spaceIndex < 0) throw invalid_argument("An index cannot be less than zero");
        if(sizeDimensions[space] <= spaceIndex) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");

        // Creation of a new SizeDimensions
        vector<int> newSizeDimensions;
        newSizeDimensions.insert(newSizeDimensions.begin(), std::begin(sizeDimensions), std::end(sizeDimensions));
        newSizeDimensions.erase(newSizeDimensions.begin() + space);

        // Creation of a new tensor to return
        UnknownRankedTensor<T> newTensor(newSizeDimensions);

        // iterating all and only taking the values according to the fixed index
        int i = 0;
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);
        auto it = getIterator();
        while( it.hasNext() ) {
            T elem = it.next();
            if(it.indexes[space] == spaceIndex) {
                newData->at(i) = elem;
                i++;
            }
        }

        newTensor.setData(newData);

        return newTensor;
    }



    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::flattening(){
        // It doesn't matter if the rank of the original tensor is 1 because in that case it produces the same tensor with the same instructions
        UnknownRankedTensor<T> newTensor(n_total_elements);
        newTensor.setData(data);
        return newTensor;
    }


    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::flattening_copy(){
        UnknownRankedTensor<T> newTensor(n_total_elements);

        // Creating a new vector with the same elements of the original tensor
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);
        TensorIterator<T> it = getIterator();

        int index = 0;
        while(it.hasNext()) {
            newData->at(index) = it.next();
            index++;
        }

        // Setting into a new tensor the new vector containing data
        newTensor.setData(newData);
        return newTensor;
    }



    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::window(const vector<int> min, const vector<int> max) {
        int min_size = min.size();
        int max_size = max.size();

        if (min_size != rank) throw invalid_argument("The number of min indexes inserted are not equal to the number of rank");
        if (max_size != rank) throw invalid_argument("The number of max indexes inserted are not equal to the number of rank");
        
        for (int i=0; i<rank; i++) {
            if (min[i] > sizeDimensions[i]-1 || max[i]>sizeDimensions[i]-1) throw invalid_argument("One of the min or max indexes is greater than the relative size dimension");
            if (min[i] < 0 || max[i] < 0) throw invalid_argument("One of the min or max indexes is smaller than zero");
            if (min[i] > max[i]) throw invalid_argument("One of the min indexes can't be greater than the relative max index");
        }

        // New tensor with a pointer to the original tensor. It enables to copy the constructor for creating a new tensor equal to the one passed to the constructor
        UnknownRankedTensor<T> newTensor(*this);

        // Start to compute attributes of the new tensor
        newTensor.n_total_elements = 1;
        newTensor.init_position = 0;

        // Index for strides that start to the last element
        int j = rank-1;

        // From 0 to rank-1, exactly like "j" that goes to other way from rank-1 to 0
        for (int i = 0; i < rank; i++) {
            newTensor.sizeDimensions[i] = max[i] - min[i] + 1;
            newTensor.n_total_elements *= newTensor.sizeDimensions[j];
            newTensor.init_position += strides[j] * min[i];
            j--;
        }

        // the data is the same of the original tensor 
        newTensor.setData(data);

        return newTensor;
    }


    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::window_copy(const vector<int> min, const vector<int> max) {
        int min_size = min.size();
        int max_size = max.size();

        if (min_size != rank) throw invalid_argument("The number of min indexes inserted are not equal to the number of rank");
        if (max_size != rank) throw invalid_argument("The number of max indexes inserted are not equal to the number of rank");
        
        for (int i=0; i<rank; i++) {
            if (min[i] > sizeDimensions[i]-1 || max[i]>sizeDimensions[i]-1) throw invalid_argument("One of the min or max indexes is greater than the relative size dimension");
            if (min[i] < 0 || max[i] < 0) throw invalid_argument("One of the min or max indexes is smaller than zero");
            if (min[i] > max[i]) throw invalid_argument("One of the min indexes can't be greater than the relative max index");
        }

        // Creating a new tensor with the new dimensions
        vector<int> newSizeDimensions(rank);
        for(int i = 0; i < rank; i++)
            newSizeDimensions[i] = max[i] - min[i] + 1;
            
        UnknownRankedTensor<T> newTensor(newSizeDimensions);

        // Filling the new tensor with a totally new vector with the same data on the correct window of the original tensor
        TensorIterator<T> it = getIterator();
        bool check_inside_window;
        int index = 0;

        shared_ptr<vector<T>> newData = make_shared<vector<T>>(newTensor.get_n_total_elements());

        // Checking and saving all the elements that are into the given windows by comparing the current indexes with the input limit indexes
        while(it.hasNext()){
            check_inside_window = true;

            for(int i = 0; i < rank; i++) {
                if(it.indexes[i] < min[i] || it.indexes[i] > max[i])
                    check_inside_window = false;
            }

            T elem = it.next();
            if(check_inside_window){
                newData->at(index) = elem;
                index++;
            }
        }

        newTensor.setData(newData);

        return newTensor;
    }



    //***************************************************************************************************************
    // Methods for the iterator
    
    template <typename T>
    TensorIterator<T> UnknownRankedTensor<T>::getIterator(){
        TensorIterator<T> iterator(*this);
        return iterator;
    }


    template <typename T>
    TensorIterator<T> UnknownRankedTensor<T>::getIterator(int excludingSpace, vector<int> inputIndexes){
        TensorIterator<T> iterator(*this, excludingSpace, inputIndexes);
        return iterator;
    }



    //************************************************************************************************************************

    // Methods for testing inserted in the folder Utils



    //************************************************************************************************************************

    // Methods for the sum between tensors

    // Algebraic Sum between tensors
    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::algebraicSum(UnknownRankedTensor<T> tensor){
        // The dimensions of the tensors must be equal
        for (int i = 0; i < rank; i++){
            if(sizeDimensions[i] != tensor.sizeDimensions[i])
                throw invalid_argument("In order to apply the algebraic sum, the dimensions of the two tensors must to be equal");
        }

        // Creating a new data vector pointer
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);

        // Creating the two iterators
        TensorIterator<T> it1 = getIterator();
        TensorIterator<T> it2 = tensor.getIterator();
        int index = 0;

        // Since there are the same dimensions, the iterators iterates in the same number of steps
        while(it1.hasNext() && it2.hasNext()){
            T elem1 = it1.next();
            T elem2 = it2.next();
            newData->at(index) = elem1 + elem2;
            index++;
        }

        // Inserting the new pointer of data and returning the current tensor
        this->setData(newData);
        return *this;
    }


    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::operator+(UnknownRankedTensor<T> tensor){
        return algebraicSum(tensor);
    }


    
    // Algebraic Sum between a tensor and an element
    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::algebraicSum(T elem){
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);
        int index = 0; 
        TensorIterator<T> it = getIterator();

        // Adding the element to every element of the tensor
        while(it.hasNext()){
            newData->at(index) = elem + it.next();
            index++;
        }

        // Inserting the new pointer of data and returning the current tensor
        this->setData(newData);
        return *this;
    }


    template <typename T>
    UnknownRankedTensor<T> UnknownRankedTensor<T>::operator+(T elem){
        return algebraicSum(elem);
    }


    //************************************************************************************************************************

    // Methods for the product between tensors

    // TODO: Product with Einstein Formalism
    
}
