#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;


// Tensor class definition
template <typename T, int n>
class RankedTensor {

private:
    vector<int> sizeDimensions;
    vector<int> tensor;


public:
    // Constructor
    RankedTensor(vector<int> args) {
        sizeDimensions = args;
        if(n != args.size()) {
            throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");
        }
        
    }

    template <typename... ints>
    // Constructor
    RankedTensor(ints...args) {
        vector<int> v = {args...};
        /*
        int * elem = &v[0];

        for(int i=0; i<5; i++){
           cout<<elem[i]<<endl; 
        }
        cout<<&v[0]<<endl;
        */
    }

    // Destructor
    ~RankedTensor() = default;

    RankedTensor<T, n> get() {
    }

};





// --------------------------------------------------------------
template <typename T>
class UnknownRankedTensor
{
private:
    /* data */

    
public:

    // Constructor
    UnknownRankedTensor(/* args */) {

    }

    // Destructor
    ~UnknownRankedTensor() {

    }
};

