#ifndef _VEC_H
#define _VEC_H
void *vec(int elem_size, int len);
void vec_push(void **vecptr);
void vec_pop(void **vecptr);
void vec_free(void *vector);
int vec_elem_size(void *vec);
int vec_len(void *vec);
int vec_used(void *vec);
#endif
