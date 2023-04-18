#include "../Methods_library/methods.cpp"


using namespace Tensor_Library;


/*
Temporanea, solo per ripasso funzionamento puntatori/referenze
    int v[] = {1, 2, 3, 4, 5};
    int * elem = &v[0];

    for(int i=0; i<5; i++){
        cout<<elem[i]<<endl;
    }
    cout<<&v[0]<<endl;
*/


int main() {
    // Short example of four tensors with different types but the same dimensions
    vector<int> testvector = {2, 3, 4};

    RankedTensor<float, 3> rt1(testvector);
    RankedTensor<int, 3> rt2(testvector);
    RankedTensor<char, 3> rt3(testvector);
    RankedTensor<double, 3> rt4(testvector);

    /*
    // Printing the sizeDimensions and the strides attribute of the four tensors

    int * sizeDimensions1 = rt1.getSizeDimensions();
    int * sizeDimensions2 = rt2.getSizeDimensions();
    int * sizeDimensions3 = rt3.getSizeDimensions();
    int * sizeDimensions4 = rt4.getSizeDimensions();

    int * strides1 = rt1.getStrides();
    int * strides2 = rt2.getStrides();
    int * strides3 = rt3.getStrides();
    int * strides4 = rt4.getStrides();

    for(int i=0; i<5; i++){
        cout<<to_string(sizeDimensions1[i]) + " "+ to_string(sizeDimensions2[i]) + " "+ to_string(sizeDimensions3[i]) + " "+ to_string(sizeDimensions4[i])<<endl;
    }

    cout<<endl;

    for(int i=0; i<5; i++){
        cout<<to_string(strides1[i]) + " "+ to_string(strides2[i]) + " "+ to_string(strides2[i]) + " "+ to_string(strides2[i])<<endl;
    }
    */

    // for each tensor, it inserts pseudo-randomic elements of the correspondent type and it prints the final (filled) tensors
    rt1.insertRandomData();
    //rt1.printData();

    rt2.insertRandomData();
    rt2.printData();

    rt3.insertRandomData();
    //rt3.printData();

    rt4.insertRandomData();
    //rt4.printData();


    // Extracting a value by using the get methods from a tensor given the vector of indexes
    vector<int> indexesVector = {1, 2, 3};
    //char value = rt3(1, 2, 3);
    //cout<<endl<<"The element from the indexes {1, 2, 3} is ---> "<<+value<<endl<<endl;

    // Trying to use the fix method
    // RankedTensor<int, 2> newTensor1 = rt2.fix(2, 1);
    // newTensor1.printData();
    // newTensor1.printTensor();

    vector<int> minIndexesVector = {0, 1, 0};
    vector<int> maxIndexesVector = {1, 1, 2};

    RankedTensor<int, 3> newTensor2 = rt2.window(minIndexesVector, maxIndexesVector);
    newTensor2.printData();

    RankedTensor<int, 3> newTensor3 = rt2.window_copy(minIndexesVector, maxIndexesVector);
    newTensor3.printData();

    // Testing the flattening methods
    //RankedTensor<int, 1> newTensor4 = rt2.flattening_copy();
    //cout << newTensor4.getSizeDimensions()[0] << endl << endl;

    //newTensor2.printTensor();

    UnknownRankedTensor<int> newTensorA(2, 3, 4);


    RankedTensor<int, 3> prova1(2, 3, 4);
    RankedTensor<int, 3> prova2(2, 3, 4);
    prova1.insertRandomData();
    prova2.insertRandomData();

    prova1.printData();
    prova2.printData();

    RankedTensor<int, 3> aaa = prova1 + prova2;
    aaa.printData();

    RankedTensor<int, 3> bbbb = prova1 + 2;
    bbbb.printData();


    return 0;
}
