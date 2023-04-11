#include "iterators.h"

using namespace std;

namespace Iterators{
    template <typename T, int n>
    RankedTensorIterator<T, n>::RankedTensorIterator(RankedTensor<T, n> &tensorInput) : tensor(&tensorInput){
        for (int i = 0; i < n; i++) {
            indexes[i] = 0;
            endIndexes[i] = tensor->sizeDimensions[i] - 1;
        }
        
    }

    template <typename T, int n>
    bool RankedTensorIterator<T, n>::hasNext(){

        for(int i = 0; i < n; i++){
            if(indexes[i] < endIndexes[i]){
                return true;
            }
            // Checking if we are above the last element
            else if(indexes[i] > endIndexes[i])
                return false;
        }

        // Checking if we are at the last element
        if(indexes[0] == endIndexes[0])
            return true;

        return false;            
    }


    template <typename T, int n>
    T RankedTensorIterator<T, n>::next(){
        int idx = n-1;
        bool check = false;
        T checkLast = indexes[0];

        vector<int> vectIndexes(begin(indexes), end(indexes));
        T elem = tensor->get(vectIndexes);

        while(!check && idx >= 0){
            if(indexes[idx] == endIndexes[idx]){
                indexes[idx] = 0;
                idx--;
            }
            else{
                indexes[idx]++;
                check = true;
            }
        }

        if(!check)
            indexes[0] = checkLast + 1;

        return elem;
    }


}