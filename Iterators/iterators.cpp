#include "iterators.h"


namespace Iterators{
    template <typename T, int n>
    RankedTensorIterator<T, n>::RankedTensorIterator(RankedTensor<T, n> &tensorInput) : tensor(&tensorInput){
        for (int i = 0; i < n; i++) {
            startIndexes[i] = 0;
            endIndexes[i] = tensor->dimensions[i] - 1;
        }
        
    }

    template <typename T, int n>
    bool RankedTensorIterator<T, n>::hasNext(){
        for(int i = 0; i < n; i++)
            if(indexes[i] < endIndexes[i])
                return true;

        return false;            
    }


    template <typename T, int n>
    RankedTensorIterator<T, n>& RankedTensorIterator<T, n>::next(){
        int index = n-1;

        while(i >= 0){
            if(indexes[i] == endIndexes[i]){
                indexes[i] = 0;
                i--;
            }
            else{
                indexes[i]++;
            }
        }

        return *this
    }


}