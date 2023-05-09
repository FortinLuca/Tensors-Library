#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            vector<int> vectorOfSpaces;
            vector<int> resultMultiplier;
            friend class Indexes;   
            friend class TensorWithIndexes<T>;

        
        public:
        
            MultiplierTensor(vector<int> multiplierOperationsInput, vector<int> vectorOfSpacesInput);

    };

}