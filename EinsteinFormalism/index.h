#include "../Utils/TensorUtils.cpp"

namespace TensorIndexes{

    /**
     * @brief Index class: it defines an object index which is important for producing a tensotWithIndexes object
     * 
     */
    class Index {

        private:
            int space;  // int-value which specifies the dimensional-space that the index represent

        public:
            /**
             * @brief Constructor of the class Index: it initializes the only field of the class Index
             * 
             * @param space: int-value which corresponds to the dimensional space represented by the Index object
             */
            Index(int space);

            /**
             * @brief getSpace() method: it extracts the dimensional space represented by to the Index object
             * 
             * @return space: int-value which corresponds to the dimensional space represented by the Index object
             */
            int getSpace();
    
    };

}
