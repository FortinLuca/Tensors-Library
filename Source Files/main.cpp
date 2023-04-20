#include "../tensors.cpp"


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

    UnknownRankedTensor<float> rt1(testvector);
    UnknownRankedTensor<int> rt2(testvector);
    UnknownRankedTensor<char> rt3(testvector);
    UnknownRankedTensor<double> rt4(testvector);

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


    // Window method
    vector<int> minIndexesVector = {0, 1, 0};
    vector<int> maxIndexesVector = {1, 1, 2};

    UnknownRankedTensor<int> newTensor2 = rt2.window(minIndexesVector, maxIndexesVector);
    newTensor2.printData();

    UnknownRankedTensor<int> newTensor3 = rt2.window_copy(minIndexesVector, maxIndexesVector);
    newTensor3.printData();


    // Testing the flattening methods
    UnknownRankedTensor<int> newTensor4 = rt2.flattening_copy();
    newTensor4.printTensor();

    UnknownRankedTensor<int> newTensor5 = rt2.flattening();
    newTensor5.printTensor();

    // Get and set methods
    cout << "get(1, 1, 1) = " << rt2(1, 1, 1) << endl;
    rt2.set(100, 1, 1, 1);
    cout << "After setting 100: get(1, 1, 1) = " << rt2(1, 1, 1) << endl << endl;

    
    UnknownRankedTensor<int> prova1(2, 3, 4);
    UnknownRankedTensor<int> prova2(2, 3, 4);
    prova1.insertRandomData();
    prova2.insertRandomData();

    prova1.printData();
    prova2.printData();


    // Iterators
    TensorIterator<int> it1 = prova2.getIterator();
    while(it1.hasNext()){
       cout << it1.next() << " ";
    }
    cout << endl;

    TensorIterator<int> it2 = prova2.getIterator(1, 2);
    while(it2.hasNext()){
       cout << it2.next() << " ";
    }
    cout << endl;

    // Fix method
    UnknownRankedTensor<int> aa = prova2.fix(1, 2);
    aa.printData();

    // Adding
    prova1 = prova1 + prova2;
    prova1.printData();


    cout << "------------------------------------------------------------------------"<< endl;

    // RankedTensor example with printData and printTensor
    RankedTensor<int, 3> nrt1(2, 3, 4);
    nrt1.insertRandomData();
    nrt1.printData();

    RankedTensor<int, 3> nrt2(2, 3, 4);
    nrt2.insertRandomData();
    nrt2.printData();

    nrt1.printTensor();


    // Get and Set methods
    cout << "get(1, 1, 1) = " << nrt1(1, 1, 1) << endl;
    nrt1.set(100, 1, 1, 1);
    cout << "After setting: get(1, 1, 1) = " << nrt1(1, 1, 1) << endl << endl;


    // Flattening methods
    RankedTensor<int, 1> nrt4 = nrt1.flattening();
    nrt4.printTensor();
    nrt4 = nrt1.flattening_copy();
    nrt4.printTensor();


    //Fix methods
    RankedTensor<int, 2> nrt3 = nrt1.fix(1, 1);
    nrt1.printData();
    nrt3.printData();
    nrt3 = nrt1.fix_copy(1, 1);
    nrt3.printData();


    // Windows methods
    RankedTensor<int, 3> nrt5 = nrt1.window({0, 1, 0}, {1, 1, 2});
    nrt1.printData();
    nrt5.printData();

    nrt5 = nrt1.window_copy({0, 1, 0}, {1, 1, 2});
    nrt1.printData();
    nrt5.printData();


    // Adding operation
    //nrt1.printData();
    //nrt2.printData();
    //nrt1 = nrt1 + nrt2;
    //nrt1.printData();
    

    return 0;
}
