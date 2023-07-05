#include "multiplierTensor.cpp"

namespace operators{
    
    template <typename T>
    /**
     * @brief + operator: it applies the sum between the two addends only if they contains the same indexes with the same sizeDimensions
     * 
     * @param tensorWithIndexes1: TensorWithIndexes<T> object on which will be applied the sum between itself and the other parameter
     * @param tensorWithIndexes2: TensorWithIndexes<T> object on which will be applied the sum between itself and the other parameter
     * @return TensorWithIndexes<T> object with the same dimensions of the factor and with an associated UnknownRankedTensor<T> object 
     * which contains the data which is the sum of the data of the two addends
     */
    TensorWithIndexes<T> operator +(TensorWithIndexes<T> tensorWithIndexes1, TensorWithIndexes<T> tensorWithIndexes2);



    template <typename T>
    /**
     * @brief * operator: it produces a MultiplierTensor<T> object which will save the useful informations in order to apply the product 
     * The product will be postponed on the constructor of the class MultiplierTensor because otherwise we loose some common indexes of other factors
     * 
     * @param tensorWithIndexes1 TensorWithIndexes<T> object on which will be applied the product between itself and the other parameter
     * @param tensorWithIndexes2 TensorWithIndexes<T> object on which will be applied the product between itself and the other parameter
     * @return  MultiplierTensor<T> object that take trace of the data, the common indexes and every other information which will be useful for the product 
     */
    MultiplierTensor<T> operator *(TensorWithIndexes<T> tensorWithIndexes1, TensorWithIndexes<T> tensorWithIndexes2);



    template <typename T>
    /**
     * @brief 
     * 
     * @param multiplierTensor 
     * @param tensorWithIndexes 
     * @return MultiplierTensor<T> 
     */
    MultiplierTensor<T> operator *(MultiplierTensor<T> multiplierTensor, TensorWithIndexes<T> tensorWithIndexes);

}