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

        //multiplierTensor = MultiplierTensor<T>();
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


    /*
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

        vector<int>::iterator it;
        vector<int> equalSpaces;
        vector<int> equalSizeDimensions;
        vector<int> differentSpaces;

        for(int i = 0; i<sizeOfInput; i++) {
            // through the two support maps, we check the two sizeDimensions's equality of the same dimensional space
            int spaceKey = spacesOfInput_int[i];
            it = find(spacesOfThis_int.begin(), spacesOfThis_int.end(), spaceKey);
            if (it != spacesOfThis_int.end()) {
                int dimensionSizeOfThis = mapTensorSizeDimensionsOfThis.at(spaceKey);
                int dimensionSizeOfInput = mapTensorSizeDimensionsOfInput.at(spaceKey);
                if (dimensionSizeOfInput != dimensionSizeOfThis) throw invalid_argument("The dimensional space's size of the first tensor must be equal to that of the same dimensional space of the second tensor");
                equalSpaces.push_back(spaceKey);
                equalSizeDimensions.push_back(dimensionSizeOfInput);

            }
        }

        differentSpaces.assign(spacesOfThis_int.begin(), spacesOfThis_int.end());
        differentSpaces.insert(differentSpaces.end(), spacesOfInput_int.begin(), spacesOfInput_int.end());

        bool isPresentEqualSpace = true;
        vector<int>::iterator it_positionToErase;
        for (int i = 0; i < (int)equalSpaces.size(); i++) {
            int equalSpace = equalSpaces[i];
            if (count(differentSpaces.begin(), differentSpaces.end(), equalSpace) > 1) {
                while (isPresentEqualSpace) {
                    it_positionToErase = find(differentSpaces.begin(), differentSpaces.end(), equalSpace);
                    differentSpaces.erase(it_positionToErase);
                    if (count(differentSpaces.begin(), differentSpaces.end(), equalSpace) == 0) {
                        isPresentEqualSpace = false;
                    }
                }
                isPresentEqualSpace = true;
            }
            
        }
        

        int dimensionMultiplierTrace = 1;
        vector<int> vectorResultTensorSizeDimensions((int)differentSpaces.size());
        for (int i = 0; i < (int)differentSpaces.size(); i++) {
            if (mapTensorSizeDimensionsOfThis.find(differentSpaces[i]) != mapTensorSizeDimensionsOfThis.end()) {
                dimensionMultiplierTrace *= mapTensorSizeDimensionsOfThis[differentSpaces[i]];
                vectorResultTensorSizeDimensions[i] = mapTensorSizeDimensionsOfThis.at(differentSpaces[i]);
            } else {
                dimensionMultiplierTrace *= mapTensorSizeDimensionsOfInput[differentSpaces[i]];
                vectorResultTensorSizeDimensions[i] = mapTensorSizeDimensionsOfInput.at(differentSpaces[i]);
            }
        }

        map<int, int> mapCommonIndexes;
        vector<int> vectorCommonIndexes; 
        for (int i=0; i<sizeOfThis; i++) {
            if (tensorWithIndexes.multiplierTensor.mapOfSpacesAndDimensions.count(spacesOfThis_int[i]) > 0) {
                mapCommonIndexes[spacesOfThis_int[i]] = tensorSizeDimensionsOfThis[i];
                vectorCommonIndexes.push_back(spacesOfThis_int[i]);
            }
        }
        for (int i=0; i<sizeOfInput; i++) {
            if (this->multiplierTensor.mapOfSpacesAndDimensions.count(spacesOfInput_int[i]) > 0) {
                mapCommonIndexes[spacesOfInput_int[i]] = tensorSizeDimensionsOfInput[i];
                vectorCommonIndexes.push_back(spacesOfInput_int[i]);
            }
        }

        map<int,int> mapOfEqualSpaces;
        vector<int> vectorOfEqualSpaces;
        for (int i = 0; i < (int)equalSpaces.size(); i++) {
            mapOfEqualSpaces[equalSpaces[i]] = equalSizeDimensions[i];
            vectorOfEqualSpaces.push_back(equalSpaces[i]);
        }

        mapCommonIndexes.insert(mapOfEqualSpaces.begin(), mapOfEqualSpaces.end());
        vectorCommonIndexes.insert(vectorCommonIndexes.end(), vectorOfEqualSpaces.begin(), vectorOfEqualSpaces.end());
        

        vector<Index> differentIndexes;
        for(int i=0; i<sizeOfThis; i++){
            if(mapOfEqualSpaces.count(spacesOfThis_int[i]) == 0)
                differentIndexes.push_back(this->getSpaces()[i]);
        }
        
        for(int i=0; i<sizeOfInput; i++){
            if(mapOfEqualSpaces.count(spacesOfInput_int[i]) == 0)
                differentIndexes.push_back(tensorWithIndexes.getSpaces()[i]);
        }

        // cout << "--------------------------------------------" << endl;
        // UnknownRankedTensor<T> supp = UnknownRankedTensor<T>(this->getTensor());
        // for (map<int, int>::iterator it = mapCommonIndexes.begin(); it != mapCommonIndexes.end(); it++) {
        //     int indexOfCycle = 0;
        //     int space = it -> first;
        //     int sizeDimension = it->second;

        //     std::vector<int>::iterator itr = find(spacesOfThis_int.begin(), spacesOfThis_int.end(), space);
        //     int spacePositionThis = distance(spacesOfThis_int.begin(), itr);

        //     itr = find(spacesOfInput_int.begin(), spacesOfInput_int.end(), space);
        //     int spacePositionInput = distance(spacesOfInput_int.begin(), itr);

        //     vector<vector<T>> totalDataThis;
        //     vector<vector<T>> totalDataInput;

        //     for(int i = 0; i < sizeDimension; i++){
        //         UnknownRankedTensor<T> prodThis = supp.fix_copy(spacePositionThis, i);
        //         UnknownRankedTensor<T> prodInput = tensorWithIndexes.getTensor().fix_copy(spacePositionInput, i);

        //         if(i == 0){
        //             totalDataThis.resize(prodThis.get_n_total_elements(), vector<T>(sizeDimension));
        //             totalDataInput.resize(prodInput.get_n_total_elements(), vector<T>(sizeDimension));
        //         }

        //         shared_ptr<vector<T>> dataThis = prodThis.getData();
        //         shared_ptr<vector<T>> dataInput = prodInput.getData();

        //         for(int j = 0; j < prodThis.get_n_total_elements(); j++){
        //             T elem = dataThis->at(j);
        //             totalDataThis[j][i]=elem;
        //         }

        //         for(int j = 0; j < prodInput.get_n_total_elements(); j++){
        //             T elem = dataInput->at(j);
        //             totalDataInput[j][i]=elem;
        //         }
                
        //     }
        //     vector<T> prodVector;
        //     int ris;
        // }

        return NULL;

    }
    */

}