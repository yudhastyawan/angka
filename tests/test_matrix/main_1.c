#include "angka.h"

int main() {
    matrix *mat = getMatrixNewConstant(4, 5, 2.);
    getMatrixPrintQuick(mat);

    getMatrixTranspose(mat);
    getMatrixPrintQuick(mat); 

    getMatrixDelete(mat);
    return 0;
}