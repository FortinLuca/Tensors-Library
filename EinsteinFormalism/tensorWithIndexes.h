#include "index.cpp"

namespace TensorIndexes{

    template <typename T>
    class TensorWithIndexes : public UnknownRankedTensor<T>{

        private:
            vector<Index> spaces;

        
        public:
            TensorWithIndexes(vector<Index> spaces);
            

            template <typename... indexes>
            TensorWithIndexes(indexes... spaces);


    };

}