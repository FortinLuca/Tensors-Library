#include "iterators.h"


namespace Iterators{
    template <typename T, int n>
    RankedTensorIterator<T, n>::RankedTensorIterator(RankedTensor<T, n> &tensorInput) : tensor(&tensorInput){
        for (int i = 0; i < n; i++) {
            startIndexes[i] = 0;
            endIndexes[i] = tensor->sizeDimensions[i] - 1;
        }
        
    }

    template <typename T, int n>
    bool RankedTensorIterator<T, n>::hasNext(){
        for(int i = 0; i < n; i++){
            if(indexes[i] < endIndexes[i])
                return true;
        }
        
        return false;            
    }


    template <typename T, int n>
    RankedTensorIterator<T, n>& RankedTensorIterator<T, n>::next(){
        int idx = n-1;

        while(idx >= 0){
            if(indexes[idx] == endIndexes[idx]){
                indexes[idx] = 0;
                idx--;
            }
            else{
                indexes[idx]++;
            }
        }

        return *this;
    }


}