#include "UnknownRankedTensor.cpp"


namespace Tensor_Library { 
    // Constructor and methods implementations of the RankedTensor class
    template <typename T, int n>
    RankedTensor<T, n>::RankedTensor(vector<int> args) : UnknownRankedTensor<T>::UnknownRankedTensor(args){
        
        int size = args.size(); 

        // Checking the dimensionality of the tensor corresponds to the number of dimensions' value in input
        if(n != size) 
            throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");

        // Setting the rank equal to n
        this->rank = n;
    }


    template <typename T, int n>
    template <typename... ints>
    RankedTensor<T, n>::RankedTensor(ints...sizes) : RankedTensor<T, n>::RankedTensor(vector<int>({sizes...})){ }
    


    // *****************************************************************************************************************************

    // Methods 

    template <typename T, int n>
    RankedTensor<T, n-1> RankedTensor<T, n>::fix(const int space, const int spaceIndex){

        // Checking the exceptions
        if(getRank() == 0) throw invalid_argument("This method cannot be applied to a trace");
        if(space < 0 || space >= n) throw invalid_argument("The dimensional space must exists and it must be lower than total rank");
        if(spaceIndex < 0) throw invalid_argument("An index cannot be less than zero");
        if(this->sizeDimensions[space] <= spaceIndex) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");

        // Creation of a new SizeDimensions
        vector<int> newSizeDimensions;
        newSizeDimensions.insert(newSizeDimensions.begin(), std::begin(this->sizeDimensions), std::end(this->sizeDimensions));
        newSizeDimensions.erase(newSizeDimensions.begin() + space);

        // Creation of a new tensor to return
        RankedTensor<T, n-1> newTensor(newSizeDimensions);
        
        // Computation of the new tensor's strides
        for(int i=0; i<n; i++){
            if(i < space)
                newTensor.getStrides()[i] = this->strides[i];
            else if(i > space)
                newTensor.getStrides()[i-1] = this->strides[i];
        }

        // Copy of the new strides and the original data in the new tensor
        newTensor.setData(this->data);

        // Computation of the new starting position, initially setted to zero
        newTensor.setInitPosition(newTensor.getInitPosition() + spaceIndex * this->strides[space]); 

        // It returns the new tensor
        return newTensor; 
    }


    template <typename T, int n>
    RankedTensor<T, n-1> RankedTensor<T, n>::fix_copy(const int space, const int spaceIndex){

        // Checking the exceptions
        if(getRank() == 0) throw invalid_argument("This method cannot be applied to a trace");
        if(space < 0 || space >= n) throw invalid_argument("The dimensional space must exists and it must be lower than total rank");
        if(spaceIndex < 0) throw invalid_argument("An index cannot be less than zero");
        if(this->sizeDimensions[space] <= spaceIndex) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");

        // Creation of a new SizeDimensions
        vector<int> newSizeDimensions;
        newSizeDimensions.insert(newSizeDimensions.begin(), std::begin(this->sizeDimensions), std::end(this->sizeDimensions));
        newSizeDimensions.erase(newSizeDimensions.begin() + space);

        // Creation of a new tensor to return
        RankedTensor<T, n-1> newTensor(newSizeDimensions);

        // iterating all and only taking the values according to the fixed index
        int i = 0;
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(this->n_total_elements);
        auto it = getIterator();
        while( it.hasNext() ) {
            T elem = it.next();
            if(it.getIndexes()[space] == spaceIndex) {
                newData->at(i) = elem;
                i++;
            }
        }

        newTensor.setData(newData);

        return newTensor;
    }



    template <typename T, int n>
    RankedTensor<T, 1> RankedTensor<T, n>::flattening(){
        RankedTensor<T, 1> newTensor(get_n_total_elements());
        newTensor.setData(this->data);
        return newTensor;
    }


    template <typename T, int n>
    RankedTensor<T, 1> RankedTensor<T, n>::flattening_copy(){
        RankedTensor<T, 1> newTensor(this->n_total_elements);

        // Creating a new vector with the same elements of the original tensor
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(this->n_total_elements);

        int index = 0;

        // Inserting the elements of the new tensors and managing the case if the tensor is a trace
        if(getRank() == 0)
            newData->at(index) = get();
        else{
            TensorIterator<T> it = getIterator();
            
            while(it.hasNext()) {
                newData->at(index) = it.next();
                index++;
            }
        }

        // Setting into a new tensor the new vector containing data
        newTensor.setData(newData);
        return newTensor;
    }



    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::window(const vector<int> min, const vector<int> max) {
        int min_size = min.size();
        int max_size = max.size();

        // Checking the rank
        if(getRank() == 0) throw invalid_argument("This method cannot be applied to a trace");

        // Checking the input arguments of the function
        if (min_size != n) throw invalid_argument("The number of min indexes inserted are not equal to the number of rank");
        if (max_size != n) throw invalid_argument("The number of max indexes inserted are not equal to the number of rank");
        
        for (int i=0; i<n; i++) {
            if (min[i] > this->sizeDimensions[i]-1 || max[i] > this->sizeDimensions[i]-1) throw invalid_argument("One of the min or max indexes is greater than the relative size dimension");
            if (min[i] < 0 || max[i] < 0) throw invalid_argument("One of the min or max indexes is smaller than zero");
            if (min[i] > max[i]) throw invalid_argument("One of the min indexes can't be greater than the relative max index");
        }

        // New tensor with a pointer to the original tensor. It enables to copy the constructor for creating a new tensor equal to the one passed to the constructor
        RankedTensor<T, n> newTensor(*this);

        // Start to compute attributes of the new tensor
        newTensor.n_total_elements = 1;
        newTensor.init_position = 0;

        // Index for strides that start to the last element
        int j = n-1;

        // From 0 to n-1, exactly like "j" that goes to other way from n-1 to 0
        for (int i = 0; i < n; i++) {
            newTensor.sizeDimensions[i] = max[i] - min[i] + 1;
            newTensor.n_total_elements *= newTensor.sizeDimensions[j];
            newTensor.init_position += this->strides[j] * min[i];
            j--;
        }

        // the data is the same of the original tensor 
        newTensor.setData(this->data);

        return newTensor;
    }


    template <typename T, int n>
    RankedTensor<T, n> RankedTensor<T, n>::window_copy(const vector<int> min, const vector<int> max) {
        int min_size = min.size();
        int max_size = max.size();

        // Checking the rank
        if(getRank() == 0) throw invalid_argument("This method cannot be applied to a trace");

        // Checking the input arguments of the function
        if (min_size != n) throw invalid_argument("The number of min indexes inserted are not equal to the number of rank");
        if (max_size != n) throw invalid_argument("The number of max indexes inserted are not equal to the number of rank");
        
        for (int i=0; i<n; i++) {
            if (min[i] > this->sizeDimensions[i]-1 || max[i] > this->sizeDimensions[i]-1) throw invalid_argument("One of the min or max indexes is greater than the relative size dimension");
            if (min[i] < 0 || max[i] < 0) throw invalid_argument("One of the min or max indexes is smaller than zero");
            if (min[i] > max[i]) throw invalid_argument("One of the min indexes can't be greater than the relative max index");
        }

        // Creating a new tensor with the new dimensions
        vector<int> newSizeDimensions(n);
        for(int i = 0; i < n; i++)
            newSizeDimensions[i] = max[i] - min[i] + 1;
            
        RankedTensor<T, n> newTensor(newSizeDimensions);

        // Filling the new tensor with a totally new vector with the same data on the correct window of the original tensor
        TensorIterator<T> it = getIterator();
        bool check_inside_window;
        int index = 0;

        shared_ptr<vector<T>> newData = make_shared<vector<T>>(newTensor.get_n_total_elements());

        // Checking and saving all the elements that are into the given windows by comparing the current indexes with the input limit indexes
        while(it.hasNext()){
            check_inside_window = true;

            for(int i = 0; i < n; i++) {
                if(it.getIndexes()[i] < min[i] || it.getIndexes()[i] > max[i])
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



    //************************************************************************************************************************
    //************************************************************************************************************************

    // Methods for the sum between tensors

}
