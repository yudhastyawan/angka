#include "angka.h"

int main() {
    Vector *vec = Vector_New_Random(3, -10., 10.);
    Vector *vec_another = Vector_New_Random(2, -100., 100.);

    Vector_Print(vec, 0);
    
    Vector_Append_Value(vec, 10.);
    Vector_Append_Vector(vec, vec_another);
    
    Vector_Print(vec, 1);
    
    Vector_Delete(vec);
    Vector_Delete(vec_another);
    return 0;
}