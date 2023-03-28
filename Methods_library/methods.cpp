#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <limits>

#include "../tensor.h"


namespace Tensor_Library{


    template <typename T, int n>
    RankedTensor<T, n>::RankedTensor(std::vector<int> args){
        int i;

        if(n != args.size()) {
            throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");
        }

        n_total_elements = 1;
        for(i = n-1; i >= 0; i--){
            if(args[i] <= 0)
                throw invalid_argument("A dimensional space cannot be zero or less");
            else{
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
    T RankedTensor<T, n>::get(vector<int> indexes){
        int index = 0;

        for(int i=0; i<n; i++)
            index += indexes[i]*strides[i];

        return index;
    }


    template<typename T, int n>
    T RankedTensor<T, n>::randomNumber() {

        T from = numeric_limits<T>::lowest();
        T to = numeric_limits<T>::max();

        if constexpr(!(is_same_v<char, T> || is_same_v<signed char, T> || is_same_v<unsigned char, T>)){
            if(from < -1000) from = -1000;
            if(to > 1000) to = 1000;
        }   

        mt19937 mt(time(nullptr));
        random_device rand_dev;
        mt19937 generator(rand_dev());

        if constexpr(is_integral_v<T>){
            uniform_int_distribution<T> distr(from, to);
            return distr(generator);
        }
        else if constexpr(is_floating_point_v<T>){
            uniform_real_distribution<T> distr(from, to);
            return distr(generator);
        }
        else throw runtime_error("This type is not managed by the Tensor library");
    }


    template <typename T, int n>
    void RankedTensor<T, n>::insertRandomData(){
        int i;

        if constexpr(is_arithmetic_v<T>){
            for (i = 0; i < n_total_elements; i++){
                T rnd = randomNumber();
                data.insert(data.begin(), rnd);
            }
        } else throw runtime_error("This type is not managed by the Tensor library"); 
    }


    template <typename T, int n>
    void RankedTensor<T, n>::printTensor(){
        for_each(data.begin(), data.end(), [] (T c) {cout << +c << " ";} );
        cout<<endl<<endl;
    }


    template <typename T>
    UnknownRankedTensor<T>::UnknownRankedTensor(){ }


    template <typename T>
    UnknownRankedTensor<T>::~UnknownRankedTensor(){ }
    
}

