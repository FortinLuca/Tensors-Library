#include <iostream>
#include <time.h>
#include <random>
#include <vector>
#include <memory>

// Declaration of the classes on the namespace Tensor_Library because for the iteration's classes we need to use the Tensor Library
namespace Tensor_Library{
    template <class T, int n>
    class RankedTensor;

    template <class T>
    class UnknownRankedTensor;
}


using namespace Tensor_Library;
using namespace std;


// Iterators definition
namespace Iterators{

    /**
     * @brief RankedTensorIterator class: iterator object of the RankedTensor class. The methods hasNext() and next() are inspired from
     * the Java's implementation
     * 
     * @tparam T: datatype of the correspondent tensor 
     * @tparam n: rank of the correspondent tensor
     */
    template <typename T>
    class TensorIterator {

        private:

            int n;
            friend class UnknownRankedTensor<T>;             // it can access private and protected members of the RankedTensor class
            UnknownRankedTensor<T> *tensor;                  // tensor which compose the iterator object
            vector<int> indexes;                             // indexes which indicates the current position          
            vector<int> endIndexes;                          // indexes of the tensor's last element
            
            // Space and index parameter used for the iterators 
            int space = -1; 
            int index = -1;
            
            
        public:
            /**
             * @brief Constructor of the RankedTensorIterator object: it initializes the private attributes of the class (excepts for space and index)
             * 
             * @param tensorInput: tensor which gives a shape to the iterator
             */
            TensorIterator(UnknownRankedTensor<T> &tensorInput);


            /**
             * @brief Constructor of the RankedTensorIterator object: it initializes the private attributes of the class (including space and index fields)
             * It constructs an iterator that iterators in a forward way along the content of the index field on the space field
             * 
             * @param tensorInput: tensor which gives a shape to the iterator
             * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
             * @param index: integer that specify the index of the space which will be fixed
             */
            TensorIterator(UnknownRankedTensor<T> &tensorInput, int space, int index);

            /**
             * @brief Destructor of the RankedTensorIterator object
             * 
             */
            ~TensorIterator() = default;

            /**
             * @brief hasNext() method: it check the presence of a new element after the current one
             * 
             * @return boolean which says true if a next element exists, false otherwise 
             */
            bool hasNext();

            /**
             * @brief next() method: it gives the current element of the tensor by seeing the indexes attribute and then it 
             * goes to the position of the next element
             * 
             * @return T element which corresponds to the current value of the array indexes
             */
            T next();

    };
    

}