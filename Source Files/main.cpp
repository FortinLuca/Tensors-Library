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
    // short example of four tensors with different types but the same dimensions
    vector<int> testvector = {2, 3, 4};
    
    RankedTensor<float, 3> rt1(testvector);
    RankedTensor<int, 3> rt2(testvector);
    RankedTensor<char, 3> rt3(testvector);
    RankedTensor<double, 3> rt4(testvector);

    /*    
    // It prints the sizeDimensions and the strides attribute of the four tensors

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
    //rt1.printTensor();

    rt2.insertRandomData();
    rt2.printTensor();

    rt3.insertRandomData();
    //rt3.printTensor();

    rt4.insertRandomData();
    //rt4.printTensor();


    // It extracts a value by using the get methods from a tensor given the vector of indexes
    vector<int> indexesVector = {1, 2, 3};
    //char value = rt3(1, 2, 3);
    //cout<<endl<<"The element from the indexes {1, 2, 3} is ---> "<<+value<<endl<<endl;

    // It tries to use the fix method
    RankedTensor<int, 2> newTensor = rt2.fix(2, 1);
    //newTensor.printTensor();

    auto it = rt2.getIterator();
    while(it.hasNext())
        cout<< it.next() << endl;

    return 0;
}