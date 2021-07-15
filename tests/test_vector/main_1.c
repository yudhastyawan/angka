#include "angka.h"

int main() {
    vector *vec = getVectorNewConstant(10, 4.);
    getVectorPrintQuick(vec);

    getVectorAddByValue(vec, 2.);
    getVectorPrintFull(vec);

    getVectorMultiplyByValue(vec, 2.);
    getVectorPrintQuick(vec);

    getVectorAppendValue(vec, 10.);
    getVectorPrintQuick(vec);

    vector *vec_another = getVectorNewCopy(vec);
    getVectorChangeAllElementsByValue(vec_another, 1.5);
    getVectorAppendVector(vec, vec_another);
    getVectorPrintQuick(vec);

    vector *vec_zero = getVectorNewZero(4);
    getVectorSetItem(vec_zero, 1, 4.);
    getVectorPrintQuick(vec_zero);

    getVectorDelete(vec);
    getVectorDelete(vec_another);
    getVectorDelete(vec_zero);
    return 0;
}