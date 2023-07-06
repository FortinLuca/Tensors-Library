#include "multiplierTensor.h"

namespace TensorIndexes{

    // Constructors
    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfSpacesAndDimensionsInput, map<int, int> mapOfEqualIndexesInput){
        mapOfSpacesAndDimensions = map<int,int> (mapOfSpacesAndDimensionsInput);
        mapOfEqualIndexes = map<int, int> (mapOfEqualIndexesInput);

        factors = vector<TensorWithIndexes<T>>();
        factors.push_back(fact1);
        factors.push_back(fact2);

        n_factors = 2;
    }


    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(MultiplierTensor<T> mt, TensorWithIndexes<T> factor){
        mapOfSpacesAndDimensions = map<int,int> (mt.mapOfSpacesAndDimensions);
        mapOfEqualIndexes = map<int, int> (mt.mapOfEqualIndexes);
        factors = vector<TensorWithIndexes<T>>(mt.factors);
        n_factors = mt.n_factors + 1;
    }



    // Getters and Setters
    template <typename T>
    vector<TensorWithIndexes<T>> MultiplierTensor<T>::getFactors(){
        return factors;
    }


    template <typename T>
    int MultiplierTensor<T>::get_N_factors(){
        return n_factors;
    }


    template <typename T>
    map<int,int> MultiplierTensor<T>::getMapOfSpacesAndDimensions(){
        return mapOfSpacesAndDimensions;
    }

    template <typename T>
    map<int, int> MultiplierTensor<T>::getMapOfEqualIndexes(){
        return mapOfEqualIndexes;
    }


}