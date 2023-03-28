#include <iostream>
#include <time.h>
#include <random>

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

        static T randomNumber();


    public:
        // Constructor
        RankedTensor(vector<int> args);


        // Implementation of a constructor with different input parameters by recalling the previous constructor
        template <typename... ints>
        RankedTensor(ints...args) : RankedTensor(vector<int>({args...})){}


        // Destructor from defualt
        ~RankedTensor() = default;
        

        //---------------------------------
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
