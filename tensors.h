#include <random>
#include <time.h>
#include <limits>

#include "Iterators/iterators.cpp"


using namespace Iterators;


// Tensor_Library definition
namespace Tensor_Library{


    /**
     * @brief UnknownRankedTensor class: the tensor hasn't the rank information at the compile time
     * 
     * @tparam T: datatype of the tensor 
     */
    template <typename T>
    class UnknownRankedTensor {

    protected:
        // Rank value of the tensor. We don't know at compiler time this value, so the sizeDimensions and strides fields will be vector initialized in the constructor
        int rank;

        vector<int> sizeDimensions;         // int-array attribute which contains the dimensions' sizes of the tensor
        vector<int> strides;                // int-array attribute which contains the strides of the tensor
        int n_total_elements;               // int attribute which contains the value of the total elements of the tensor
        shared_ptr<vector<T>> data;         // int-vector pointer attribute which points to the vector that contains the data of tensor
        int init_position;

        friend class TensorIterator<T>;


        static T randomNumber();
    
        
    public:

        // Constructors
        /**
         * @brief Constructor of the UnknownRankedTensor class: it initializes all the private attributes of the class
         * 
         * @param sizes: int-vector of the dimensions' sizes
         */
        UnknownRankedTensor(vector<int> sizes);


        /**
         * @brief Constructor of the UnknownRankedTensor class: it initializes all the private attributes of the class. 
         * This is the overload version of the previous constructor that behaves exactly in the same way but with a different parameter in input
         * 
         * @param sizes: series of integers correspondent to the dimensions' sizes
         */
        template <typename... ints>
        UnknownRankedTensor(ints...sizes) : UnknownRankedTensor(vector<int>({sizes...})){}

        // Rule of five
        /**
         * @brief Copy-constructor of the UnknownRankedTensor class: it produces a tensor which is the copy of the input one
         * It forces the compiler to produce automatically the copy-constructor 
         * 
         * @param tensor: tensor which will be copied
         */
        UnknownRankedTensor(const UnknownRankedTensor<T> &tensor) = default;


        /**
         * @brief Move-constructor of the UnknownRankedTensor class: it produces a completely new tensor in which the parameter of the tensor's input will be moved
         * It forces the compiler to produce automatically the move-constructor 
         *
         * @param tensor: tensor in which will be copied in the constructed one
         */
        UnknownRankedTensor(UnknownRankedTensor<T> &&tensor) = default;



        /**
         * @brief Destructor of the UnknownRankedTensor class: it forces the compiler to produce automatically the destructor
         */
        ~UnknownRankedTensor() = default;


        /**
         * @brief Copy assignment operator: 
         * It forces the compiler to generates the assignment operator that assign a copy of the UnknownRankedTensor object reference
         * 
         */
        UnknownRankedTensor& operator=(const UnknownRankedTensor& tensor) = default;

        
        /**
         * @brief Move assignment operator: 
         * It forces the compiler to generates the assignment operator that assign a reference of an UnknownRankedTensor object which has the same parameters of the input one
         * 
         */
        UnknownRankedTensor& operator=(UnknownRankedTensor&& tensor) = default;



        // ********************************************************************************************

        // Operator

        /**
         * @brief Direct access operator in which automatically will be applied the get method by only using the round brackets without specifying get
         * 
         * @param tensorIndexes: vector of integers that contains the indexes of the element which will be returned
         * @return tensor's element of type T which corresponds to the indexes given in input
         */
        T operator()(vector<int> tensorIndexes);


        /**
         * @brief Direct access operator similar to the previous one, but with the difference that the input will be a series of integer corresponding to the positional indexes
         * 
         * @param tensorIndexes: series of integers which composes the indexes of the element to return
         * @return tensor's element of type T which corresponds to the indexes given in input
         */
        template <typename... ints>
        T operator()(ints... tensorIndexes);

        
        // *******************************************************************************

        // Getters and Setters

        int getRank();

        
        /**
         * @brief getSizeDimensions() method: it extracts the array attribute which contains the size's dimensions
         * 
         * @return int-array attribute sizeDimensions
         */
        vector<int> getSizeDimensions();


        /**
         * @brief getStrides() method: it extracts the array attribute which contains the strides
         * 
         * @return int-array attribute Strides
         */
        vector<int> getStrides();


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
         * @return the correspondent integer number of the initial position
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
         * @brief set() method: it sets an element into the tensor given the input indexes
         * 
         * @param elem: element of type T to be inserted into the tensor 
         * @param tensorIndexes: vector of indexes that specifies the position in which insert the element
         */
        void set(T elem, vector<int> tensorIndexes);


        /**
         * @brief set() method: it sets an element into the tensor given the input indexes
         * 
         * @param elem: element of type T to be inserted into the tensor 
         * @param tensorIndexes: a number of int parameters that specifies the position in which insert the element
         */
        template <typename... ints>
        void set(T elem, ints... tensorIndexes);



        /**
         * @brief fix() method: it slices the tensor by fixing a specifing space
         *  
         * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
         * @param tensorIndexes: integer that specify the index of the space which will be fices 
         * @return new tensor of type UnknownRankedTensor<T> with that rank will be reduced by one and the data points to the original tensor
         */
        UnknownRankedTensor<T> fix(const int space, const int tensorIndex);


        /**
         * @brief fix_copy() method: it slices the tensor by fixing a specifing space.
         * The new tensor returned has the data which doesn't point to the original tensor, but it will be copied into another new data structure
         * 
         * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
         * @param tensorIndexes: integer that specify the index of the space which will be fixed  
         * @return new tensor of type UnknownRankedTensor<T> with the rank that will be reduced by one and the data doesn't point to the original tensor
         */
        UnknownRankedTensor<T> fix_copy(const int space, const int tensorIndex);



        /**
         * @brief flattening() method: it applies the flattening to a tensor. The data will point to the original tensor
         * 
         * @return tensor with the same type T and with rank 1. This tensor will share the data with the tensor from which we call this method 
         */
        UnknownRankedTensor<T> flattening();


        /**
         * @brief flattening_copy() method: it creates new tensor of rank = 1 applying the flattening to a tensor. 
         * It will be created a completely new tensor in which the data doesn't point to the original one
         * 
         * @return new tensor with the same type T and with rank 1
         */
        UnknownRankedTensor<T> flattening_copy();



        /** 
         * @brief window() method: it creates a new tensor of rank = n (original rank) generating a sub-window of given tensor changing the starting-point and end-point of each index
         * The data will point to the original tensor
         *
         * @param min: vector of all starting (min) indexes 
         * @param max: vector of all ending (max) indexes
         * 
         * @return new tensor with the same type T and rank n but with low (or equal) total number of elements included in data 
         */
        UnknownRankedTensor<T> window(vector<int> min, vector<int> max);


        /**
         * @brief  window_copy() method: it creates a new tensor of rank = n (original rank) generating a sub-window of a given tensor
         * It will be created a completely new tensor in which the data doesn't point to the original one  
         * 
         * @param min: vector of all starting (min) indexes  
         * @param max: vector of all ending (max) indexes 
         * @return new tensor with the same type T and rank n but with low (or equal) total number of elements included in data.
         */
        UnknownRankedTensor<T> window_copy(vector<int> min, vector<int> max);



        // *************************************************************************************************
        // Methods for iterator

        /**
         * @brief getIterator() method: it produces an iterator of a corresponding tensor
         * 
         * @return iterator of type TensorIterator<T>, with T corresponding to the type
         */
        TensorIterator<T> getIterator();


        /**
         * @brief getIterator() method: it produces an iterator which will iterate only on the element with the fixed index on the given space
         * 
         * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
         * @param index: integer that specify the index of the space which will be fixed 
         * @return new iterator that iterates only on the elements correspondent to the correspondent fixed index on the given space  
         */
        TensorIterator<T> getIterator(int excludingSpace, vector<int> inputIndexes);



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


        // *****************************************************************************************

        // Methods for the operations between tensors
        /**
         * @brief algebraicSum() method: it modifies all the elements of the tensor by summing each of its element with the element of the input's tensor 
         * 
         * @param tensor: tensor with the same rank and type of the current one. The two tensors must have the same dimensions
         * @return the current tensor with all elements modified by the algebraic sum of the elements
         */
        UnknownRankedTensor<T> algebraicSum(UnknownRankedTensor<T> tensor);


        /**
         * @brief algebraicSum() method: it modifies all the elements of the tensor by summing each of its element with the input element of type T
         * 
         * @param elem: element of type T which will be summed to each element of the tensor
         * @return the current tensor with all elements modified by the algebraic sum of the elements with the input one
         */
        UnknownRankedTensor<T> algebraicSum(T elem);



        /**
         * @brief Operator which lets the application of the algebraic sum between two tensors with the + operator. 
         * It applies the algebraicSum() method between the current tensor and the input one
         * 
         * @param tensor: tensor with the same rank and type of the current one. The two tensors must have the same dimensions
         * @return the current tensor with all elements modified by the algebraic sum of the elements
         */
        UnknownRankedTensor<T> operator+(UnknownRankedTensor<T> tensor);


        /**
         * @brief Operator which lets the application of the algebraic sum between two tensors with the + operator.
         * It applies the algebraicSum() method between the current tensor and the input element of type T
         * 
         * @param elem: element of type T which will be summed to each element of the tensor
         * @return the current tensor with all elements modified by the algebraic sum of the elements with the input one
         */
        UnknownRankedTensor<T> operator+(T elem);


        // TODO: Product between tensors with Einstein's formalism


    };





    // -----------------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------





    /**
     * @brief RankedTensor class: tensor has rank information at compile time without having dimensional informations
     * 
     * @tparam T: datatype of the tensor 
     * @tparam n: rank of the tensor
     */
    template <typename T, int n>
    class RankedTensor : public UnknownRankedTensor<T>{


    private:        

        /**
         * @brief randomNumber method: static, private and auxiliary function used to generate a random T element where T must be an arithmetic type
         * 
         * @return T number generated randomically by the uniform distribution
         */

        using UnknownRankedTensor<T>::randomNumber;


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
        template <typename... ints>
        RankedTensor(ints...sizes) : RankedTensor(vector<int>({sizes...})){}


        /**
         * @brief Constructor of the RankedTensor class: it produces a tensor which is the copy of the input one
         * 
         * @param tensor: tensor which will be copied
         */
        RankedTensor(RankedTensor<T, n> &tensor) = default;


        /**
         * @brief Constructor of the RankedTensor class: it produces a completely new tensor in which the parameter of the tensor's input will be moved
         * 
         * @param tensor: tensor in which will be copied in the constructed one
         */
        RankedTensor(RankedTensor<T, n> &&tensor) = default;


        /**
         * @brief Destructor of the RankedTensor class: it will be mantained as default
         */
        ~RankedTensor() = default;


        /**
         * @brief Copy assignment operator: 
         * It forces the compiler to generates the assignment operator that assign a copy of the RankedTensor object reference
         * 
         */
        RankedTensor& operator=(const RankedTensor& tensor) = default;

        
        /**
         * @brief Move assignment operator: 
         * It forces the compiler to generates the assignment operator that assign a reference of a RankedTensor object which has the same parameters of the input one
         * 
         */
        RankedTensor& operator=(RankedTensor&& tensor) = default;



        // ********************************************************************************************

        // Operator

        /**
         * @brief Direct access operator in which automatically will be applied the get method by only using the round brackets without specifying get
         * 
         * @param tensorIndexes: vector of integers that contains the indexes of the element which will be returned
         * @return tensor's element of type T which corresponds to the indexes given in input
         */
        //T operator()(vector<int> tensorIndexes);
        //using UnknownRankedTensor<T>::operator();


        /**
         * @brief Direct access operator similar to the previous one, but with the difference that the input will be a series of integer corresponding to the positional indexes
         * 
         * @param tensorIndexes: series of integers which composes the indexes of the element to return
         * @return tensor's element of type T which corresponds to the indexes given in input
         */


        
        // *******************************************************************************

        // Getters and Setters


        // getRank() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::getRank;
        

        // getSizeDimensions() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::getSizeDimensions;


        // getStrides() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::getStrides;


        // getData() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::getData;


        // setData() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::setData;


        // getInitPosition() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::getInitPosition;


        // setInitPosition() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::setInitPosition;


        // get_n_total_elements() methods: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::get_n_total_elements;



        // ***********************************************************************************************

        // Methods

        // get() method: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::get;



        // set() method: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::set;


        /**
         * @brief fix() method: it slices the tensor by fixing a specifing space
         *  
         * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
         * @param tensorIndexes: integer that specify the index of the space which will be fices 
         * @return new tensor of type RankedTensor<T, n-1>, the rank will be reduced by one and the data points to the original tensor
         */
        RankedTensor<T, n-1> fix(const int space, const int tensorIndex);


        /**
         * @brief fix_copy() method: it slices the tensor by fixing a specifing space.
         * The new tensor returned has the data which doesn't point to the original tensor, but it will be copied into another new data structure
         * 
         * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
         * @param tensorIndexes: integer that specify the index of the space which will be fixed  
         * @return new tensor of type RankedTensor<T, n-1>, the rank will be reduced by one and the data doesn't point to the original tensor
         */
        RankedTensor<T, n-1> fix_copy(const int space, const int tensorIndex);



        /**
         * @brief flattening() method: it applies the flattening to a tensor. The data will point to the original tensor
         * 
         * @return tensor with the same type T and with rank 1. This tensor will share the data with the tensor from which we call this method 
         */
        RankedTensor<T, 1> flattening();


        /**
         * @brief flattening_copy() method: it creates new tensor of rank = 1 applying the flattening to a tensor. 
         * It will be created a completely new tensor in which the data doesn't point to the original one
         * 
         * @return new tensor with the same type T and with rank 1
         */
        RankedTensor<T, 1> flattening_copy();



        /** 
         * @brief window() method: it creates a new tensor of rank = n (original rank) generating a sub-window of given tensor changing the starting-point and end-point of each index
         * The data will point to the original tensor
         * @param min: vector of all starting (min) indexes 
         * @param max: vector of all ending (max) indexes
         * 
         * @return new tensor with the same type T and rank n but with low (or equal) total number of elements included in data 
         */
        RankedTensor<T, n> window(vector<int> min, vector<int> max);


        /**
         * @brief  window_copy() method: it creates a new tensor of rank = n (original rank) generating a sub-window of a given tensor
         * It will be created a completely new tensor in which the data doesn't point to the original one  
         * 
         * @param min: vector of all starting (min) indexes  
         * @param max: vector of all ending (max) indexes 
         * @return new tensor with the same type T and rank n but with low (or equal) total number of elements included in data.
         */
        RankedTensor<T, n> window_copy(vector<int> min, vector<int> max);



        // *************************************************************************************************

        // Methods for iterator

        // getIterator() method: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::getIterator;



        // *************************************************************************************************

        // Methods for testing
  

        // insertRandomData() method: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::insertRandomData;


        // printData() method: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::printData;


        // printTensor() method: inherited from the superclass UnknownRankedTensor
        using UnknownRankedTensor<T>::printTensor;



        // *****************************************************************************************

        // Methods for the operations between tensors
        /**
         * @brief algebraicSum() method: it modifies all the elements of the tensor by summing each of its element with the element of the input's tensor 
         * 
         * @param tensor: tensor with the same rank and type of the current one. The two tensors must have the same dimensions
         * @return the current tensor with all elements modified by the algebraic sum of the elements
         */
        RankedTensor<T, n> algebraicSum(RankedTensor<T, n> tensor);


        /**
         * @brief algebraicSum() method: it modifies all the elements of the tensor by summing each of its element with the input element of type T
         * 
         * @param elem: element of type T which will be summed to each element of the tensor
         * @return the current tensor with all elements modified by the algebraic sum of the elements with the input one
         */
        RankedTensor<T, n> algebraicSum(T elem);



        /**
         * @brief Operator which lets the application of the algebraic sum between two tensors with the + operator. 
         * It applies the algebraicSum() method between the current tensor and the input one
         * 
         * @param tensor: tensor with the same rank and type of the current one. The two tensors must have the same dimensions
         * @return the current tensor with all elements modified by the algebraic sum of the elements
         */
        RankedTensor<T, n> operator+(RankedTensor<T, n> tensor);


        /**
         * @brief Operator which lets the application of the algebraic sum between two tensors with the + operator.
         * It applies the algebraicSum() method between the current tensor and the input element of type T
         * 
         * @param elem: element of type T which will be summed to each element of the tensor
         * @return the current tensor with all elements modified by the algebraic sum of the elements with the input one
         */
        RankedTensor<T, n> operator+(T elem);



        // TODO: Product between tensors with Einstein's formalism 

    };


}
