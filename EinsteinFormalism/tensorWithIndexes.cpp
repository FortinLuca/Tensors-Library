#include "tensorWithIndexes.h"

using namespace TensorIndexes;

namespace TensorIndexes{

    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> inputSpaces, UnknownRankedTensor<T> &inputTensor) : tensor(&inputTensor){
        int sizeInputSpaces = inputSpaces.size();

        if(tensor->getRank() != sizeInputSpaces)
            throw invalid_argument("The rank must corresponds to the number of indexes inserted in input");
        
        for (int i = 0; i < tensor->getRank(); i++){
            spaces[i] = inputSpaces[i];
        }
    }

    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... inputSpaces, UnknownRankedTensor<T> &inputTensor) : TensorWithIndexes<T>::TensorWithIndexes(vector<Index>({inputSpaces...}), inputTensor){

    }

}