#include "angka.h"

int main() {
    Matrix *mat = Matrix_New_Zero(5, 6);
    Matrix_QuickPrint(mat);
    Matrix_Delete(mat);
    return 0;
}