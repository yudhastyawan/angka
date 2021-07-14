#include "angka.h"

int main() {
    Vector *vec = Vector_New_Constant(3, 1.);
    Vector_QuickPrint(vec);

    Vector *vec2 = Vector_New_Copy(vec);
    Vector_QuickPrint(vec2);

    Vector_Delete(vec);
    Vector_Delete(vec2);
    return 0;
}