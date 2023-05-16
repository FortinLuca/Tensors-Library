#include "multiplierTensor.h"

namespace TensorIndexes{

    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(map<int,int> mapOfSpacesAndDimensionsInput){
        mapOfSpacesAndDimensions = map<int,int> (mapOfSpacesAndDimensionsInput);
    };

    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(){
    };


}