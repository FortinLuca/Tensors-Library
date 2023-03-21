#include <iostream>
#include "../tensor.h"


class Solve {
    public:
        void solve() {
            cout << "We're going to solve every tensor!" << endl;
        }
};

int main() {
    vector<int> test = {3, 4, 5};
    //RankedTensor<float, 3> z(test);
    RankedTensor<float, 5> rt(1, 2, 3, 4, 5);

    return 0;
}