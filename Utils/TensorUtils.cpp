#include "../RankedTensor.cpp"


namespace Tensor_Library{

    // UnknownRankedTensor methods used for testing 

    template <typename T>
    T UnknownRankedTensor<T>::randomNumber() {

        // Computation of the limits of datatype T
        T from = numeric_limits<T>::lowest();
        T to = numeric_limits<T>::max();

        // Reduction of the range from -1000 to 1000 only for non-char elements (because the maximum char's range is lower)
        if constexpr(!(is_same_v<char, T> || is_same_v<signed char, T> || is_same_v<unsigned char, T>)){
            // There exist situations in which the value is inside the range, so we have to make a check before changing the range
            if(from < -1000) from = -1000;
            if(to > 1000) to = 1000;
        }   

        // Setting a 32-bit pseudo-randomic number generator using the Mersenne algorithm (which we haven't studied)
        // It's better than rand() because it produces random sequence much longer to repeat itself
        mt19937 mt(time(nullptr));

        // Uniformly-distributed integer random number generator that produces non-deterministic random numbers
        random_device rand_dev;

        // Creating a generator which produces pseudo-randomic numbers and we'll use it for the uniform distribution
        mt19937 generator(rand_dev());

        // If the type is integral (int, char, long int, ...), we use the discrete uniform distribution and the generator previously implemented
        if constexpr(is_integral_v<T>){
            uniform_int_distribution<T> distr(from, to);
            return distr(generator);
        }
        // If the type is floating point (float, double, ...), we use the continuous uniform distribution
        else if constexpr(is_floating_point_v<T>){
            uniform_real_distribution<T> distr(from, to);
            return distr(generator);
        }
        // Otherwise we throw an exception because we don't manage this new different type T for this method
        else throw runtime_error("This type is not managed by the Tensor library");
    }


    template <typename T>
    void UnknownRankedTensor<T>::insertRandomData(){
        int i;
        data = make_shared<vector<T>>(n_total_elements);

        // Insertion random elements of type T only for arithmetic types (numeric types), otherwise we throw an exception 
        if constexpr(is_arithmetic_v<T>){
            // Inserting always n_total_element elements
            for (i = 0; i < n_total_elements; i++){
                T rnd = randomNumber();
                data->at(i) = rnd;
            }
        } else throw runtime_error("This type is not managed by the Tensor library"); 
    }



    template <typename T>
    void UnknownRankedTensor<T>::printData(){
        if(rank > 0){
            TensorIterator<T> it = getIterator();
            while(it.hasNext())
                cout<< it.next() << " ";
        }
        else{
            cout << data->at(0) << endl;
        }
            
        cout<<endl<<endl;
    }


    template <typename T>
    void UnknownRankedTensor<T> ::printTensor(){
        
        // Printing the dimensions of the tensor
        cout << "Tensor's dimensions: ";
        for(int i = 0; i < rank; i++){
            cout << sizeDimensions[i];
            if(i < rank-1)
                cout << " x ";
            else 
                cout << endl;
        }
        
        
        // Printing the strides
        cout << "Tensor's strides: ";
        for(int i = 0; i < rank; i++){
            cout << strides[i];
            if(i < rank-1)
                cout << " x ";
            else 
                cout << endl;
        }

        // Printing the total number of element of the tensor
        cout << "Total number of element of the tensor: " << n_total_elements << endl;

        // Printing the tensor's data
        cout << "Tensor's data: ";
        printData();
        cout << endl;
    }



    // ***************************************************************************
    // RankedTensor methods used for testing are inherited from UnknownRankedTensor

}