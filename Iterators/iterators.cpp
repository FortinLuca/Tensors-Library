#include "iterators.h"

using namespace std;


namespace Iterators{

    // Constructor implementation
    template <typename T, int n>
    RankedTensorIterator<T, n>::RankedTensorIterator(RankedTensor<T, n> &tensorInput) : tensor(&tensorInput){
        for (int i = 0; i < n; i++) {
            indexes[i] = 0;
            endIndexes[i] = tensor->sizeDimensions[i] - 1;
        }
    }

    
    template <typename T, int n>
    RankedTensorIterator<T, n>::RankedTensorIterator(RankedTensor<T, n> &tensorInput, int space, int index) : tensor(&tensorInput){

        if(space < 0 || index < 0)
            throw invalid_argument("The space and the index in which iterate must be greater than zero");

        this->space = space;
        this->index = index;

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
    template <typename T, int n>
    bool RankedTensorIterator<T, n>::hasNext(){
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
    template <typename T, int n>
    T RankedTensorIterator<T, n>::next(){
        int idx = n-1;
        bool check = false;
        int checkLast = indexes[0];

        // Saving the element of the current position into the elem variable by using the get method
        vector<int> vectIndexes(begin(indexes), end(indexes));
        T elem = tensor->get(vectIndexes);

        // Ordered sliding of the tensor elements
        while(!check && idx >= 0){          
            if(indexes[idx] == endIndexes[idx]){
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


}