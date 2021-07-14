#include "angka.h"

int main() {
    Vector *vec = Vector_New_Random(5, -10., 10.);
    // Vector *vec = Vector_New_Constant(5, 10.);
    Vector_LongPrint(vec);

    Matrix *mat = Matrix_New_FromVector(vec);
    Matrix_LongPrint(mat);

    Matrix_Transpose(mat);
    Matrix_LongPrint(mat);

    Matrix *identity = Matrix_New_Identity(100);
    Matrix_QuickPrint(identity);

    Matrix *mat2 = Matrix_New_Constant(10, 10, 0.);
    Matrix_QuickPrint(mat2);
    Matrix_Delete(mat2);

    Vector_Delete(vec);
    Matrix_Delete(mat);
    Matrix_Delete(identity);
    return 0;
}