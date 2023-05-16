#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            map<int,int> mapOfSpacesAndDimensions;
            vector<Index> vectorOfIndexes;
            friend class Indexes;   
            friend class TensorWithIndexes<T>;

        
        public:
        
            MultiplierTensor(map<int,int> mapOfSpacesAndDimensionsInput);

            MultiplierTensor();

    };

}