#include "tensorWithIndexes.h"

namespace TensorIndexes{

    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> inputSpaces){
        int sizeInputSpaces = inputSpaces.size();

        if(rank != sizeInputSpaces)
            throw invalid_argument("The rank must corresponds to the number of indexes inserted in input");
        
        for (int i = 0; i < rank; i++){
            spaces[i] = inputSpaces[i];
        }
    }

    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... inputSpaces) : TensorWithIndexes<T>::TensorWithIndexes({inputSpaces}){

    }

}