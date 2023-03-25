#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>

#include "../Utils/utils.cpp"
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
    RankedTensor<T, n> RankedTensor<T, n>::get(){}


    template <typename T, int n>
    void RankedTensor<T, n>::insertRandomData(){
        int i;

        if(!is_integral<T>::value && !is_floating_point<T>::value)
            throw runtime_error("This type is not managed by the Tensor library"); 

        for (i = 0; i < n_total_elements; i++){
            T rnd = random();
            data.insert(data.begin(), rnd);
        }
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

