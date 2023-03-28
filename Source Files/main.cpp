#include "../Methods_library/methods.cpp"


using namespace Tensor_Library;


 /*
 temporanea, solo per ripasso funzionamento puntatori/referenze
        int * elem = &v[0];

        for(int i=0; i<5; i++){
            cout<<elem[i]<<endl; 
        }
        cout<<&v[0]<<endl;
*/


int main() {
    srand(time(NULL));

    // little example with four tensors with different numeric types but with the same rimensions
    vector<int> testvector = {1, 2, 3, 4, 5};
    
    RankedTensor<float, 5> rt1(testvector);
    RankedTensor<int, 5> rt2(testvector);
    RankedTensor<char, 5> rt3(testvector);
    RankedTensor<double, 5> rt4(testvector);

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

    // For each tensor, it insert randomically elements of the correspondents type and it prints the filled tensors
    rt1.insertRandomData();
    rt1.printTensor();

    rt2.insertRandomData();
    rt2.printTensor();

    rt3.insertRandomData();
    rt3.printTensor();

    rt4.insertRandomData();
    rt4.printTensor();


    // It extract a value by using the get methods from a tensor
    vector<int> testvector2 = {0, 1, 1, 2, 3};
    cout<<endl<<rt1.get(testvector2)<<endl;

    
    return 0;
}