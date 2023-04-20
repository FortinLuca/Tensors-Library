#include "iterators.h"

using namespace std;


namespace Iterators{

    // Constructor implementation
    template <typename T>
    TensorIterator<T>::TensorIterator(UnknownRankedTensor<T> &tensorInput) : tensor(&tensorInput){
        n = tensor->getRank();
        indexes = vector<int>(n);
        endIndexes = vector<int>(n);

        for (int i = 0; i < n; i++) {
            indexes[i] = 0;
            endIndexes[i] = tensor->sizeDimensions[i] - 1;
        }
    }

    
    template <typename T>
    TensorIterator<T>::TensorIterator(UnknownRankedTensor<T> &tensorInput, int space, int index) : tensor(&tensorInput){
        n = tensor->getRank();
        indexes = vector<int>(n);
        endIndexes = vector<int>(n);

        // Checking the validity of the two parameters
        if(space < 0 || index < 0)
            throw invalid_argument("The space and the index in which iterate must be greater than zero");

        // Initializing the space and index fields
        this->space = space;
        this->index = index;

        // Initializing the indexes and endIndexes fields by using space and index values
        for (int i = 0; i < n; i++) {
            if(i != space){
                indexes[i] = 0;
                endIndexes[i] = tensor->sizeDimensions[i] - 1;
            }        
            else{
                indexes[i] = index;
                endIndexes[i] = index;
            }
        }
    }
    

    // Implementation of the hasNext method
    template <typename T>
    bool TensorIterator<T>::hasNext(){
        for(int i = 0; i < n; i++){
            // Checking if we have a successive element
            if(indexes[i] < endIndexes[i])
                return true;
    
            // Checking if we are above the last element
            else if(indexes[i] > endIndexes[i])
                return false;
        }
        //if we are here then we are in te last vector space "i"

        // Checking if we are at the last element
        if(indexes[0] == endIndexes[0])
            return true;

        return false;
    }


    // Implementation of the next method
    template <typename T>
    T TensorIterator<T>::next(){
        int idx = n-1;
        bool check = false;
        int checkLast = indexes[0];

        // Saving the element of the current position into the elem variable by using the get method
        vector<int> vectIndexes(begin(indexes), end(indexes));
        T elem = tensor->get(vectIndexes);

        // Ordered sliding of the tensor elements
        while(!check && idx >= 0){ 
            if(indexes[idx] == endIndexes[idx]){
                // Checking the fixed index of the given space
                if(space < 0 || idx != space)
                    indexes[idx] = 0;
                else
                    indexes[idx] = index;

                idx--;
            }
            else{
                indexes[idx]++;
                check = true;
            }
        }

        // Handling the case where you are in the last element
        if(!check)
            indexes[0] = checkLast + 1;

        // Returning the element saved before
        return elem;
    }


    template <typename T>
    vector<int> TensorIterator<T>::getIndexes(){
        return indexes;
    }


}