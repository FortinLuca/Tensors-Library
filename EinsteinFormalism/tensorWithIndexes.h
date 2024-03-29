#include "index.cpp"

namespace TensorIndexes{

    /**
     * @brief TensorWithIndexes class: it defines the objects which allows us to distinguish the indexes for the product between tensors
     * 
     * @tparam T: datatype of the tensor
     */
    template <typename T>
    class TensorWithIndexes{

        private:
            vector<Index> vectorIndexObjects;       // vector which contains the Index objects which will be used for the product operation
            UnknownRankedTensor<T> *tensor;         // pointer to a UnknownRankedTensor object which compose the TensorWithIndexes object (subsumption in case of RankedTensor object)          
            
            friend class Indexes;                   // it can access the private or protected fields of the Index objects
            friend class UnknownRankedTensor<T>;    // it can access the private or protected fields of the UnknownRankedTensor objects

        
        public:
            // Constructors
            /**
             * @brief Constructor of TensorWithIndexes: it initializes all the fields of the class
             * 
             * @param inputVectorIndexObjects: input Index-vector that contains the Index objects which will be used for the product operation
             * @param inputTensor: input pointer to a tensor which will compose the object of this class
             */
            TensorWithIndexes(vector<Index> inputVectorIndexObjects, UnknownRankedTensor<T> &inputTensor);
            

            /**
             * @brief Overloading constructor of TensorWithIndexes: it initializes all the fields of the class
             * 
             * @param inputVectorIndexObjects: input series of Index objects which will be used for the product operation
             * @param inputTensor: input pointer to a tensor which will compose the object of this class
             */
            template <typename... indexes>
            TensorWithIndexes(indexes... inputVectorIndexObjects, UnknownRankedTensor<T> &inputTensor);


            // ---------------------------------------------------------------------------------------------------------
            // Getters
            /**
             * @brief getTensor() method: it gets the pointer tensor parameter
             * 
             * @return UnknownRankedTensor<T>& field, a pointer of the tensor contained in this class
             */
            UnknownRankedTensor<T>& getTensor();


            /**
             * @brief getVectorIndexObjects() method: it returns the Index-vector parameter
             * 
             * @return vector<Index> field contained in this class
             */
            vector<Index> getVectorIndexObjects();

    };

}