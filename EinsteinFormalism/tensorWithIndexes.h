#include "index.cpp"

namespace TensorIndexes{

    template <typename T>
    class TensorWithIndexes{

        private:
            vector<Index> spaces;
            UnknownRankedTensor<T> *tensor;     // pointer to a UnknownRankedTensor object which compose the iterator object (subsumption in case of RankedTensor object)

        
        public:
            TensorWithIndexes(vector<Index> inputSpaces, UnknownRankedTensor<T> &inputTensor);
            

            template <typename... indexes>
            TensorWithIndexes(indexes... inputSpaces, UnknownRankedTensor<T> &inputTensor);


    };

}