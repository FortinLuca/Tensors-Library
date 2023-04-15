#include "Iterators/iterators.cpp"

using namespace std;
using namespace Iterators;


// Tensor_Library definition
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
        int sizeDimensions[n];          // int-array attribute which contains the dimensions' sizes of the tensor
        int n_total_elements;           // int attribute which contains the value of the total elements of the tensor
        int strides[n];                 // int-array attribute which contains the strides of the tensor
        shared_ptr<vector<T>> data;     // int-vector pointer attribute which points to the vector that contains the data of tensor
        int init_position;
        friend class RankedTensorIterator<T, n>;

        /**
         * @brief randomNumber method: static, private and auxiliary function used to generate a random T element where T must be an arithmetic type
         * 
         * @return T number generated randomically by the uniform distribution
         */
        static T randomNumber();


    public:
        // Constructors
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
        // template <typename... ints>
        // RankedTensor(ints...sizes) : RankedTensor(vector<int>({sizes...})){}

        RankedTensor(RankedTensor<T, n> &tensor) = default;

        RankedTensor(RankedTensor<T, n> &&tensor) = default;


        /**
         * @brief Destructor of the RankedTensor class: it will be mantained as default
         */
        ~RankedTensor() = default;

        // ********************************************************************************************

        // Operator
        /**
         * @brief 
         * 
         * @param tensorIndexes 
         * @return T 
         */
        T operator()(vector<int> tensorIndexes);

        /**
         * @brief 
         * 
         * @tparam ints 
         * @param tensorIndexes 
         * @return T 
         */
        template <typename... ints>
        T operator()(ints... tensorIndexes);

        
        // *******************************************************************************

        // Getters and Setters
        
        /**
         * @brief getSizeDimensions() method: it extracts the array attribute which contains the size's dimensions
         * 
         * @return int-array attribute sizeDimensions
         */
        int * getSizeDimensions();

        /**
         * @brief getStrides() method: it extracts the array attribute which contains the strides
         * 
         * @return int-array attribute Strides
         */
        int * getStrides();

        /**
         * @brief getData() method: it extracts the Data object
         * 
         * @return shared_ptr<vector<T>> 
         */
        shared_ptr<vector<T>> getData();

        /**
         * @brief setData() method: it sets the Data object
         * 
         * @param newData: it will be the new Data of the tensor
         */
        void setData(shared_ptr<vector<T>> newData);

        /**
         * @brief getInitPosition(): it gets the InitPosition object
         * 
         * @return  
         */
        int getInitPosition();

        /**
         * @brief setInitPosition(): it set the InitPosition object
         * 
         * @param i: it will be the new value of the attribute InitPosition
         */
        void setInitPosition(int i);

        /**
         * @brief get_n_total_elements() methods: Get the n_total_elements
         * 
         * @return the value of the attribute n_total_elements
         */
        int get_n_total_elements();


        // ***********************************************************************************************

        // Methods
        /**
         * @brief get() method: it extracts the element correspondent to the position provided
         * 
         * @param tensorIndexes: vector which contains the indexes of the value to extract
         * @return element at the correspondent indexes
         */
        T get(vector<int> tensorIndexes);


        /**
         * @brief get() method: it extracts the element correspondent to the position provided
         * 
         * @param tensorIndexes: number of int parameters correspondent to the indexes of the value to extract
         * @return element at the correspondent indexes
         */
        template <typename... ints>
        T get(ints...tensorIndexes);


        /**
         * @brief 
         * 
         * @tparam ints 
         * @param space 
         * @param tensorIndexes 
         * @return RankedTensor<T, n-1> 
         */
        RankedTensor<T, n-1> fix(const int space, const int tensorIndex);


        /**
         * @brief 
         * 
         * @tparam ints
         * @param space 
         * @param tensorIndexes 
         * @return RankedTensor<T, n-1> 
         */
        RankedTensor<T, n-1> fix_copy(const int space, const int tensorIndex);


        /**
         * @brief flattening() method: it applies the flattening to a tensor
         * 
         * @return tensor with the same type T and with rank 1. This tensor will share the data with the tensor from which we call this method 
         */
        RankedTensor<T, 1> flattening();

        /**
         * @brief flattening_copy() method: it creates new tensor of rank = 1 applying the flattening to a tensor
         * 
         * @return new tensor with the same type T and with rank 1
         */
        RankedTensor<T, 1> flattening_copy();

        /** @brief window() method: it creates a new tensor of rank = n (original rank) generating a sub-window of given tensor changing the starting-point and end-point of each index
         * 
         * @param min[]: vector of all starting (min) indexes 
         * @param max[]: vector of all ending (max) indexes
         * 
         * @return new tensor with the same type T and rank n but with low (or equal) total number of elements included in data 
         */
        RankedTensor<T, n> window(vector<int> min, vector<int> max);

        // TODO:
        RankedTensor<T, n> window_copy(vector<int> min, vector<int> max);


        // *************************************************************************************************
        // Methods for iterator
        RankedTensorIterator<T, n> getIterator();


        // *************************************************************************************************

        // Methods for testing
        /**
         * @brief insertRandomData() method: it inserts pseudo-randomic values into the vector attribute of type T data with a number of element correspondent to the n_total_elements attribute.
         * The insertion is done in order to the type T, the tensor dimensions and the uniform distribution.
         * It exploits the auxiliary, private and static function randomNumber()
         * The range goes from -1000 and to 1000, ***RIMUOVEREI QUESTA PARTE*** --> unless the arithmetic types limits are smaller (like char)
         */
        void insertRandomData();


        /**
         * @brief printData() method: it prints every elements contained in the tensor ("data" attribute)
         */
        void printData();


        /**
         * @brief printTensor() method: it prints the most important fields (sizeDimensions, strides and n_total_elements) and the data of the correspondent tensor
         * 
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
