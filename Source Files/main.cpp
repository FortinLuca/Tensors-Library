#include <iostream>
#include "../tensor.h"


class Solve {
    public:
        void solve() {
            cout << "We're going to solve every tensor!" << endl;
        }
};

int main() {
    vector<int> testvector = {1, 2, 3, 4, 5};
    
    RankedTensor<float, 5> rt1(testvector);
    RankedTensor<float, 5> rt2(1, 2, 3, 4, 5);

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


    return 0;
}