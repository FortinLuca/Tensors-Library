#include "index.h"

namespace TensorIndexes{

    Index::Index(int space){
        this->space = space;
    }
    
    int Index::getSpace() {
        return space;
    }
    
}