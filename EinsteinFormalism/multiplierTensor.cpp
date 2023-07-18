#include "multiplierTensor.h"

namespace TensorIndexes{

    // Constructors
    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfDifferentIndexesInput, map<int, int> mapOfEqualIndexesInput, vector<Index> vectorDifferentIndexesInput){
        
        // Saving the two maps parameters
        mapOfDifferentIndexes = map<int,int> (mapOfDifferentIndexesInput);
        mapOfEqualIndexes = map<int, int> (mapOfEqualIndexesInput);
        vectorDifferentIndexes = vector<Index>(vectorDifferentIndexesInput);

        // Filling the vector with the two TensorWithIndexes factors
        factors = vector<TensorWithIndexes<T>>();
        factors.push_back(fact1);
        factors.push_back(fact2);

        // Initializing an empty prod_result in order to use it to save the result after the method apply_product
        prod_result = UnknownRankedTensor<T>();
    }


    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(MultiplierTensor<T> &mt){
        
        // Saving all the parameters
        mapOfDifferentIndexes = map<int,int> (mt.mapOfDifferentIndexes);
        mapOfEqualIndexes = map<int, int> (mt.mapOfEqualIndexes);
        vectorDifferentIndexes = vector<Index> (mt.vectorDifferentIndexes);
        factors = vector<TensorWithIndexes<T>>(mt.factors);

        // copying the prod_result of the other multiplier tensor
        prod_result = UnknownRankedTensor<T>(mt.prod_result);
    }



    // Getters and Setters
    template <typename T>
    vector<TensorWithIndexes<T>> MultiplierTensor<T>::getFactors(){
        return factors;
    }


    template <typename T>
    map<int,int> MultiplierTensor<T>::getMapOfDifferentIndexes(){
        return mapOfDifferentIndexes;
    }


    template <typename T>
    map<int, int> MultiplierTensor<T>::getMapOfEqualIndexes(){
        return mapOfEqualIndexes;
    }


    template <typename T>
    vector<Index> MultiplierTensor<T>::getVectorDifferentIndexes(){
        return vectorDifferentIndexes;
    }


    template <typename T>
    void MultiplierTensor<T>::setMapOfDifferentIndexes(map<int, int> mapOfDifferentIndexesInput){
        this->mapOfDifferentIndexes = map<int,int> (mapOfDifferentIndexesInput);
    }


    template <typename T>
    void MultiplierTensor<T>::setMapOfEqualIndexes(map<int, int> mapOfEqualIndexesInput){
        this->mapOfEqualIndexes = map<int, int> (mapOfEqualIndexesInput);
    }


    template <typename T>
    void MultiplierTensor<T>::setFactors(vector<TensorWithIndexes<T>> factorsInput){
        this->factors = vector<TensorWithIndexes<T>>(factorsInput);
    }


    template <typename T>
    void MultiplierTensor<T>::setVectorDifferentIndexes(vector<Index> vectorDifferentIndexesInput){
        this->vectorDifferentIndexes = vector<Index> (vectorDifferentIndexesInput);
    }



    // Methods
    template <typename T>
    void MultiplierTensor<T>::recursiveProduct(vector<int> sizeTotalIndexes, vector<int> spaceTotalIndexes, size_t index, UnknownRankedTensor<T> resultInput, vector<vector<int>> vectorFactorsIndexes, vector<int> resultIndexes, vector<int> spaceDifferentIndexes){
        // Base case
        if (index >= sizeTotalIndexes.size()) 
            return;
        
        for (int i = 0; i < sizeTotalIndexes[index]; ++i) {
            
            // Insert indexes into the factors in the right position
            for(int j = 0; j < (int)factors.size(); j++){
                vector<Index> indexes = factors[j].getSpaces();
                for(int z = 0; z < (int)indexes.size(); z++){
                    if(spaceTotalIndexes[index] == indexes[z].getSpace())
                        vectorFactorsIndexes[j][z] = i;
                }               
            }

            // Insert indexes into the result in the right position
            for(int j = 0; j < (int)spaceDifferentIndexes.size(); j++){
                if(spaceDifferentIndexes[j] == spaceTotalIndexes[index])
                    resultIndexes[j] = i;              
            }

            recursiveProduct(sizeTotalIndexes, spaceTotalIndexes, index + 1, resultInput, vectorFactorsIndexes, resultIndexes, spaceDifferentIndexes);

            // Innermost loop
            if (index == sizeTotalIndexes.size() - 1) {
                // Product
                resultInput.set(resultInput(resultIndexes) + prod(vectorFactorsIndexes), resultIndexes);
            }
        }
    }


    template <typename T>
    T MultiplierTensor<T>::prod(vector<vector<int>> vectorFactorsIndexes) {
        // Application of the product part of the Einstein Notation
        T elem = 1;
        for(int i = 0; i < (int) factors.size(); i++){
            elem *= factors[i].getTensor()(vectorFactorsIndexes[i]);
        }

        return elem;
    }


    template <typename T>
    TensorWithIndexes<T> MultiplierTensor<T>::applyProduct(){

        // Obtain all the useful attributes in order to apply the product
        vector<TensorWithIndexes<T>> factors = getFactors();
        //int n_factors = get_N_factors();
        map<int, int> commonIndexes = getMapOfEqualIndexes();
        map<int, int> nonCommonIndexes = getMapOfDifferentIndexes();

        // Extract the sizeDimensions of the common and non-common indexes
        vector<int> sizeDimensionsDifferentIndexes = vector<int> ();
        for(auto it = nonCommonIndexes.cbegin(); it != nonCommonIndexes.cend(); ++it){
            sizeDimensionsDifferentIndexes.push_back(it->second);
        }

        vector<int> sizeDimensionsCommonIndexes = vector<int> ();
        for(auto it = commonIndexes.cbegin(); it != commonIndexes.cend(); ++it){
            sizeDimensionsCommonIndexes.push_back(it->second);
        }

        // Initialize the prod_result tensor. This parameter is useful in order to not lose the UnknownRankedTensor after returning the tensorWithIndexes object because it contains a pointer to the tensor
        // Without the prod_result attribute, the pointer after the method and returning the TensorWithIndexes object would point to a cancelled tensor because, otherwise the tensor it is locally created
        prod_result = UnknownRankedTensor<T>(sizeDimensionsDifferentIndexes);
        
        // Insert zeros into the resulting tensor
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(prod_result.get_n_total_elements());
        for (int i = 0; i < prod_result.get_n_total_elements(); i++)
            newData->at(i) = 0;
        prod_result.setData(newData);


        // Initialize the data structures which will contains the indexes for each tensor
        vector<vector<int>> vectorFactorsIndexes = vector<vector<int>> (factors.size());
        for(int i = 0; i < (int) vectorFactorsIndexes.size(); i++){
            vectorFactorsIndexes[i] = vector<int>(factors[i].getTensor().getSizeDimensions().size());
        }

        vector<int> resultIndexes = vector<int>(prod_result.getSizeDimensions().size());

        map<int, int> totalIndexes = mapOfDifferentIndexes;
        totalIndexes.insert(mapOfEqualIndexes.begin(), mapOfEqualIndexes.end());

        // Divide the map into two vectors that contain respectively the keys and the values 
        vector<int> spaceTotalIndexes, sizeTotalIndexes;
        for(map<int,int>::iterator it = totalIndexes.begin(); it != totalIndexes.end(); ++it) {
            spaceTotalIndexes.push_back(it->first);
            sizeTotalIndexes.push_back(it->second);
        }

        // Save the keys of the mapOfDifferentIndexes into a vector for the function
        vector<int> spaceDifferentIndexes;
        for(map<int,int>::iterator it = mapOfDifferentIndexes.begin(); it != mapOfDifferentIndexes.end(); ++it) {
            spaceDifferentIndexes.push_back(it->first);
        }
        

        // Recurive application of the product between all the factors
        recursiveProduct(sizeTotalIndexes, spaceTotalIndexes, 0, prod_result, vectorFactorsIndexes, resultIndexes, spaceDifferentIndexes);

        // Return the tensorWithIndexes object
        return prod_result(vectorDifferentIndexes);
    }
}