#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <limits>

#include "tensors.h"


namespace Tensor_Library{

    // Constructor and methods implementations of the RankedTensor class
    template <typename T, int n>
    RankedTensor<T, n>::RankedTensor(std::vector<int> args){
        int i;

        // Checking the dimensionality of the tensor corresponds to the number of dimensions' value in input
        if(n != args.size()) 
            throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");

        // Checking that the rank is greater than zero
        if(n <= 0)
            throw invalid_argument("The rank must be greater than zero");

        n_total_elements = 1;
        init_position = 0;

        for(i = n-1; i >= 0; i--){
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


    //*************************************************************************************************************************
    //RankedTensor<T, n>& operator=(const RankedTensor<T,n>& rankedTensor) = default;

    template <typename T, int n>
    T RankedTensor<T, n>::operator()(vector<int> tensorIndexes){
        return get(tensorIndexes);
    }

    template <typename T, int n>
    template <typename... ints>
    T RankedTensor<T, n>::operator()(ints... tensorIndexes){
         return get(vector<int> ({tensorIndexes...}));
    }
    //*****************************************************************************************************************************

    // Getters and setters

    template <typename T, int n>
    int * RankedTensor<T, n>::getSizeDimensions(){
        return sizeDimensions;
    }


    template <typename T, int n>
    int * RankedTensor<T, n>::getStrides(){
        return strides;
    }

    template <typename T, int n>
    shared_ptr<vector<T>> RankedTensor<T, n>::getData(){
        return data;
    }

    template <typename T, int n>
    void RankedTensor<T, n>::setData(shared_ptr<vector<T>> newData){
        data = newData;
    }

    template <typename T, int n>
    int RankedTensor<T, n>::getInitPosition(){
        return init_position;
    }

    template <typename T, int n>
    void RankedTensor<T, n>::setInitPosition(int i){
        init_position = i;
    }

    template <typename T, int n>
    int RankedTensor<T, n>::get_n_total_elements() {
        return n_total_elements;
    }

    //******************************************************************************************************************************

    // Methods

    template <typename T, int n>
    T RankedTensor<T, n>::get(vector<int> tensorIndexes){
        int index = init_position;
        int i = 0;

        if(tensorIndexes.size() != n) throw invalid_argument("The number of indexes' dimensions inserted are not equal to the number of rank");

        //check of the association of tensor index provided and corrispective dimension vector
        for (int tensorIndex : tensorIndexes) {
            if (sizeDimensions[i] <= tensorIndex ) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");
            if (tensorIndex < 0) throw invalid_argument("An index cannot be less than zero");
            i++;
        }

        // Computation of the index of the vector from which we take the value provided
        for(int i=0; i<n; i++)
            index += strides[i] * tensorIndexes[i];  // Expolitation of the input tensor indexes and the strides concept

        return data->at(index);
    }


    template <typename T, int n>
    template <typename... ints>
    T RankedTensor<T, n>::get(ints... tensorIndexes){
        return get(vector<int>({tensorIndexes...}));
    }



    template <typename T, int n>
    RankedTensor<T, n-1> RankedTensor<T, n>::fix(const int space, const int spaceIndex){
        
        // Checking the exceptions
        if(space < 0 || space >= n) throw invalid_argument("The dimensional space must exists and it must be lower than total rank");
        if(spaceIndex < 0) throw invalid_argument("An index cannot be less than zero");
        if(sizeDimensions[space] <= spaceIndex) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");

        // Creation of a new SizeDimensions
        vector<int> newSizeDimensions;
        newSizeDimensions.insert(newSizeDimensions.begin(), std::begin(sizeDimensions), std::end(sizeDimensions));
        newSizeDimensions.erase(newSizeDimensions.begin() + space);

        // Creation of a new tensor to return
        RankedTensor<T, n-1> newTensor(newSizeDimensions);
        
        // Computation of the new tensor's strides
        for(int i=0; i<n; i++){
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


    // TODO: implement this
    template <typename T, int n>
    RankedTensor<T, n-1> RankedTensor<T, n>::fix_copy(const int space, const int spaceIndex){
        // Checking the exceptions
        if(space < 0 || space >= n) throw invalid_argument("The dimensional space must exists and it must be lower than total rank");
        if(spaceIndex < 0) throw invalid_argument("An index cannot be less than zero");
        if(sizeDimensions[space] <= spaceIndex) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");

        // Creation of a new SizeDimensions
        vector<int> newSizeDimensions;
        newSizeDimensions.insert(newSizeDimensions.begin(), std::begin(sizeDimensions), std::end(sizeDimensions));
        newSizeDimensions.erase(newSizeDimensions.begin() + space);

        // Creation of a new tensor to return
        RankedTensor<T, n-1> newTensor(newSizeDimensions);

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



    template <typename T, int n>
    RankedTensor<T, 1> RankedTensor<T, n>::flattening(){
        // It doesn't matter if the rank of the original tensor is 1 because in that case it produces the same tensor with the same instructions
        RankedTensor<T, 1> newTensor(n_total_elements);
        newTensor.setData(data);
        return newTensor;
    }

    template <typename T, int n>
    RankedTensor<T, 1> RankedTensor<T, n>::flattening_copy(){
        RankedTensor<T, 1> newTensor(n_total_elements);

        // Creating a new vector with the same elements of the original tensor
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);
        RankedTensorIterator<T, n> it = getIterator();

        int index = 0;
        while(it.hasNext()) {
            newData->at(index) = it.next();
            index++;
        }

        // Setting into a new tensor the new vector containing data
        newTensor.setData(newData);
        return newTensor;
    }



    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::window(const vector<int> min, const vector<int> max) {
        if (min.size() != n) throw invalid_argument("The number of min indexes inserted are not equal to the number of rank");
        if (max.size() != n) throw invalid_argument("The number of max indexes inserted are not equal to the number of rank");
        
        for (int i=0; i<n; i++) {
            if (min[i] > sizeDimensions[i]-1 || max[i]>sizeDimensions[i]-1) throw invalid_argument("One of the min or max indexes is greater than the relative size dimension");
            if (min[i] < 0 || max[i] < 0) throw invalid_argument("One of the min or max indexes is smaller than zero");
            if (min[i] > max[i]) throw invalid_argument("One of the min indexes can't be greater than the relative max index");
        }

        // New tensor with a pointer to the original tensor. It enables to copy the constructor for creating a new tensor equal to the one passed to the constructor
        RankedTensor<T,n> newTensor(*this);

        // Start to compute attributes of the new tensor
        newTensor.n_total_elements = 1;
        newTensor.init_position = 0;

        // Index for strides that start to the last element
        int j = n-1;

        // From 0 to n-1, exactly like "j" that goes to other way from n-1 to 0
        for (int i = 0; i < n; i++) {
            newTensor.sizeDimensions[i] = max[i] - min[i] + 1;
            newTensor.n_total_elements *= newTensor.sizeDimensions[j];
            newTensor.init_position += strides[j] * min[i];
            j--;
        }

        // the data is the same of the original tensor 
        newTensor.setData(data);

        return newTensor;
    }


    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::window_copy(const vector<int> min, const vector<int> max) {
        if (min.size() != n) throw invalid_argument("The number of min indexes inserted are not equal to the number of rank");
        if (max.size() != n) throw invalid_argument("The number of max indexes inserted are not equal to the number of rank");
        
        for (int i=0; i<n; i++) {
            if (min[i] > sizeDimensions[i]-1 || max[i]>sizeDimensions[i]-1) throw invalid_argument("One of the min or max indexes is greater than the relative size dimension");
            if (min[i] < 0 || max[i] < 0) throw invalid_argument("One of the min or max indexes is smaller than zero");
            if (min[i] > max[i]) throw invalid_argument("One of the min indexes can't be greater than the relative max index");
        }

        // Creating a new tensor with the new dimensions
        vector<int> newSizeDimensions(n);
        for(int i = 0; i < n; i++)
            newSizeDimensions[i] = max[i] - min[i] + 1;
            
        RankedTensor<T, n> newTensor(newSizeDimensions);

        // Filling the new tensor with a totally new vector with the same data on the correct window of the original tensor
        RankedTensorIterator<T, n> it = getIterator();
        bool check_inside_window;
        int index = 0;

        shared_ptr<vector<T>> newData = make_shared<vector<T>>(newTensor.get_n_total_elements());

        while(it.hasNext()){
            check_inside_window = true;

            for(int i = 0; i < n; i++) {
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
    
    template <typename T, int n>
    RankedTensorIterator<T, n> RankedTensor<T, n>::getIterator(){
        RankedTensorIterator<T, n> iterator(*this);
        return iterator;
    }

    //************************************************************************************************************************

    // Methods for testing    

    //spostare in utils?
    template <typename T, int n>
    T RankedTensor<T, n>::randomNumber() {

        // Computation of the limits of datatype T
        T from = numeric_limits<T>::lowest();
        T to = numeric_limits<T>::max();

        // Reduction of the range from -1000 to 1000 only for non-char elements (because the maximum char's range is lower)
        if constexpr(!(is_same_v<char, T> || is_same_v<signed char, T> || is_same_v<unsigned char, T>)){
            // There exist situations in which the value is inside the range, so we have to make a check before changing the range
            if(from < -1000) from = -1000;
            if(to > 1000) to = 1000;
        }   

        // Setting a 32-bit pseudo-randomic number generator using the Mersenne algorithm (which we haven't studied)
        // It's better than rand() because it produces random sequence much longer to repeat itself
        mt19937 mt(time(nullptr));

        // Uniformly-distributed integer random number generator that produces non-deterministic random numbers
        random_device rand_dev;

        // Creating a generator which produces pseudo-randomic numbers and we'll use it for the uniform distribution
        mt19937 generator(rand_dev());

        // If the type is integral (int, char, long int, ...), we use the discrete uniform distribution and the generator previously implemented
        if constexpr(is_integral_v<T>){
            uniform_int_distribution<T> distr(from, to);
            return distr(generator);
        }
        // If the type is floating point (float, double, ...), we use the continuous uniform distribution
        else if constexpr(is_floating_point_v<T>){
            uniform_real_distribution<T> distr(from, to);
            return distr(generator);
        }
        // Otherwise we throw an exception because we don't manage this new different type T for this method
        else throw runtime_error("This type is not managed by the Tensor library");
    }


    template <typename T, int n>
    void RankedTensor<T, n>::insertRandomData(){
        int i;
        data = make_shared<vector<T>>(n_total_elements);

        // Insertion random elements of type T only for arithmetic types (numeric types), otherwise we throw an exception 
        if constexpr(is_arithmetic_v<T>){
            // Inserting always n_total_element elements
            for (i = 0; i < n_total_elements; i++){
                T rnd = randomNumber();
                data->at(i) = rnd;
            }
        } else throw runtime_error("This type is not managed by the Tensor library"); 
    }


    template <typename T, int n>
    void RankedTensor<T, n>::printData(){
        auto it = getIterator();
        while(it.hasNext())
            cout<< it.next() << " ";
            
        cout<<endl<<endl;
    }



    template <typename T, int n>
    void RankedTensor<T, n>::printTensor(){
        
        // Printing the dimensions of the tensor
        cout << "Tensor's dimensions: ";
        for(int i = 0; i < n; i++){
            cout << sizeDimensions[i];
            if(i < n-1)
                cout << " x ";
            else 
                cout << endl;
        }
        
        
        // Printing the strides
        cout << "Tensor's strides: ";
        for(int i = 0; i < n; i++){
            cout << strides[i];
            if(i < n-1)
                cout << " x ";
            else 
                cout << endl;
        }

        // Printing the total number of element of the tensor
        cout << "Total number of element of the tensor: " << n_total_elements << endl;

        // Printing the tensor's data
        cout << "Tensor's data: ";
        printData();
        cout << endl;
    }


    //************************************************************************************************************************

    // Methods for operations between tensors
    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::algebraicSum(RankedTensor<T, n> tensor){
        for (int i = 0; i < n; i++){
            if(sizeDimensions[i] != tensor.sizeDimensions[i])
                throw invalid_argument("In order to apply the algebraic sum, the dimensions of the two tensors must to be equal");
        }

        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);

        RankedTensorIterator<T, n> it1 = getIterator();
        RankedTensorIterator<T, n> it2 = tensor.getIterator();
        int index = 0;

        while(it1.hasNext() && it2.hasNext()){
            T elem1 = it1.next();
            T elem2 = it2.next();
            newData->at(index) = elem1 + elem2;
            index++;
        }

        this->setData(newData);
        return *this;
    }

    
    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::algebraicSum(T elem){
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);
        int index = 0; 
        RankedTensorIterator<T, n> it = getIterator();

        while(it.hasNext()){
            newData->at(index) = elem + it.next();
            index++;
        }

        this->setData(newData);
        return *this;
    }


    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::operator+(RankedTensor<T, n> tensor){
        return algebraicSum(tensor);
    }

    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::operator+(T elem){
        return algebraicSum(elem);
    }

    
    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::multiply(RankedTensor<T, n> tensor){
        return NULL;
    }

    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::operator*(RankedTensor<T, n> tensor){
        return multiply(tensor);
    }




    //---------------------------------------------------------------------------------------------------------------------------------
    //*********************************************************************************************************************************
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // Constructor and methods implementations of the UnknownRankedTensor class
    template <typename T>
    UnknownRankedTensor<T>::UnknownRankedTensor(vector<int> args){
        n = args.size();
        
    }
    
}

