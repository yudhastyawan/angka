#include "angka.h"

int main() {
    Matrix *mat = Matrix_New_Constant(5, 10, 3.);
    Matrix_QuickPrint(mat);
    Matrix_SetItem(mat, 1, 1, 5.);
    Matrix_QuickPrint(mat);

    Matrix_Transpose(mat);
    Matrix_QuickPrint(mat);

    Matrix_Delete(mat);
    return 0;
}