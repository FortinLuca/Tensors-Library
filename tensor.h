#include <iostream>

using namespace std;


// Tensor class definition
namespace Tensor_Library{
    
    template <typename T, int n>
    class RankedTensor {


    private:
        int sizeDimensions[n];
        int n_total_elements;
        int strides[n];
        vector<T> data;


    public:
        // Constructor
        RankedTensor(vector<int> args);


        // Implementation of a constructor with different input parameters by recalling the previous constructor
        template <typename... ints>
        RankedTensor(ints...args) : RankedTensor(vector<int>({args...})){}

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
        RankedTensor<T, n> get();

        int * getSizeDimensions();

        int * getStrides();

        void insertRandomData();

        void printTensor();

    };
        


    // --------------------------------------------------------------
    template <typename T>
    class UnknownRankedTensor {

    private:
        /* data */

        
    public:

        // Constructor
        UnknownRankedTensor();

        // Destructor
        ~UnknownRankedTensor();

    };

}
