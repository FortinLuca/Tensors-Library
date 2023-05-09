#include "multiplierTensor.h"

namespace TensorIndexes{

    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(vector<int> multiplierOperationsInput, vector<int> vectorOfSpacesInput){
        resultMultiplier.assign(multiplierOperationsInput.begin(), multiplierOperationsInput.end());
        vectorOfSpaces.assign(vectorOfSpacesInput.begin(), vectorOfSpacesInput.end());
    };


}