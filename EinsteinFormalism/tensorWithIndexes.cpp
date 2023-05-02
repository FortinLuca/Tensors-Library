#include "tensorWithIndexes.h"

namespace TensorIndexes{

    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> inputSpaces, UnknownRankedTensor<T> &inputTensor) : tensor(&inputTensor){

        // Reserving a portion of memory to the spaces field
        spaces.reserve(tensor->getRank());
        int sizeInputSpaces = inputSpaces.size();

        // Checking if the rank and the dimension of the Index-vector corresponds
        if(tensor->getRank() != sizeInputSpaces)
            throw invalid_argument("The rank must corresponds to the number of indexes inserted in input");
        
        // Copying into the field all the elements of the input vector
        for (int i=0; i<tensor->getRank(); i++) 
            spaces.push_back(inputSpaces[i]); 
    }


    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... inputSpaces, UnknownRankedTensor<T> &inputTensor) : TensorWithIndexes<T>::TensorWithIndexes(vector<Index>({inputSpaces...}), inputTensor){

    }



    template <typename T>
    UnknownRankedTensor<T>& TensorWithIndexes<T>::getTensor(){
        return *tensor;
    }


    template <typename T>
    vector<Index> TensorWithIndexes<T>::getSpaces(){
        return spaces;
    }


}