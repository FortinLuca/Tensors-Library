#include "../EinsteinFormalism/operators.cpp"

// Execution line: g++ -std=c++17 -g -Wall -o3 main.cpp -o  main


int main() {

    using namespace operators;
    
    // Short example of four tensors with different types but the same dimension
    vector<int> dimensionsVector = {2, 3, 4};

    UnknownRankedTensor<float> ut1(dimensionsVector);
    UnknownRankedTensor<int> ut2(dimensionsVector);
    RankedTensor<int, 3> rt1(dimensionsVector);
    

    // Printing the sizeDimensions and the strides attribute of the four tensors
    vector<int> sizeDimensions1 = ut1.getSizeDimensions();
    vector<int> sizeDimensions2 = ut2.getSizeDimensions();
    vector<int> sizeDimensions3 = rt1.getSizeDimensions();

    vector<int> strides1 = ut1.getStrides();
    vector<int> strides2 = ut2.getStrides();
    vector<int> strides3 = rt1.getStrides();

    vector<vector<int>> v = {sizeDimensions1, sizeDimensions2, sizeDimensions3};
    vector<vector<int>> s = {strides1, strides2, strides3};

    for (int i =0; i<3; i++) {
        cout << "sizeDimensions" + to_string(i+1) + ":" << endl;
        for (int j=0; j<(int)v[i].size(); j++) {
            cout << to_string(v[i][j]) + " ";
        }

        cout << endl;

        cout << "strides" + to_string(i+1) + ":" << endl;
        for (int j=0; j<(int)s[i].size(); j++) {
            cout<<to_string(s[i][j]) + " ";
        }
    
        cout<<endl<<endl;;
    }


    // For each tensor, it inserts pseudo-randomic elements of the correspondent type and it prints the final (filled) tensors
    ut1.insertRandomData();
    ut1.printTensor();

    ut2.insertRandomData();
    ut2.printTensor();

    rt1.insertRandomData();
    rt1.printTensor();


    // Using of GET and SET methods:
    // extracting a value by using the GET method through OPERATOR "()" given the vector of indexes and from both a RankedTensor and UnknownRankedTensor
    cout << "get(1, 1, 1) = " << ut2(1, 1, 1) << endl;
    ut2.set(100, 1, 1, 1);
    cout << "After setting 100: get(1, 1, 1) = " << ut2(1, 1, 1) << endl << endl;

    cout << "get(1, 1, 1) = " << rt1(1, 1, 1) << endl;
    rt1.set(100, 1, 1, 1);
    cout << "After setting: get(1, 1, 1) = " << rt1(1, 1, 1) << endl << endl << endl;


    // Testing the WINDOW methods for both tensor classes
    vector<int> minIndexesVector = {0, 1, 0};
    vector<int> maxIndexesVector = {1, 1, 2};

    cout << "WINDOWS method:" << endl;
    cout << "minIndexesVector: ";
    for (int i=0; i<(int)minIndexesVector.size(); i++) {
        cout<<minIndexesVector[i] << " "; 
    }
    cout << endl << "maxIndexesVector: ";
    for (int i=0; i<(int)maxIndexesVector.size(); i++) {
        cout<<maxIndexesVector[i] << " "; 
    }
    cout << endl << endl;


    UnknownRankedTensor<int> windowTensorU = ut2.window(minIndexesVector, maxIndexesVector);
    windowTensorU.printData();

    RankedTensor<int, 3> windowTensorR = rt1.window(minIndexesVector, maxIndexesVector);
    windowTensorR.printData();

    UnknownRankedTensor<int> windowCopyTensorU = ut2.window_copy(minIndexesVector, maxIndexesVector);
    windowCopyTensorU.printData();

    RankedTensor<int, 3> windowCopyTensorR = rt1.window_copy(minIndexesVector, maxIndexesVector);
    windowCopyTensorR.printData();


    // Testing the FLATTENING methods for both tensor classes
    cout << endl << "FLATTENING method:" << endl;
    UnknownRankedTensor<int> flatteningTensorU = ut2.flattening();
    flatteningTensorU.printTensor();

    RankedTensor<int, 1> flatteningTensorR = rt1.flattening();
    flatteningTensorR.printTensor();

    UnknownRankedTensor<int> flatteningCopyTensorU = ut2.flattening_copy();
    flatteningCopyTensorU.printTensor();

    RankedTensor<int, 1> flatteningCopyTensorR = rt1.flattening_copy();
    flatteningCopyTensorR.printTensor();


    // Testing the FIX method for both tensor classes
    cout << endl << "FIX method:" << endl;
    UnknownRankedTensor<int> fixTensorU = ut2.fix(1, 2);
    fixTensorU.printData();

    RankedTensor<int, 2> fixTensorR = rt1.fix(1, 2);
    fixTensorR.printData();

    UnknownRankedTensor<int> fixCopyTensorU = ut2.fix_copy(1, 2);
    fixCopyTensorU.printData();

    RankedTensor<int, 2> fixCopyTensorR = rt1.fix_copy(1, 2);
    fixCopyTensorR.printData();


    cout << "------------------------------------------------------------------------" << endl;


    // Testing the methods for class ITERATOR for both tensor classes
    cout << endl << "ITERATOR methods:" << endl;
    UnknownRankedTensor<int> iteratorTensorU(2, 3, 4);
    iteratorTensorU.insertRandomData();
    iteratorTensorU.printData();

    RankedTensor<int, 3> iteratorTensorR(2, 3, 4);
    iteratorTensorR.insertRandomData();
    iteratorTensorR.printData();


    // Using of method "getIterator" to print the whole tensor data for both tensor classes
    TensorIterator<int> it1 = iteratorTensorU.getIterator();
    while(it1.hasNext()){
       cout << it1.next() << " ";
    }
    cout << endl << endl;

    TensorIterator<int> it2 = iteratorTensorR.getIterator();
    while(it2.hasNext()){
       cout << it2.next() << " ";
    }
    cout << endl << endl;

    // Using of method "getIterator" to print the data along only one index by keeping fixed the others for both tensor classes
    TensorIterator<int> it3 = iteratorTensorU.getIterator(1, {1, 0});
    while(it3.hasNext()){
       cout << it3.next() << " ";
    }
    cout << endl << endl;

    TensorIterator<int> it4 = iteratorTensorR.getIterator(1, {1, 0});
    while(it4.hasNext()){
       cout << it4.next() << " ";
    }
    cout << endl << endl;


    cout << "------------------------------------------------------------------------" << endl;

    // SUM:
    // testing the SUM operation for both tensor classes
    cout << endl << "SUM operation:" << endl;
    cout << "Addends:" << endl;
    UnknownRankedTensor<int> sumTensor1(4, 4, 4);
    sumTensor1.insertRandomData();
    sumTensor1.printData();

    UnknownRankedTensor<int> sumTensor2(4, 4, 4);
    sumTensor2.insertRandomData();
    sumTensor2.printData();

    RankedTensor<int, 3> sumTensor3(4, 4, 4);   //in this case we use a Rankedtensor unlike the previous two
    sumTensor3.insertRandomData();
    sumTensor3.printData();

    // Defining the Indexes
    Index i(0);
    Index j(1);
    Index k(2);
    Index w(3);
    Index z(4);
    Index f(5);

    TensorWithIndexes<int> sumTensor1WithIndexes = sumTensor1({i, j, k});
    TensorWithIndexes<int> sumTensor2WithIndexes = sumTensor2({i, j, k});
    TensorWithIndexes<int> sumTensor3WithIndexes = sumTensor3({i, j, k});

    TensorWithIndexes<int> sumFinalTensor = sumTensor1WithIndexes + sumTensor2WithIndexes + sumTensor3WithIndexes;
    cout << "Sum result:" << endl;
    sumFinalTensor.getTensor().printData();
    

    // PRODUCT:
    // Testing the PRODUCT operation for both tensor classes (through the EINSTEIN FORMALISM)
    cout << endl << "PRODUCT operation:" << endl;
    cout << "Factors:" << endl;
    UnknownRankedTensor<int> productTensor1(4, 3, 4, 4);
    productTensor1.insertRandomData();

    UnknownRankedTensor<int> productTensor2(4, 4, 4);
    productTensor2.insertRandomData();

    RankedTensor<int, 2> productTensor3(7, 3);  //in this case we use a Rankedtensor unlike the previous two
    productTensor3.insertRandomData();

    UnknownRankedTensor<int> productTensor4(3, 4, 4);
    productTensor4.insertRandomData();

    // Creation of TensorWithIndexes starting from an UnknownRankedTensor or RankedTensor
    TensorWithIndexes<int> productTensor1WithIndexes = productTensor1({i, j, k, w});
    productTensor1WithIndexes.getTensor().printData();

    TensorWithIndexes<int> productTensor2WithIndexes = productTensor2({i, k, z});
    productTensor2WithIndexes.getTensor().printData();

    TensorWithIndexes<int> productTensor3WithIndexes = productTensor3({f, j});
    productTensor3WithIndexes.getTensor().printData();


    MultiplierTensor<int> multiplierTensor = productTensor1WithIndexes * productTensor2WithIndexes * productTensor3WithIndexes;
    TensorWithIndexes<int> productFinalTensor = multiplierTensor.applyProduct();
    cout << "Product result:" << endl;
    productFinalTensor.getTensor().printData();


    // testing the PRODUCT operation for the TRACE case that returns a tensor with one element
    cout << "Factors:" << endl;
    productTensor1WithIndexes.getTensor().printData();
    productTensor2WithIndexes.getTensor().printData();
    TensorWithIndexes<int> productTensor4WithIndexes = productTensor4({j, w, z});
    productTensor4WithIndexes.getTensor().printData();

    MultiplierTensor<int> multiplierTensorForTrace = productTensor1WithIndexes * productTensor2WithIndexes * productTensor4WithIndexes;
    TensorWithIndexes<int> productFinalTensorForTrace = multiplierTensorForTrace.applyProduct();
    cout << "Product result:" << endl;
    productFinalTensorForTrace.getTensor().printData();


    return 0;
}
