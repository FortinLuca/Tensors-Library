# Tensors-Library
[Advanced Algorithms &amp; Programming Methods mod. 2] Creation of a Tensors Library
We have implemented a library that manages the tensor data structure.

## Tensors Classes
Two tensor classes:
* **UnknownRankedTensor**: there is no compile time information about rank or dimensions of the tensor, only type
* **RankedTensor**: the tensor has rank information in its type, but no dimensional information

The data is maintained in a consecutive area. The template specification must maintain an array of the strides and width of each dimension. In the classes there are as attributes also:
* ***stride***: distance in the next element of this index
* width: number of entries for this index

Tensor methods:
* *getters* and *setter*: methods used for retrieving attributes of the tensor classes
* *get*: method used for retrieving an element from a tensor given the position
* *set*: method used for setting an element from a tensor given the position and the element to be inserted
* *getIterator*: methods used for producing a forward iterator for the tensor
* *window* and *window_copy*: methods used for producing a window corresponding to a portion of the tensor (with the same rank) given the initial indexes position and the ending indexes position
* *flattening* and *flattening_copy*: methods used for producing a tensor of rank 1 which contains all the elements of the initial tensor
* *fix* and *fix_copy*: methods used for producing a tensor of rank decreased by one with the slicing of the initial tensor by fixing a specific space

The last three methods have two versions:
* the *normal* version in which the result will point to the data of the original tensor in which the method is applied
* the *copy* version in which the result copies the elements from the original tensors

The *RankedTensor* class is a **subclass** of *UnknownRankedTensor* class, so it inherites parameters and attributes from its superclass. Only in some cases we had to override the method with a similar implementation.


## Iterator class
The class must provide **forward** iterators to the full content of the tensor or to the content along any one index, keeping the other indices fixed.
The only two relevant methods are:
* *hasNext*: it checks whether there is a successive element
* *next*: it retrieves the correct element and it passes to the successive one


## Operation between tensors
For this purpose we have introducted the ***Index*** class which contains an identifier indexes to distinguish the space.
Then from a tensor we can create a ***tensorWithIndexes*** objects which contains the pointer to the original tensor and the indexes.

### Operators
We have introducted the ***operator +*** in order to apply the sum between two TensorWithIndexes objects and two ***operators \**** in order to prepare the product between two TensorWithIndexes objects or one MultiplierTensor object and one TensorWithIndexes object.

### Multiplier class
In this class, after the ***operator \**** are saved all the informations in order to apply the product without losing informations.
The method ***applyProduct*** uses all the attributes saved from the operators * and it applies the product between the factors by following the Einstein's Formalism.

