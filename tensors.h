#include <random>
#include <time.h>
#include <limits>
#include <algorithm>
#include <map>

#include "Iterators/iterators.cpp"


namespace TensorIndexes{
    class Index;

    template <typename T>
    class TensorWithIndexes;

    template <typename T>
    class MultiplierTensor;
}


using namespace Iterators;
using namespace TensorIndexes;


// Tensor_Library definition
namespace Tensor_Library{


    /**
     * @brief UnknownRankedTensor class: the tensor hasn't the rank information at compile-time
     * 
     * @tparam T: datatype of the tensor 
     */
    template <typename T>
    class UnknownRankedTensor {

    protected:  // protected because in this ways the fields can be directly accessed by the RankedTensor class

        // Rank value of the tensor: we don't know at compile-time this value, so the sizeDimensions and strides fields will be vector initialized in the constructor
        int rank;

        vector<int> sizeDimensions;         // int-vector attribute which contains the dimensions' sizes of the tensor
        vector<int> strides;                // int-vector attribute which contains the strides of the tensor
        int n_total_elements;               // int attribute which contains the value of the total elements of the tensor
        shared_ptr<vector<T>> data;         // int-vector pointer attribute which points to the vector that contains the data of tensor
        int init_position;                  // int attribute which helps to keep track of the position in which retrieves elements or builds iterators

        friend class TensorIterator<T>;     // it can access private and protected members of the TensorIterator class

        /**
         * @brief randomNumber() method: it produce a randomic arithmetic number. It's an auxiliar function used the insertRandomData method
         * 
         * @return T-type element produced randomically
         */
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
        UnknownRankedTensor(ints...sizes);


        // Rule of five
        /**
         * @brief Copy-constructor of the UnknownRankedTensor class: it produces a tensor which is the copy of the input one
         * It forces the compiler to produce automatically the copy-constructor 
         * 
         * @param tensor: tensor which will be copied
         */
        UnknownRankedTensor(UnknownRankedTensor<T> &tensor) = default;


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
        virtual ~UnknownRankedTensor() = default;


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


        
        // *******************************************************************************

        // Getters and Setters
        /**
         * @brief getRank() method: it extracts the rank of the tensor
         * 
         * @return int-value which corresponds to the rank of the tensor 
         */
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
         * @return data object of type shared_ptr<vector<T>> (an intelligent pointer of a vector)
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
         * @param tensorIndexes: integer that specify the index of the space which will be fixed
         * @return new tensor of type UnknownRankedTensor<T> with that rank will be reduced by one and the data points to the original tensor
         */
        UnknownRankedTensor<T> fix(const int space, const int tensorIndex);


        /**
         * @brief fix_copy() method: it slices the tensor by fixing a specifing space.
         * The new tensor returned has the data which doesn't point to the original tensor, but it will be copied into another new data structure
         * 
         * @param space: integer that goes from 0 to n-1. It specifies the space which will be fixed
         * @param tensorIndexes: integer that specify the index of the space which will be fixed  
         * @return new UnknownRankedTensor object of type UnknownRankedTensor<T> with the rank that will be reduced by one and the data doesn't point to the original tensor
         */
        UnknownRankedTensor<T> fix_copy(const int space, const int tensorIndex);



        /**
         * @brief flattening() method: it applies the flattening to a tensor. The data will point to the original tensor
         * 
         * @return UnknownRankedTensor object with the same type T and with rank 1. This tensor will share the data with the tensor from which we call this method 
         */
        UnknownRankedTensor<T> flattening();


        /**
         * @brief flattening_copy() method: it creates new tensor of rank = 1 applying the flattening to a tensor. 
         * It will be created a completely new tensor in which the data doesn't point to the original one
         * 
         * @return new UnknownRankedTensor object with the same type T and with rank 1
         */
        UnknownRankedTensor<T> flattening_copy();



        /** 
         * @brief window() method: it creates a new tensor of rank = n (original rank) generating a sub-window of given tensor changing the starting-point and end-point of each index
         * The data will point to the original tensor
         *
         * @param min: vector of all starting (min) indexes 
         * @param max: vector of all ending (max) indexes
         * @return new UnknownRankedTensor object with the same type T and rank n but with low (or equal) total number of elements included in data 
         */
        UnknownRankedTensor<T> window(vector<int> min, vector<int> max);


        /**
         * @brief  window_copy() method: it creates a new tensor of rank = n (original rank) generating a sub-window of a given tensor
         * It will be created a completely new tensor in which the data doesn't point to the original one  
         * 
         * @param min: vector of all starting (min) indexes  
         * @param max: vector of all ending (max) indexes 
         * @return new UnknownRankedTensor object with the same type T and rank n but with low (or equal) total number of elements included in data.
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
         * @param excludingSpace: integer that goes from 0 to n-1. It specifies the space which will be iterated
         * @param inputIndexes: vector integer that specify the indexes that will be fixed 
         * @return new iterator that iterates only on the elements correspondent to the correspondent fixed index and the not-fixed space 
         */
        TensorIterator<T> getIterator(int excludingSpace, vector<int> inputIndexes);


        /**
         * @brief getIterator() method: it produces an iterator which will iterate only on the element with the fixed index on the given space
         * 
         * @param excludingSpace: integer that goes from 0 to n-1. It specifies the space which will be iterated
         * @param inputIndexes: vector integer that specify the indexes that will be fixed 
         * @return new iterator that iterates only on the elements correspondent to the correspondent fixed index and the not-fixed space 
         */
        template <typename... ints>
        TensorIterator<T> getIterator(int excludingSpace, ints... inputIndexes);



        // *************************************************************************************************

        // Methods for testing
        /**
         * @brief insertRandomData() method: it inserts pseudo-randomic values into the vector attribute of type T data with a number of element correspondent to the n_total_elements attribute.
         * The insertion is done in order to the type T, the tensor dimensions and the uniform distribution.
         * It exploits the auxiliary, private and static function randomNumber()
         * The range goes from -1000 and to 1000
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



        // **************************************************************************************************************
        // Operations between tensors

        // Operator which returns the TensorWithIndexes object by giving the indexes to the tensor object
        /**
         * @brief Operator which allows us to produce a TensorWithIndexes objects from a tensor by giving a vector of Index objects
         * 
         * @param spaces: vector of Index objects which will be given to the tensor object
         * @return TensorWithIndexes<T> object which will be useful to the product operation 
         */
        TensorWithIndexes<T> operator()(vector<Index> spaces);

    };





    // ------------------------------------------------------------------------------------------------------------------
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
        RankedTensor(ints...sizes);


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
         * @return RankedTensor object with the same type T and with rank 1. This tensor will share the data with the tensor from which we call this method 
         */
        RankedTensor<T, 1> flattening();


        /**
         * @brief flattening_copy() method: it creates new tensor of rank = 1 applying the flattening to a tensor. 
         * It will be created a completely new tensor in which the data doesn't point to the original one
         * 
         * @return new RankedTensor object with the same type T and with rank 1
         */
        RankedTensor<T, 1> flattening_copy();



        /** 
         * @brief window() method: it creates a new tensor of rank = n (original rank) generating a sub-window of given tensor changing the starting-point and end-point of each index
         * The data will point to the original tensor
         * @param min: vector of all starting (min) indexes 
         * @param max: vector of all ending (max) indexes
         * 
         * @return new RankedTensor object with the same type T and rank n but with low (or equal) total number of elements included in data 
         */
        RankedTensor<T, n> window(vector<int> min, vector<int> max);


        /**
         * @brief  window_copy() method: it creates a new tensor of rank = n (original rank) generating a sub-window of a given tensor
         * It will be created a completely new tensor in which the data doesn't point to the original one  
         * 
         * @param min: vector of all starting (min) indexes  
         * @param max: vector of all ending (max) indexes 
         * @return new RankedTensor object with the same type T and rank n but with low (or equal) total number of elements included in data.
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

        using UnknownRankedTensor<T>::operator();

    };


}
