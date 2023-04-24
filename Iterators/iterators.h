#include <iostream>
#include <cstdlib>
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
     * @brief TensorIterator class: iterator object of the tensor's classes. The methods hasNext() and next() are inspired from
     * the Java's implementation
     * 
     * @tparam T: datatype of the correspondent tensor 
     * @tparam n: rank of the correspondent tensor
     */
    template <typename T>
    class TensorIterator {

        private:

            int n;                                           // Rank of the tensor for which the iterator is built
            UnknownRankedTensor<T> *tensor;                  // pointer to a UnknownRankedTensor object which compose the iterator object (subsumption in case of RankedTensor object)
            vector<int> indexes;                             // indexes which indicates the current position          
            vector<int> endIndexes;                          // indexes of the tensor's last element

            friend class UnknownRankedTensor<T>;             // it can access private and protected members of the UnknownRankedTensor class            

            // Space and index parameter used for the iterators 
            int space = -1; 
            int index = -1;
            
            
        public:
            /**
             * @brief Constructor of the TensorIterator object: it initializes the private attributes of the class (excepts for space and index)
             * In case of RankedTensor object in input, it works anyway for the concept of subsunction of a child class object to a superclass object
             * 
             * @param tensorInput: tensor which gives a shape to the iterator
             */
            TensorIterator(UnknownRankedTensor<T> &tensorInput);


            /**
             * @brief Constructor of the TensorIterator object: it initializes the private attributes of the class (including space and index fields)
             * It constructs an iterator that iterators in a forward way along the content of the index field on the space field
             * 
             * @param tensorInput: tensor which gives a shape to the iterator
             * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
             * @param index: integer that specify the index of the space which will be fixed
             */
            TensorIterator(UnknownRankedTensor<T> &tensorInput, int space, int index);


            /**
             * @brief Destructor of the TensorIterator object
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


            /**
             * @brief getIndexes() method: it asks for the indexes of the iterator that gives the current position during the iteration
             * This method was added because the class RankedTensor can't acceeds the private fields of this class (UnknownRankedTensor can access them because they are friend classes)
             * 
             * @return vector of integer of the indexes
             */
            vector<int> getIndexes();
             
    };
    
}