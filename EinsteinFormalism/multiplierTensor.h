#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            map<int,int> mapOfDifferentIndexes;      // map of the non-common indexes in which the keys are the spaces of the indexes and the values are the dimensions of the spaces
            map<int, int> mapOfEqualIndexes;         // map of the common indexes in which the keys are the spaces of the indexes and the values are the dimensions of the spaces
            vector<Index> vectorDifferentIndexes;  // vector which contains the indexes of the resulting tensor
            vector<TensorWithIndexes<T>> factors;    // vector which contains the TensorWithIndexes objects that are the factor of the product

            // the attributes of this class can be accessed from the classes Indexes and TensorWithIndexes
            friend class Indexes;                    
            friend class TensorWithIndexes<T>;

            /**
             * @brief 
             * 
             */
            void recursiveProduct(vector<int> sizeTotalIndexes, vector<int> spaceTotalIndexes, size_t index, UnknownRankedTensor<T> resultInput, vector<vector<int>> vectorFactorsIndexes, vector<int> resultIndexes, vector<int> spaceDifferentIndexes);


            /**
             * @brief 
             * 
             * @param resultInput 
             */
            T prod(vector<vector<int>> vectorFactorsIndexes);

        
        public:

            // Constructors
            MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfSpacesAndDimensionsInput, map<int, int> mapOfEqualIndexesInput, vector<Index> vectorDifferentIndexesInput);

            MultiplierTensor(MultiplierTensor<T>& mt);


            // getters and setters
            /**
             * @brief GetFactors method: it extract the factors of the product 
             * 
             * @return vector<TensorWithIndexes<T>> object that contains the tensorWithIndexes arguments of the product
             */
            vector<TensorWithIndexes<T>> getFactors();


            /**
             * @brief getMapOfDifferentIndexes method: it extracts the map of the non-common indexes
             * 
             * @return map<int,int> object which contains the spaces of the non-common indexes and their dimensions
             */
            map<int,int> getMapOfDifferentIndexes();

            /**
             * @brief getMapOfEqualIndexes method: it extracts the map of the common indexes
             * 
             * @return map<int, int> object which contains the spaces of the common indexes and their dimensions
             */
            map<int, int> getMapOfEqualIndexes();

            
            /**
             * @brief getVectorDifferentIndexes method: it extracts the vector of different indexes
             * 
             * @return vector<Index> object which contains all the Index object used for producing the resulting tensorWithIndexes after the product
             */
            vector<Index> getVectorDifferentIndexes();

            /**
             * @brief setMapOfDifferentIndexes method: it sets the map of the different indexes with the input one
             * 
             * @param mapOfDifferentIndexesInput: input map to be set as mapOfDifferentIndexes attribute
             */
            void setMapOfDifferentIndexes(map<int, int> mapOfDifferentIndexesInput);

            /**
             * @brief setMapOfEqualIndexes method: it sets the map of the different indexes with the input one
             * 
             * @param mapOfEqualIndexesInput: input map to be set as mapOfEqualIndexes attribute
             */
            void setMapOfEqualIndexes(map<int, int> mapOfEqualIndexesInput);

            /**
             * @brief setFactors method: it sets the vector containing the factors of the products
             * 
             * @param tensors: a vector of tensorWithIndexes objects that contains the updated factors
             */
            void setFactors(vector<TensorWithIndexes<T>> tensors);

            /**
             * @brief setVectorDifferentIndexes method: it sets the vector of different indexes
             * 
             * @param vectorDifferentIndexesInput: a vector of Index object that contains the updated indexes for the resulting tensor
             */
            void setVectorDifferentIndexes(vector<Index> vectorDifferentIndexesInput);


            // Methods
            TensorWithIndexes<T> applyProduct();
    };

}