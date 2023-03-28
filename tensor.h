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
        /** Constructor
        * @tparam ssss */
        RankedTensor(vector<int> sizes);


        // Implementation of a constructor with different input parameters by recalling the previous constructor
        template <typename... ints>
        RankedTensor(ints...sizes) : RankedTensor(vector<int>({sizes...})){}


        // Destructor from defualt
        ~RankedTensor() = default;
        

        //---------------------------------
        T get(vector<int> indexes);

        //template <typename... ints>
        //get(ints...indexes) : get(vector<int>({indexes...})){}


        /** GetSizeDimensions
        * @tparam ssss 
        * @return aaa */
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
