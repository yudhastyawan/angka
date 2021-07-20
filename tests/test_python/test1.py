import sys
sys.path += ["C:\\Users\\Lenovo\\Documents\\projects\\windows\\angka\\swig"]
from angka import *
mat = agx_matrix_new_random(100, 100, -10., 10.)
agx_matrix_print_partial(mat)
vec = agx_vector_new_from_matrix(mat)
agx_vector_print_partial(vec)
fig = agv_subplots(1,1)
agv_imshow(agv_set_canvas(fig, 0), mat)
agv_show(fig)
agx_matrix_delete(mat)
agx_vector_delete(vec)