#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            map<int,int> mapOfSpacesAndDimensions;
            map<int, int> mapOfEqualIndexes;
            int n_factors;
            vector<TensorWithIndexes<T>> factors;

            friend class Indexes;   
            friend class TensorWithIndexes<T>;

        
        public:

            // Constructors
            MultiplierTensor(TensorWithIndexes<T> fact1, TensorWithIndexes<T> fact2, map<int,int> mapOfSpacesAndDimensionsInput, map<int, int> mapOfEqualIndexesInput);

            MultiplierTensor(MultiplierTensor<T> mt, TensorWithIndexes<T> factor);


            // getters and setters
            vector<TensorWithIndexes<T>> getFactors();

            int get_N_factors();

            map<int,int> getMapOfSpacesAndDimensions();

            map<int, int> getMapOfEqualIndexes();
    };

}