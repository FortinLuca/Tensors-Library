
namespace Tensor_Library{
    template <class T, int n>
    class RankedTensor;

    template <class T>
    class UnknownRankedTensor;
}


using namespace Tensor_Library;


namespace Iterators{
    
    template <typename T, int n>
    class RankedTensorIterator {

        private:
            friend class RankedTensor<T, n>;
            RankedTensor<T, n> *tensor;
            int indexes[n];
            int startIndexes[n];
            int endIndexes[n];


        public:
            RankedTensorIterator(RankedTensor<T, n> &tensorInput);

            ~RankedTensorIterator() = default;

            bool hasNext();

            T next();

    };
    

}