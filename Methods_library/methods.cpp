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


    template <typename T, int n>
    int * RankedTensor<T, n>::getSizeDimensions(){
        return sizeDimensions;
    }


    template <typename T, int n>
    int * RankedTensor<T, n>::getStrides(){
        return strides;
    }


    template <typename T, int n>
    T RankedTensor<T, n>::get(vector<int> tensorIndexes){
        int index = 0;
        int i = 0;

        if(tensorIndexes.size() != n) throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");

        //check of the association of tensor index provided and corrispective dimension vector
        for (int tensorIndex : tensorIndexes) {
            if (sizeDimensions[i] <= tensorIndex ) throw runtime_error("Error in association of tensor index provided to get function and the real dimension of the corrispective vector");
            if (tensorIndex < 0) throw invalid_argument("An index cannot be less than zero");
            i++;
        }

        // Computation of the index of the vector from which we take the value provided
        for(int i=0; i<n; i++)
            index += strides[i]*tensorIndexes[i];  // Expolitation of the input tensor indexes and the strides concept

        return data[index];
    }

    
    template <typename T, int n>
    template<typename... ints>
    T RankedTensor<T, n>::get(ints... tensorIndexes){
        return get(vector<int>({tensorIndexes...}));
    }


    // TODO: implement this
    template <typename T, int n>
    template<typename... ints>
    RankedTensor<T, n-1> RankedTensor<T, n>::fix(const int space, ints... tensorIndexes){
        return 0;
    }

    // TODO: implement this
    template <typename T, int n>
    template <typename... ints>
    RankedTensor<T, n-1> fix_copy(const int space, ints... indexes){
        return 0;
    }
    


    template<typename T, int n>
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

        // Insertion random elements of type T only for arithmetic types (numeric types), otherwise we throw an exception 
        if constexpr(is_arithmetic_v<T>){
            // Inserting always n_total_element elements
            for (i = 0; i < n_total_elements; i++){
                T rnd = randomNumber();
                data.insert(data.begin(), rnd);
            }
        } else throw runtime_error("This type is not managed by the Tensor library"); 
    }


    template <typename T, int n>
    void RankedTensor<T, n>::printTensor(){
        // We exploit the for_each contruct to print the element in the data vector
        for_each(data.begin(), data.end(), [] (T c) {cout << +c << " ";} );
        cout<<endl<<endl;
    }


    //---------------------------------------------------------------------------------
    // Constructor and methods implementations of the UnknownRankedTensor class
    template <typename T>
    UnknownRankedTensor<T>::UnknownRankedTensor(){ }


    template <typename T>
    UnknownRankedTensor<T>::~UnknownRankedTensor(){ }
    
}

