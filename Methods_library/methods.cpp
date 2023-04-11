#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <limits>

#include "../tensor.h"


namespace Tensor_Library{

    // Constructor and methods implementations of the RankedTensor class
    template <typename T, int n>
    RankedTensor<T, n>::RankedTensor(std::vector<int> args){
        int i;

        // Checking the dimensionality of the tensor corresponds to the number of dimensions' value in input
        if(n != args.size()) {
            throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");
        }

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
        int index = 0;
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
            index += strides[i]*tensorIndexes[i];  // Expolitation of the input tensor indexes and the strides concept

        return data->at(index + init_position);
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
    RankedTensor<T, n-1> RankedTensor<T, n>::fix_copy(const int space, const int tensorIndex){
        return 0;
    }

    //***************************************************************************************************************
    // Methods for the iterator
    template <typename T, int n>
    RankedTensorIterator<T, n> RankedTensor<T, n>::getIterator(){
        return RankedTensorIterator<T, n>(*this);
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
    void RankedTensor<T, n>::printTensor(){
        // We exploit the for_each contruct to print the element in the data vector
        //for_each(data.begin(), data.get().end(), [] (T c) {cout << +c << " ";} );
        for (int i = 0; i < n_total_elements; i++) {
            cout << +data->at(i) << " ";
        } 
        cout<<endl<<endl;
    }


    //---------------------------------------------------------------------------------------------------------------------------------
    //*********************************************************************************************************************************
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // Constructor and methods implementations of the UnknownRankedTensor class
    template <typename T>
    UnknownRankedTensor<T>::UnknownRankedTensor(){ }


    template <typename T>
    UnknownRankedTensor<T>::~UnknownRankedTensor(){ }
    
}

