#include "operators.h"

namespace operators{

    template <typename T>
    TensorWithIndexes<T> operator +(TensorWithIndexes<T> tensorWithIndexes1, TensorWithIndexes<T> tensorWithIndexes2) {

        // We retrieve the spaces (indexes) and relative size of "this" (first tensor before the operator *) and the parameter of input "tensorWithIndexes" (second tensor after the operator *)
        // from now on the first tensor is related to the key word "this" and the second tensor is related to the key word "input"
        vector<Index> spaces1 = tensorWithIndexes1.getSpaces();
        vector<Index> spaces2 = tensorWithIndexes2.getSpaces();
        int size1 = spaces1.size();
        int size2 = spaces2.size();

        // Checking the ranks of the tensors to sum
        if(size1 != size2) throw invalid_argument("The tensors for algebraic sums must be with the same rank");

        vector<int> sizeDimensions1 = tensorWithIndexes1.getTensor().getSizeDimensions();
        vector<int> sizeDimensions2 = tensorWithIndexes2.getTensor().getSizeDimensions();

        // Checking the order of the indexes and their dimensionality
        for(int i = 0; i < size1; i++){
            if(spaces1[i].getSpace() != spaces2[i].getSpace()) 
                throw invalid_argument("The tensors must have the same spaces in the same order for the application of the algebraic sum");
            
            if(sizeDimensions1[i] != sizeDimensions2[i])
                throw invalid_argument("The tensors must have the same sizeDimensions value in the same order fot the application of the algebraic sum");

        }

        // Creating a new data vector and a new tensor
        int n_total_elements = tensorWithIndexes1.getTensor().get_n_total_elements();
        shared_ptr<vector<T>> newData = make_shared<vector<T>>(n_total_elements);

        // Creating the two iterators
        TensorIterator<T> it1 = tensorWithIndexes1.getTensor().getIterator();
        TensorIterator<T> it2 = tensorWithIndexes2.getTensor().getIterator();
        int index = 0;

        // Since there are the same dimensions, the iterators iterates in the same number of steps
        while(it1.hasNext() && it2.hasNext()){         
            T elem1 = it1.next();
            T elem2 = it2.next();
            newData->at(index) = elem1 + elem2;
            index++;
        }

        // Inserting the new pointer of data and returning the current tensor
        tensorWithIndexes1.getTensor().setData(newData);
        
        // Returning the final result
        return tensorWithIndexes1;    
    }



    template <typename T>
    MultiplierTensor<T> operator*(TensorWithIndexes<T> tensorWithIndexes1, TensorWithIndexes<T> tensorWithIndexes2){
        // we retrieve the spaces (indexes) and relative size of "this" (first tensor before the operator *) and the parameter of input "tensorWithIndexes" (second tensor after the operator *)
        // from now on the first tensor is related to the key word "this" and the second tensor is related to the key word "input"
        vector<Index> spaces1 = tensorWithIndexes1.getSpaces();
        vector<Index> spaces2 = tensorWithIndexes2.getSpaces();
        int size1 = spaces1.size();
        int size2 = spaces2.size();

        // we retrieve the vectors containing the sizeDimensions of this tensor and input tensor and the relative sizes of the both vectors
        vector<int> tensorSizeDimensions1 = tensorWithIndexes2.getTensor().getSizeDimensions();
        vector<int> tensorSizeDimensions2 = tensorWithIndexes1.getTensor().getSizeDimensions();
        int sizeTensorSizeDimensions1 = tensorSizeDimensions2.size();
        int sizeTensorSizeDimensions2 = tensorSizeDimensions1.size();

        // creation of support vectors of integer "spaces1_int" and "spaces2_int" where the elements are the mapped values of the respective vectors of Index "spaces1" and "spaces2"
        // in this way we exploit the vector iterator function find() to make all more readble
        vector<int> spaces1_int = vector<int>(size1);
        for(int i=0; i<size1; i++) {
            spaces1_int[i]=spaces1[i].getSpace();
        }

        vector<int> spaces2_int = vector<int>(size2);
        for(int i=0; i<size2; i++) {
            spaces2_int[i]=spaces2[i].getSpace();
        }

        // creation of support maps "mapTensorSizeDimensions1" and "mapTensorSizeDimensions2" with key equal to the dimensional space (index) of the relative tensorWithIndexes and value equal to its sizeDimension (corresponding to that dimensional space) 
        map<int, int> mapTensorSizeDimensions1;
        map<int, int> mapTensorSizeDimensions2;
        for (int i = 0; i<sizeTensorSizeDimensions1; i++) {
            mapTensorSizeDimensions1[spaces1_int[i]] = tensorSizeDimensions1[i];
        }

        for (int i = 0; i<sizeTensorSizeDimensions2; i++) {
            mapTensorSizeDimensions2[spaces2_int[i]] = tensorSizeDimensions2[i];
        }

        vector<int>::iterator it;
        vector<int> equalSpaces;
        vector<int> equalSizeDimensions;
        vector<int> differentSpaces;

        for(int i = 0; i<size2; i++) {
            // through the two support maps, we check the two sizeDimensions's equality of the same dimensional space
            int spaceKey = spaces2_int[i];
            it = find(spaces1_int.begin(), spaces1_int.end(), spaceKey);
            if (it != spaces1_int.end()) {
                int dimensionSize1 = mapTensorSizeDimensions1.at(spaceKey);
                int dimensionSize2 = mapTensorSizeDimensions2.at(spaceKey);
                if (dimensionSize2 != dimensionSize1) throw invalid_argument("The dimensional space's size of the first tensor must be equal to that of the same dimensional space of the second tensor");
                equalSpaces.push_back(spaceKey);
                equalSizeDimensions.push_back(dimensionSize2);

            }
        }

        differentSpaces.assign(spaces1_int.begin(), spaces1_int.end());
        differentSpaces.insert(differentSpaces.end(), spaces2_int.begin(), spaces2_int.end());

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
            if (mapTensorSizeDimensions1.find(differentSpaces[i]) != mapTensorSizeDimensions1.end()) {
                dimensionMultiplierTrace *= mapTensorSizeDimensions1[differentSpaces[i]];
                vectorResultTensorSizeDimensions[i] = mapTensorSizeDimensions1.at(differentSpaces[i]);
            } else {
                dimensionMultiplierTrace *= mapTensorSizeDimensions2[differentSpaces[i]];
                vectorResultTensorSizeDimensions[i] = mapTensorSizeDimensions2.at(differentSpaces[i]);
            }
        }


        MultiplierTensor<T> temp = MultiplierTensor<T>();

        return temp;
    }
}