#include "tensorWithIndexes.h"

namespace TensorIndexes{

    // Constructors
    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> inputVectorIndexObjects, UnknownRankedTensor<T> &inputTensor) : tensor(&inputTensor){

        // Reserving a portion of memory to the vectorIndexObjects field
        vectorIndexObjects.reserve(tensor->getRank());
        int sizeInputVectorIndexObjects = inputVectorIndexObjects.size();

        // Checking if the rank and the dimension of the Index-vector corresponds
        if(tensor->getRank() != sizeInputVectorIndexObjects) throw invalid_argument("The rank must corresponds to the number of indexes inserted in input");
        
        int sizeOfThis = inputVectorIndexObjects.size();
        vector<int> inputVectorIndexObjects_int = vector<int>(sizeOfThis);
        for(int i=0; i<sizeOfThis; i++) {
            inputVectorIndexObjects_int[i]=inputVectorIndexObjects[i].getSpace();
        }

        // Checking if in the inputVectorIndexObjects parameter there are the same space more times
        vector<int>::iterator it;
        for (int i=0; i<sizeOfThis; i++) {
            if (count(inputVectorIndexObjects_int.begin(), inputVectorIndexObjects_int.end(), inputVectorIndexObjects_int[i]) > 1) throw invalid_argument("A tensorWithIndexes can't have two or more identical dimensional spaces (indexes)");
        }

        // Copying into the field all the elements of the input vector
        for (int i=0; i<tensor->getRank(); i++) 
            vectorIndexObjects.push_back(inputVectorIndexObjects[i]); 
    }


    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... inputVectorIndexObjects, UnknownRankedTensor<T> &inputTensor) : TensorWithIndexes<T>::TensorWithIndexes(vector<Index>({inputVectorIndexObjects...}), inputTensor){ }


    // Methods
    template <typename T>
    UnknownRankedTensor<T>& TensorWithIndexes<T>::getTensor(){
        return *tensor;
    }


    template <typename T>
    vector<Index> TensorWithIndexes<T>::getVectorIndexObjects(){
        return vectorIndexObjects;
    }

}