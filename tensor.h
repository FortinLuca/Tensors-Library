#include <iostream>
#include <time.h>
#include <random>

using namespace std;


// Tensor class definition
namespace Tensor_Library{

    /**
     * @brief RankedTensor class: the tensor has rank information at compile time without having dimensional informations
     * 
     * @tparam T: datatype of the tensor 
     * @tparam n: rank of the tensor
     */
    template <typename T, int n>
    class RankedTensor {


    private:
        int sizeDimensions[n];   // int-array attribute which contains the dimensions' sizes of the tensor
        int n_total_elements;    // int attribute which contains the value of the tensor's total elements
        int strides[n];          // int-array attribute which contains the strides of the tensor
        vector<T> data;          // int-vector attribute which contains the tensor's data

        /**
         * @brief randomNumber method: static, private and auxiliary function used to generate a random T element where T must be an arithmetic type
         * 
         * @return T number generated randomically by the uniform distribution
         */
        static T randomNumber();


    public:
        /**
         * @brief Constructor of the RankedTensor class: it initializes all the private attributes of the class
         * 
         * @param sizes: integer-numbers vector of the dimensions' sizes
         */
        RankedTensor(vector<int> sizes);


        /**
         * @brief Constructor of the RankedTensor class: it initializes all the private attributes of the class. 
         * This is the overloaded version of the previous constructor that behaves exactly in the same way
         * 
         * @param sizes: series of integer correspondent to the dimensions' sizes
         */
        template <typename... ints>
        RankedTensor(ints...sizes) : RankedTensor(vector<int>({sizes...})){}


        /**
         * @brief Destructor of the RankedTensor class: it will be mantained as default
         */
        ~RankedTensor() = default;
        


        /**
         * @brief get method: it extracts the element correspondent to the position requested
         * 
         * @param indexes: vector which contains the indexes of the value to extract
         * @return element at the correspondent entry
         */
        T get(vector<int> indexes);

        //template <typename... ints>
        //get(ints...indexes) : get(vector<int>({indexes...})){}


        /**
         * @brief getSizeDimensions method: extract the array attribute which contains the size's dimensions
         * 
         * @return int-array attribute sizeDimensions
         */
        int * getSizeDimensions();


        /**
         * @brief getStrides method: extract the array attribute which contains the strides
         * 
         * @return int-array attribute Strides
         */
        int * getStrides();


        /**
         * @brief insertRandomData methods: it inserts pseudo-randomic values into the vector attribute of type T data with a number of element correspondent to the n_total_elements attribute.
         * The inserting is made in base of the type T, the tensor dimensions and the uniform distribution.
         * It exploits the auxiliary, private and static function randomNumber
         * The maximum range can be from -1000 to 1000, unless the limits of the arithmetic types has smaller limits (such as char)
         */
        void insertRandomData();


        /**
         * @brief printTensor method: it prints every element contained in the tensor (from the data attribute)
         */
        void printTensor();

    };
        


    // --------------------------------------------------------------------------------------------------------
    /**
     * @brief UnknownRankedTensor class: the tensor hasn't the rank information at the compile time
     * 
     * @tparam T: datatype of the tensor 
     */
    template <typename T>
    class UnknownRankedTensor {

    private:
        /* data */

        
    public:

        /**
         * @brief Constructor of the UnknownRankedTensor class: it initializes all the private attributes of the class
         */
        UnknownRankedTensor();

        /**
         * @brief Destructor of the UnknownRankedTensor class: it will be mantained as default
         */
        ~UnknownRankedTensor();

    };

}
