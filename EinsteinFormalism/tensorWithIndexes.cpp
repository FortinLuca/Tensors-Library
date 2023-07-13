#include "tensorWithIndexes.h"

namespace TensorIndexes{

    // Constructors
    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> inputSpaces, UnknownRankedTensor<T> &inputTensor) : tensor(&inputTensor){

        // Reserving a portion of memory to the spaces field
        spaces.reserve(tensor->getRank());
        int sizeInputSpaces = inputSpaces.size();

        // Checking if the rank and the dimension of the Index-vector corresponds
        if(tensor->getRank() != sizeInputSpaces) throw invalid_argument("The rank must corresponds to the number of indexes inserted in input");
        
        int sizeOfThis = inputSpaces.size();
        vector<int> inputSpaces_int = vector<int>(sizeOfThis);
        for(int i=0; i<sizeOfThis; i++) {
            inputSpaces_int[i]=inputSpaces[i].getSpace();
        }

        // TODO: portare inputSpaces_int come variabile globale per usufruirne nella funzione operator * ?
        // Checking if in the inputSpaces parameter there are the same space more times
        vector<int>::iterator it;
        for (int i=0; i<sizeOfThis; i++) {
            if (count(inputSpaces_int.begin(), inputSpaces_int.end(), inputSpaces_int[i]) > 1) throw invalid_argument("A tensorWithIndexes can't have two or more identical dimensional spaces (indexes)");
        }

        // Copying into the field all the elements of the input vector
        for (int i=0; i<tensor->getRank(); i++) 
            spaces.push_back(inputSpaces[i]); 

        //multiplierTensor = MultiplierTensor<T>();
    }


    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... inputSpaces, UnknownRankedTensor<T> &inputTensor) : TensorWithIndexes<T>::TensorWithIndexes(vector<Index>({inputSpaces...}), inputTensor){ }


    // Methods
    template <typename T>
    UnknownRankedTensor<T>& TensorWithIndexes<T>::getTensor(){
        return *tensor;
    }


    template <typename T>
    vector<Index> TensorWithIndexes<T>::getSpaces(){
        return spaces;
    }

}