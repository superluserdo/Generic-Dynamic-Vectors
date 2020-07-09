#ifndef _VEC_H
#define _VEC_H
void *vec(size_t elem_size, size_t len);
void vec_push_n(void **vecptr, size_t n, void *items);
void vec_push(void **vecptr, void *item);
void vec_pop_n(void **vecptr, size_t n);
void vec_pop(void **vecptr);
void vec_free(void *vector);
size_t vec_elem_size(void *vec);
size_t vec_len(void *vec);
size_t vec_used(void *vec);
#endif
