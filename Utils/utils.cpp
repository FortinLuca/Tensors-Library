#include <type_traits>
#include <random>


using namespace std;


template<typename T>
typename enable_if<is_integral<T>::value, T>::type random(T from, T to) {
    mt19937 mt(time(nullptr)); 

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<T> distr(from, to);
    return distr(generator);
}


template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type random(T from, T to) {
    mt19937 mt(time(nullptr)); 

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<T> distr(from, to);
    return distr(generator);
}