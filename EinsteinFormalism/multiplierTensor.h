#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            map<int,int> mapOfSpacesAndDimensions;   // map of the non-common indexes in which the keys are the spaces of the indexes and the values are the dimensions of the spaces
            map<int, int> mapOfEqualIndexes;         // map of the common indexes in which the keys are the spaces of the indexes and the values are the dimensions of the spaces
            int n_factors;                           // number of factors of the products
            vector<TensorWithIndexes<T>> factors;    // vector which contains the TensorWithIndexes objects that are the factor of the product

            // the attributes of this class can be accessed from the classes Indexes and TensorWithIndexes
            friend class Indexes;                    
            friend class TensorWithIndexes<T>;

        
        public:

            // Constructors
            MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfSpacesAndDimensionsInput, map<int, int> mapOfEqualIndexesInput);

            MultiplierTensor(MultiplierTensor<T> mt);


            // getters and setters
            /**
             * @brief GetFactors method: it extract the factors of the product 
             * 
             * @return vector<TensorWithIndexes<T>> object that contains the tensorWithIndexes arguments of the product
             */
            vector<TensorWithIndexes<T>> getFactors();

            /**
             * @brief get_N_factors method: it extract the number of factores of the product
             * 
             * @return int-value which correspond to the number of factors of the product
             */
            int get_N_factors();

            /**
             * @brief getMapOfSpacesAndDimensions method: it extracts the map of the non-common indexes
             * 
             * @return map<int,int> object which contains the spaces of the non-common indexes and their dimensions
             */
            map<int,int> getMapOfSpacesAndDimensions();

            /**
             * @brief getMapOfEqualIndexes method: it extracts the map of the common indexes
             * 
             * @return map<int, int> object which contains the spaces of the common indexes and their dimensions
             */
            map<int, int> getMapOfEqualIndexes();


            // Methods
            //TensorWithIndexes<T> applyProduct();
            void applyProduct();
    };

}