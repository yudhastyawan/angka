#include "angka.h"

int main() {
    Matrix *mat = Matrix_New_Random(3,4,-10,10);
    Matrix_Print(mat, TRUE);
    
    Matrix_Delete(mat);
    return 0;
}