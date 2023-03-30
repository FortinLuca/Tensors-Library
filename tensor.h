#include <iostream>
#include <time.h>
#include <random>

using namespace std;


// Tensor_Library class definition
namespace Tensor_Library{

    /**
     * @brief RankedTensor class: tensor has rank information at compile time without having dimensional informations
     * 
     * @tparam T: datatype of the tensor 
     * @tparam n: rank of the tensor
     */
    template <typename T, int n>
    class RankedTensor {


    private:
        int sizeDimensions[n];   // int-array attribute which contains the dimensions' sizes of the tensor
        int n_total_elements;    // int attribute which contains the value of the total elements of the tensor
        int strides[n];          // int-array attribute which contains the strides of the tensor
        vector<T> data;          // int-vector attribute which contains the data of tensor

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
         * @param sizes: int-vector of the dimensions' sizes
         */
        RankedTensor(vector<int> sizes);


        /**
         * @brief Constructor of the RankedTensor class: it initializes all the private attributes of the class. 
         * This is the overload version of the previous constructor that behaves exactly in the same way but with a different parameter in input
         * 
         * @param sizes: series of integers correspondent to the dimensions' sizes
         */
        template <typename... ints>
        RankedTensor(ints...sizes) : RankedTensor(vector<int>({sizes...})){}


        /**
         * @brief Destructor of the RankedTensor class: it will be mantained as default
         */
        ~RankedTensor() = default;
        


        /**
         * @brief get() method: it extracts the element correspondent to the position provided
         * 
         * @param indexes: vector which contains the indexes of the value to extract
         * @return element at the correspondent indexes
         */
        T get(vector<int> indexes);


        /**
         * @brief get() method: it extracts the element correspondent to the position provided
         * 
         * @param indexes: number of int parameters correspondent to the indexes of the value to extract
         * @return element at the correspondent indexes
         */
        template <typename... ints>
        T get(ints...indexes);


        /**
         * @brief 
         * 
         * @tparam ints 
         * @param space 
         * @param indexes 
         * @return RankedTensor<T, n-1> 
         */
        template <typename... ints>
        RankedTensor<T, n-1> fix(const int space, ints... indexes);


        /**
         * @brief 
         * 
         * @tparam ints 
         * @param space 
         * @param indexes 
         * @return RankedTensor<T, n-1> 
         */
        template <typename... ints>
        RankedTensor<T, n-1> fix_copy(const int space, ints... indexes); 


        /**
         * @brief getSizeDimensions() method: extract the array attribute which contains the size's dimensions
         * 
         * @return int-array attribute sizeDimensions
         */
        int * getSizeDimensions();


        /**
         * @brief getStrides() method: extract the array attribute which contains the strides
         * 
         * @return int-array attribute Strides
         */
        int * getStrides();


        /**
         * @brief insertRandomData() method: it inserts pseudo-randomic values into the vector attribute of type T data with a number of element correspondent to the n_total_elements attribute.
         * The insertion is done in order to the type T, the tensor dimensions and the uniform distribution.
         * It exploits the auxiliary, private and static function randomNumber()
         * The range goes from -1000 and to 1000, ***RIMUOVEREI QUESTA PARTE*** --> unless the arithmetic types limits are smaller (like char)
         */
        void insertRandomData();


        /**
         * @brief printTensor() method: it prints every elements contained in the tensor ("data" attribute)
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
        const int n;
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
