#include "tensorWithIndexes.h"

namespace TensorIndexes{

    template <typename T>
    TensorWithIndexes<T>::TensorWithIndexes(vector<Index> inputSpaces, UnknownRankedTensor<T> &inputTensor) : tensor(&inputTensor){

        // Reserving a portion of memory to the spaces field
        spaces.reserve(tensor->getRank());
        int sizeInputSpaces = inputSpaces.size();

        // Checking if the rank and the dimension of the Index-vector corresponds
        if(tensor->getRank() != sizeInputSpaces) throw invalid_argument("The rank must corresponds to the number of indexes inserted in input");
        
        int sizeOfThis = inputSpaces.size();
        vector<int> inputSpaces_int = vector<int>(sizeOfThis);
        for(int i=0; i<sizeOfThis; i++) {
            inputSpaces_int[i]=inputSpaces[i].getSpace();
        }

        // TODO: portare inputSpaces_int come variabile globale per usufruirne nella funzione operator * ?
        // Checking if in the inputSpaces parameter there are the same space more times
        vector<int>::iterator it;
        for (int i=0; i<sizeOfThis; i++) {
            if (count(inputSpaces_int.begin(), inputSpaces_int.end(), inputSpaces_int[i]) > 1) throw invalid_argument("A tensorWithIndexes can't have two or more identical dimensional spaces (indexes)");
        }

        // Copying into the field all the elements of the input vector
        for (int i=0; i<tensor->getRank(); i++) 
            spaces.push_back(inputSpaces[i]); 
    }


    template <typename T>
    template <typename... indexes>
    TensorWithIndexes<T>::TensorWithIndexes(indexes... inputSpaces, UnknownRankedTensor<T> &inputTensor) : TensorWithIndexes<T>::TensorWithIndexes(vector<Index>({inputSpaces...}), inputTensor){

    }

    template <typename T>
    UnknownRankedTensor<T>& TensorWithIndexes<T>::getTensor(){
        return *tensor;
    }


    template <typename T>
    vector<Index> TensorWithIndexes<T>::getSpaces(){
        return spaces;
    }


    template <typename T>
    TensorWithIndexes<T> TensorWithIndexes<T>::operator +(TensorWithIndexes<T> tensorWithIndexes) {

        // We retrieve the spaces (indexes) and relative size of "this" (first tensor before the operator *) and the parameter of input "tensorWithIndexes" (second tensor after the operator *)
        // from now on the first tensor is related to the key word "this" and the second tensor is related to the key word "input"
        vector<Index> spacesOfThis = this->getSpaces();
        vector<Index> spacesOfInput = tensorWithIndexes.getSpaces();
        int sizeOfThis = spacesOfThis.size();
        int sizeOfInput = spacesOfInput.size();

        // Checking the ranks of the tensors to sum
        if(sizeOfThis != sizeOfInput) throw invalid_argument("The tensors for algebraic sums must be with the same rank");

        vector<int> sizeDimensionsOfThis = this->getTensor().getSizeDimensions();
        vector<int> sizeDimensionsOfInput = tensorWithIndexes.getTensor().getSizeDimensions();

        // Checking the order of the indexes and their dimensionality
        for(int i = 0; i < sizeOfThis; i++){
            if(spacesOfThis[i].getSpace() != spacesOfInput[i].getSpace()) 
                throw invalid_argument("The tensors must have the same spaces in the same order for the application of the algebraic sum");
            
            if(sizeDimensionsOfThis[i] != sizeDimensionsOfInput[i])
                throw invalid_argument("The tensors must have the same sizeDimensions value in the same order fot the application of the algebraic sum");

        }

        // Creating a new data vector and a new tensor
        UnknownRankedTensor<T> newTensor(sizeDimensionsOfThis);
        int n_total_elements = newTensor.get_n_total_elements();
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);

        // Creating the two iterators
        TensorIterator<T> itOfThis = this->getTensor().getIterator();
        TensorIterator<T> itOfInput = tensorWithIndexes.getTensor().getIterator();
        int index = 0;

        // Since there are the same dimensions, the iterators iterates in the same number of steps
        while(itOfThis.hasNext() && itOfInput.hasNext()){         
            T elem1 = itOfThis.next();
            T elem2 = itOfInput.next();
            newData->at(index) = elem1 + elem2;
            index++;
        }

        // Inserting the new pointer of data and returning the current tensor
        this->getTensor().setData(newData);
        
        // Returning the final result
        return *this;    
        
    }



    template <typename T>
    TensorWithIndexes<T> TensorWithIndexes<T>::operator *(TensorWithIndexes<T> tensorWithIndexes) { 
        // we retrieve the spaces (indexes) and relative size of "this" (first tensor before the operator *) and the parameter of input "tensorWithIndexes" (second tensor after the operator *)
        // from now on the first tensor is related to the key word "this" and the second tensor is related to the key word "input"
        vector<Index> spacesOfThis = this->getSpaces();
        vector<Index> spacesOfInput = tensorWithIndexes.getSpaces();
        int sizeOfThis = spacesOfThis.size();
        int sizeOfInput = spacesOfInput.size();

        // we retrieve the vectors containing the sizeDimensions of this tensor and input tensor and the relative sizes of the both vectors
        vector<int> tensorSizeDimensionsOfInput = tensorWithIndexes.getTensor().getSizeDimensions();
        vector<int> tensorSizeDimensionsOfThis = this->getTensor().getSizeDimensions();
        int sizeTensorSizeDimensionsOfInput = tensorSizeDimensionsOfInput.size();
        int sizeTensorSizeDimensionsOfThis = tensorSizeDimensionsOfThis.size();

        // creation of support vectors of integer "spacesOfThis_int" and "spacesOfInput_int" where the elements are the mapped values of the respective vectors of Index "spacesOfThis" and "spacesOfInput"
        // in this way we exploit the vector iterator function find() to make all more readble
        vector<int> spacesOfThis_int = vector<int>(sizeOfThis);
        for(int i=0; i<sizeOfThis; i++) {
            spacesOfThis_int[i]=spacesOfThis[i].getSpace();
        }
        vector<int> spacesOfInput_int = vector<int>(sizeOfInput);
        for(int i=0; i<sizeOfInput; i++) {
            spacesOfInput_int[i]=spacesOfInput[i].getSpace();
        }

        // creation of support maps "mapTensorSizeDimensionsOfThis" and "mapTensorSizeDimensionsOfInput" with key equal to the dimensional space (index) of the relative tensorWithIndexes and value equal to its sizeDimension (corresponding to that dimensional space) 
        map<int, int> mapTensorSizeDimensionsOfThis;
        map<int, int> mapTensorSizeDimensionsOfInput;
        for (int i = 0; i<sizeTensorSizeDimensionsOfThis; i++) {
            mapTensorSizeDimensionsOfThis[spacesOfThis_int[i]] = tensorSizeDimensionsOfThis[i];
        }
        for (int i = 0; i<sizeTensorSizeDimensionsOfInput; i++) {
            mapTensorSizeDimensionsOfInput[spacesOfInput_int[i]] = tensorSizeDimensionsOfInput[i];
        }

        // according to the dimensional spaces' size, we decide to use the one with the bigger size as parameter of the find() function
        // in this way we iterate along all the bigger vector to find the same space from the lower vector without losing possible dimensional spaces (indexes)
        if (spacesOfThis.size() >= spacesOfInput.size()) {
            vector<int>::iterator it;
            for(int i = 0; i<sizeOfInput; i++) {
                // inside this "if" block, through find() function, we search (and then check) if the dimensional spaces (indexes) of the first tensor 
                // are included in the ones of the second tensor, or viceversa
                int spaceToFind = spacesOfInput[i].getSpace();
                it = find(spacesOfThis_int.begin(), spacesOfThis_int.end(), spaceToFind);
                if (it == spacesOfThis_int.end()) throw invalid_argument("No match between the two tensors'spaces. It's mandatory that the second tensor (with lower rank) has the same identical spaces (i,j,k,etc..) of the first one (with greater rank)");
                
                // through the two support maps, we check the two sizeDimensions's equality of the same dimensional space  
                int dimensionSizeOfThis = mapTensorSizeDimensionsOfThis.at(spaceToFind);
                int dimensionSizeOfInput = mapTensorSizeDimensionsOfInput.at(spaceToFind);
                if (dimensionSizeOfInput != dimensionSizeOfThis) throw invalid_argument("The dimensional space's size of the first tensor must be equal to that of the same dimensional space of the second tensor");
            }
        } else {
            vector<int>::iterator it;
            for(int i = 0; i<sizeOfThis; i++) {
                // inside this "if" block, through find() function, we search (and then check) if the dimensional spaces (indexes) of the second tensor 
                // are included in the ones of the first tensor, or viceversa
                int spaceToFind = spacesOfThis[i].getSpace();
                it = find(spacesOfInput_int.begin(), spacesOfInput_int.end(), spaceToFind);
                if (it == spacesOfInput_int.end()) throw invalid_argument("No match between the two tensors'spaces. It's mandatory that the first tensor (with lower rank) has the same identical spaces (i,j,k,etc..) of the second one (with greater rank)");

                // through the two support maps, we check the two sizeDimensions's equality of the same dimensional space  
                int dimensionSizeOfThis = mapTensorSizeDimensionsOfThis[spaceToFind];
                int dimensionSizeOfInput = mapTensorSizeDimensionsOfInput[spaceToFind];
                if (dimensionSizeOfInput != dimensionSizeOfThis) throw invalid_argument("The dimensional space's size of the second tensor must be equal to that of the same dimensional space of the first tensor");
            }
        }
        

        // ATENZIONE: al momento non funziona perchè torna this e non il tensore risultante, poi sarà corretto il controllo
        return *this;

    }

}