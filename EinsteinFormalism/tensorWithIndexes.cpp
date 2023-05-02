#include "tensorWithIndexes.h"

namespace TensorIndexes{

    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> spaces){

    }

    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... space) : TensorWithIndexes<T>::TensorWithIndexes(vector<Index> spaces){

    }

}