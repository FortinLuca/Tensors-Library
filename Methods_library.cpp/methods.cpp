#include "../tensor.h"
#include "Utils/utils.cpp"

/*
namespace Tensor_Library{

    RankedTensor::RankedTensor(){
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


    int * RankedTensor::getSizeDimensions(){
        return sizeDimensions;
    }


    int * RankedTensor::getStrides(){
        return strides;
    }


    void * RankedTensor::insertRandomData(T from, T to){
        int i;

        if(!is_integral<T>::value && !is_floating_point<T>::value)
            throw runtime_error("This type is not managed by the Tensor library"); 

        for (i = 0; i < n_total_elements; i++){
            T rnd = random(from, to);
            data.insert(data.begin(), rnd);

        }
    }


    void RankedTensor::printTensor(){
        for_each(data.begin(), data.end(), [] (const float c) {cout << c << " ";} );
        cout<<endl<<endl;
    }


}

*/