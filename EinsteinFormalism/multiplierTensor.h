#include "tensorWithIndexes.cpp"

namespace TensorIndexes{

    template <typename T>
    class MultiplierTensor{

        private:

            friend class Indexes;   
            friend class TensorWithIndexes<T>;

        
        public:
        
            MultiplierTensor();

    };

}