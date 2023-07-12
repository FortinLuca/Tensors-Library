#include "multiplierTensor.h"

namespace TensorIndexes{

    // Constructors
    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfDifferentIndexesInput, map<int, int> mapOfEqualIndexesInput){
        
        // Saving the two maps parameters
        mapOfDifferentIndexes = map<int,int> (mapOfDifferentIndexesInput);
        mapOfEqualIndexes = map<int, int> (mapOfEqualIndexesInput);

        // Filling the vector with the two TensorWithIndexes factors
        factors = vector<TensorWithIndexes<T>>();
        factors.push_back(fact1);
        factors.push_back(fact2);
        n_factors = 2;
    }


    template <typename T>
    MultiplierTensor<T>::MultiplierTensor(MultiplierTensor<T> &mt){
        
        // Saving all the parameters
        mapOfDifferentIndexes = map<int,int> (mt.mapOfDifferentIndexes);
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
    map<int,int> MultiplierTensor<T>::getMapOfDifferentIndexes(){
        return mapOfDifferentIndexes;
    }


    template <typename T>
    map<int, int> MultiplierTensor<T>::getMapOfEqualIndexes(){
        return mapOfEqualIndexes;
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


    // Methods
    template <typename T>
    void MultiplierTensor<T>::looper(map<int, int> totalIndexes, map<int,int>::const_iterator index,  map<int,int>::const_iterator end, map<int,int>::const_iterator secondEnd, UnknownRankedTensor<T> resultInput, vector<vector<int>> vectorFactorsIndexes, vector<int> resultIndexes, size_t counter, size_t sizeUncommonIndexes) {
        if (index == end){
            // cout << i << " - " << index->second << "   " << index->first << endl;
            // test
            for (auto element : resultIndexes) {
                cout << element << " ";
            }
            cout << endl;

            for (auto element : vectorFactorsIndexes) {
                for (auto elem : element)
                    cout << elem << " ";
                cout << endl;
            }
            cout << endl << endl;

            // Product
            resultInput.set(resultInput(resultIndexes) + prod(vectorFactorsIndexes), resultIndexes);
        }
        else{
            for (int i = 0; i<index->second; ++i) {
                
                looper(totalIndexes, ++index, end, secondEnd, resultInput, vectorFactorsIndexes, resultIndexes, counter + 1, sizeUncommonIndexes);

                int space = index->first;           

                // Insert indexes into the factors in the right position
                for(int j = 0; j < (int)factors.size(); j++){
                    vector<Index> indexes = factors[j].getSpaces();
                    for(int z = 0; z < (int)indexes.size(); z++){
                        if(space == indexes[z].getSpace())
                            vectorFactorsIndexes[j][z] = i;
                    }               
                }

                // Insert indexes into the result in the right position
                if(counter < sizeUncommonIndexes){
                    resultIndexes[counter] = i;
                }

                
            
                //if (index == secondEnd) {
                    
                //}
            }
        }
    }


    template <typename T>
    T MultiplierTensor<T>::prod(vector<vector<int>> vectorFactorsIndexes) {
        T elem = 1;
        for(int i = 0; i < (int) factors.size(); i++){
            elem *= factors[i].getTensor()(vectorFactorsIndexes[i]);
        }

        return elem;
    }


    template <typename T>
    //TensorWithIndexes<T> MultiplierTensor<T>::applyProduct(){
    void MultiplierTensor<T>::applyProduct(){

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

        // Create a new tensor in order to compute the resulting tensor
        UnknownRankedTensor<T> result = UnknownRankedTensor<T>(sizeDimensionsDifferentIndexes);
        
        // Insert zeros into the resulting tensor
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(result.get_n_total_elements());
        for (int i = 0; i < result.get_n_total_elements(); i++)
            newData->at(i) = 0;
        result.setData(newData);


        // Initialize the data structures which will contains the indexes for each tensor
        vector<vector<int>> vectorFactorsIndexes = vector<vector<int>> (factors.size());
        for(int i = 0; i < (int) vectorFactorsIndexes.size(); i++){
            vectorFactorsIndexes[i] = vector<int>(factors[i].getTensor().getSizeDimensions().size());
        }

        vector<int> resultIndexes = vector<int>(result.getSizeDimensions().size());

        map<int, int> totalIndexes = mapOfDifferentIndexes;
        totalIndexes.insert(mapOfEqualIndexes.begin(), mapOfEqualIndexes.end());
        

        // Recurive application of the product between all the factors
        looper(totalIndexes, totalIndexes.cbegin(), totalIndexes.cend(), --totalIndexes.cend(), result, vectorFactorsIndexes, resultIndexes, 0, mapOfDifferentIndexes.size());
        result.printTensor();
        /*
        // Multiplying matrix a and b and storing in array mult.
        for(i = 0; i < r1; ++i)
            for(j = 0; j < c2; ++j)
                for(k = 0; k < c1; ++k)
                    mult[i][j] += a[i][k] * b[k][j];
        */

    }


}