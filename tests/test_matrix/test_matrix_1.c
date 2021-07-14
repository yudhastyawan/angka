#include "angka.h"

int main() {
    Matrix *mat = Matrix_New_Random(3,4,-10,10);
    // Matrix *mat = Matrix_New_Constant(4,4,10.);
    Matrix_QuickPrint(mat);
    // Matrix_Add_ByValue(mat, 2.);
    Matrix_Transpose(mat);
    Matrix_QuickPrint(mat);

    Matrix *mat2 = Matrix_New_Copy(mat);
    Matrix_QuickPrint(mat2);
    // Double_Print(Matrix_GetItem(mat, 99, 999));
    
    Matrix_Delete(mat);
    Matrix_Delete(mat2);
    return 0;
}