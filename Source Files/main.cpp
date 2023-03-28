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

    vector<int> testvector = {1, 2, 3, 4, 5};
    
    RankedTensor<float, 5> rt1(testvector);
    RankedTensor<int, 5> rt2(testvector);
    RankedTensor<char, 5> rt3(testvector);
    RankedTensor<double, 5> rt4(testvector);

    /*    
    // RankedTensor<float, 5> rt2(1, 2, 3, 4, 5);

    int * sizeDimensions1 = rt1.getSizeDimensions();
    int * sizeDimensions2 = rt2.getSizeDimensions();

    int * strides1 = rt1.getStrides();
    int * strides2 = rt2.getStrides();

    for(int i=0; i<5; i++){
        cout<<to_string(sizeDimensions1[i]) + " "+ to_string(sizeDimensions2[i])<<endl;
    }

    cout<<endl;

    for(int i=0; i<5; i++){
        cout<<to_string(strides1[i]) + " "+ to_string(strides2[i])<<endl;
    }
    */

    rt1.insertRandomData();
    rt1.printTensor();

    rt2.insertRandomData();
    rt2.printTensor();

    rt3.insertRandomData();
    rt3.printTensor();

    rt4.insertRandomData();
    rt4.printTensor();

    
    return 0;
}