#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            map<int,int> mapOfDifferentIndexes;      // map of the non-common indexes in which the keys are the spaces of the indexes and the values are the dimensions of the spaces
            map<int, int> mapOfEqualIndexes;         // map of the common indexes in which the keys are the spaces of the indexes and the values are the dimensions of the spaces
            vector<Index> vectorDifferentIndexes;    // vector which contains the indexes of the resulting tensor
            vector<TensorWithIndexes<T>> factors;    // vector which contains the TensorWithIndexes objects that are the factor of the product
            UnknownRankedTensor<T> prod_result;      // UnknownRankedTensor which will save the result of the result after invoking the applyProduct method

            // it can access the private or protected fields of the classes Indexes and TensorWithIndexes
            friend class Indexes;                    
            friend class TensorWithIndexes<T>;

            
            /**
             * @brief recursiveProduct method: auxiliary function of the applyProd method. It applies a recursion in order to apply the Einstein's Formalism formula without knowing at compile time how many nested loop use (equal to the number of indexes)
             * 
             * @param sizeTotalIndexes: vector of integers that contain the sizes of the indexes in each factor of the product 
             * @param spaceTotalIndexes: vector of integers that contain the indentifier space integgers of the indexes in each factor of the product 
             * @param index: size_t value used for iterating the sizeTotalIndexes vector and extracting all the elements for applying a series of nested loop for each element into the vector
             * @param resultInput: UnknownRankedTensor object initially setted to zero which eventually will contain the result of the product
             * @param vectorFactorsIndexes: vector of vectors of integer which is initially empty but eventually it contains in the correct order all the iterated indexes for each factor in order to retrieve the correct elements
             * @param resultIndexes: vector of integer which is initially empty but eventually it contains in the correct order all the iterated indexes for each factor in order to retrieve the correct elements
             * @param spaceDifferentIndexes: vector of integers that contains the spaces of the resulting tensor in order to compute correctly the elements of the resultIndexes vector  
             */
            void recursiveProduct(vector<int> sizeTotalIndexes, vector<int> spaceTotalIndexes, size_t index, UnknownRankedTensor<T> resultInput, vector<vector<int>> vectorFactorsIndexes, vector<int> resultIndexes, vector<int> spaceDifferentIndexes);


            /**
             * @brief prod method: auxiliary function of the recursiveProduct method invoked in the innermost loop of that method. It applies the product part of the Einstein's Formalism between the factors
             * 
             * @param vectorFactorsIndexes: vector of vectors of integer that was correctly filled into the 
             * @return T element obtained from the product of each element retrieved from each factor 
             */
            T prod(vector<vector<int>> vectorFactorsIndexes);

        
        public:

            // Constructors
            /**
             * @brief Construct of a MultiplierTensor object: it initializes the private attributes of the class
             * @param fact1: first TensorWithIndexes factor
             * @param fact2: second TensorWithIndexes factor
             * @param mapOfSpacesAndDimensionsInput: map of integers which contains all the indexes of the resulting tensor. The key is the intentifier integer space and the value is the size dimension
             * @param mapOfEqualIndexesInput: map of integers which contains all the common indexes from all the factors. The key is the intentifier integer space and the value is the size dimension
             * @param vectorDifferentIndexesInput: vector of Index objects of the resulting tensor which will be used for producing a TensorWithIndexes object from an UnknownRankedTensor
             */
            MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfSpacesAndDimensionsInput, map<int, int> mapOfEqualIndexesInput, vector<Index> vectorDifferentIndexesInput);


            /**
             * @brief Construct of a MultiplierTensor object: it copies all the attributes from another MultiplierTensor object
             * 
             * @param mt: MultiplierTensor object from which copy the attributes
             */
            MultiplierTensor(MultiplierTensor<T>& mt);


            // -------------------------------------------------------------------------------------
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


            // --------------------------------------------------------------------------------------------------------------
            // Methods
            /**
             * @brief applyProduct method: it computes the real product and it uses all the attributes obtained from the operators *
             * 
             * @return TensorWithIndexes<T> object which contains the resulting tensor and the correct indexes after the application of the Einstein's Notation
             */
            TensorWithIndexes<T> applyProduct();
    };

}