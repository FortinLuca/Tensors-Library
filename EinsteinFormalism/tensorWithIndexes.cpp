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


    template <typename T>
    TensorWithIndexes<T> TensorWithIndexes<T>::operator *(TensorWithIndexes<T> tensorWithIndexes) { 
        // creation of support vector of integer "spacesOfThis_int" where the elements are the mapped values of the vector of Index "spacesOfThis"
        // in this way we exploit the vector iterator function find() to make all more readble  
        vector<Index> spacesOfThis = this->getSpaces();
        int sizeOfThis = spacesOfThis.size();
        vector<int> spacesOfThis_int = vector<int>(sizeOfThis);
        for(int i = 0; i<sizeOfThis; i++) {
            spacesOfThis_int[i]=spacesOfThis[i].getSpace();
        }

        // through find() function, we search (and then check) if the dimensional spaces (indexes) as parameters of the first tensor "with indexes" 
        // are included in the ones of the second tensor "with indexes", or viceversa
        vector<int>::iterator it;
        vector<Index> spacesOfInput = tensorWithIndexes.getSpaces();
        int sizeOfInput = spacesOfInput.size();
        for(int i = 0; i<sizeOfInput; i++) {
            int spaceToFind = spacesOfInput[i].getSpace();
            it = find(spacesOfThis_int.begin(), spacesOfThis_int.end(), spaceToFind);
            if (it == spacesOfThis_int.end()) throw invalid_argument("No match between the two tensors'spaces. It's mandatory that the tensor of lower rank has the same identical spaces (i,j,k,etc..) of the greater one");
        }

        //TODO: completare i controlli e tutto il resto delle operazioni

        return *this;

    }

}