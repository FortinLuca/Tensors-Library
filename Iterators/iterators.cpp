#include "iterators.h"


namespace Iterators{

    // Constructor implementation, in case of RankedTensor object input, it works anyway for subsuption
    template <typename T>
    TensorIterator<T>::TensorIterator(UnknownRankedTensor<T> &tensorInput) : tensor(&tensorInput){

        // A zero-rank tensor cannot have an iterator
        if(tensorInput.getRank() <= 0)
            throw invalid_argument("The rank for the production of an iterator must be greater than zero");

        // Initialization of the rank and the flag
        n = tensor->getRank();
        indexes = vector<int>(n);
        endIndexes = vector<int>(n);
        this->isIteratorAllContent = true;

        // Initializing the indexes and endIndexes fields by using space and index values
        for (int i = 0; i < n; i++) {
            indexes[i] = 0;
            endIndexes[i] = tensor->sizeDimensions[i] - 1;
        }
    }

    
    template <typename T>
    TensorIterator<T>::TensorIterator(UnknownRankedTensor<T> &tensorInput, int excludingSpace, vector<int> inputIndexes) : tensor(&tensorInput){

        // A zero-rank tensor cannot have an iterator
        n = tensor->getRank();
        if(n <= 0)
            throw invalid_argument("The rank for the production of an iterator must be greater than zero");
        
        indexes = vector<int>(n);
        endIndexes = vector<int>(n);

        int inputIndexesSize = inputIndexes.size();

        // Checking the validity of the parameters
        if (excludingSpace < 0) throw invalid_argument("The space to exclude in which to iterate must be greater than zero");
        if (excludingSpace > n-1) throw invalid_argument("The space to exclude in which to iterate must be lower than the rank - 1 size (starting from 0)");
        if (inputIndexesSize != n-1) throw invalid_argument("The inputIndexes size must have exactly rank - 1 size elements (staring from 0)");

        for (int i=0; i<n-1; i++) {
            if (inputIndexes[i] < 0) throw invalid_argument("One of the indexes chosen in which to iterate is lower than zero");
            if (inputIndexes[i] > this->tensor->getSizeDimensions()[i]-1) throw invalid_argument("One of the indexes chosen in which to iterate is greater than the relative size dimension of the original tensor");
        }

        // Initializing the tensorSpaces and tensorIndexes support vectors to enable the check on which space to iterate and from which indeces to start   
        int i;
        for (i=0; i<=n-1; i++) {
            this->tensorSpaces.push_back(i);
        }

        this->tensorSpaces.erase(tensorSpaces.begin() + excludingSpace);
        this->tensorIndexes.insert(tensorIndexes.begin(), std::begin(inputIndexes), std::end(inputIndexes));
        this->isIteratorAllContent = false;

        bool flag = false;
        int sup = 0;

        // Initializing the indexes and endIndexes fields by using excludingSpace and indexes values and exploiting the "flag" and "sup" variables 
        // to understand if we have already meet the excluding space to skip
        for (int i = 0; i < n; i++) {
            if(i == excludingSpace){
                indexes[i] = 0;
                endIndexes[i] = tensor->sizeDimensions[i] - 1;
                flag = true;
            } else {
                if (flag) sup = 1;
                indexes[i] = inputIndexes[i- sup] ;
                endIndexes[i] = inputIndexes[i- sup];
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
        //if we are here then we are in the last vector space "i"

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
        int sup = 1;

        // Saving the element of the current position into the elem variable by using the get method
        vector<int> vectIndexes(begin(indexes), end(indexes));
        T elem = tensor->get(vectIndexes);

        // Ordered smoothness of the tensor elements
        while(!check && idx >= 0){ 
            if(indexes[idx] == endIndexes[idx]){

                // Checking the fixed index of the given spaces and if it's the case of the iterator of all content (or not)
                // "sup" variable is used also in this case to understand if we have already meet the excluding space to skip
                if(isIteratorAllContent || idx != tensorSpaces[idx-sup]) {
                    indexes[idx] = 0;
                    sup = 0;
                } else {
                    indexes[idx] = tensorIndexes[idx-sup];
                }
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


    // getter useful for the RankedTensor object because I can't set that as friend class for the different template
    template <typename T>
    vector<int> TensorIterator<T>::getIndexes(){
        return indexes;
    }


}