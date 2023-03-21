#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;


// Tensor class definition
template <typename T, int n>
class RankedTensor {

private:
    int sizeDimensions[n];
    int n_total_elements;
    int strides[n];


public:
    // Constructor
    RankedTensor(vector<int> args) {
        int i;

        if(n != args.size()) {
            throw invalid_argument("The number of space dimensions inserted are not equal to the number of rank");
        }

        n_total_elements = 1;
        for(i = n-1; i >= 0; i--){
            if(args[i] <= 0)
                throw invalid_argument("A dimensional space cannot be zero or less");
            else{
                strides[i] = n_total_elements;

                n_total_elements *= args[i];
                sizeDimensions[i] = args[i];
            }
        }
        
    }


    // Implementation of a constructor with different input parameters by recalling the previous constructor
    template <typename... ints>
    RankedTensor(ints...args) : RankedTensor(vector<int>({args...})) {}
    
    /*
    int * elem = &v[0];

    for(int i=0; i<5; i++){
        cout<<elem[i]<<endl; 
    }
    cout<<&v[0]<<endl;
    */


    // Destructor from defualt
    ~RankedTensor() = default;
    

    //---------------------------------
    //ONLY FOR TESTING
    RankedTensor<T, n> get() {
    }

    int * getSizeDimensions(){
        return sizeDimensions;
    }

    int * getStrides(){
        return strides;
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

