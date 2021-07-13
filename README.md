# angka
a repository focusing on data processing package namely angka

## Progress Records
### \[7/13/2021\] - create a data type of `Vector`
```c
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
```

the result:
```
3 [-6.76483, -8.21903, 5.01727]
6 [-6.76483, -8.21903, 5.01727, 10.00000, 73.40965, -51.27795]
```
