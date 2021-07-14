#include "angka.h"

int main() {
    Vector *vec = Vector_New_Constant(3, 1.);
    Vector_QuickPrint(vec);

    Vector_Add_ByValue(vec, 2.);
    Vector_QuickPrint(vec);

    Vector_Substract_ByValue(vec, 2.);
    Vector_QuickPrint(vec);

    Vector_Multiply_ByValue(vec, 2.);
    Vector_QuickPrint(vec);

    Vector_Devide_ByValue(vec, 2.);
    Vector_QuickPrint(vec);

    Vector_Delete(vec);
    return 0;
}