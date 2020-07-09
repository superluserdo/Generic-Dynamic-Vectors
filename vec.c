#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vec.h>

#define FILEINFO fprintf(stderr, "In %s, line %d\n", __FILE__, __LINE__);
#define VEC_RESIZE_MULTIPLIER 2

enum vector_e { START=-3, ELEM_SIZE=-3, LEN=-2, USED=-1, DATA=0};

void *vec(int elem_size, int len) {
	int *ptr = malloc((sizeof(int)) * 3 + elem_size*len);
	ptr = &ptr[3];
	ptr[ELEM_SIZE] = elem_size;
	ptr[LEN] = len;
	ptr[USED] = 0;
	memset(&ptr[DATA], 0, elem_size*len);
	return (void *)ptr;
}

int vec_elem_size(void *vec) {
	int *ptr = vec;
	return ptr[ELEM_SIZE];
}

int vec_len(void *vec) {
	int *ptr = vec;
	return ptr[LEN];
}

int vec_used(void *vec) {
	int *ptr = vec;
	return ptr[USED];
}

void vec_push(void **vecptr) {

	int *vec = (int *)*vecptr;

	/* Resize vector if we have run out of space */
	if (vec[USED] == vec[LEN]) {
		vec = realloc(&vec[START], vec[ELEM_SIZE]*vec[LEN]*VEC_RESIZE_MULTIPLIER + 3*sizeof(int));
		if (!vec) {
			fprintf(stderr, "Can't realloc vector\n");
			FILEINFO
			abort();
		}
		vec = &vec[3]; // Make vec point to start of data
		vec[LEN] *= VEC_RESIZE_MULTIPLIER; // Expand listed size
	}

		vec[USED]++; // Increase "used" count
		*vecptr = (void *)vec;
}

void vec_pop(void **vecptr) {
	int *vec = (int *)*vecptr;

	/* Free vector if we are popping the only remaining element */
	if (vec[USED] > 0) {
		vec[USED]--; // Reduce "used" count
	}

	/* Reduce vector if we have unecessarily large free space */
	if (vec[LEN] > vec[USED] * VEC_RESIZE_MULTIPLIER) {
		vec = realloc(&vec[START], vec[ELEM_SIZE]*vec[USED] + 3*sizeof(int));
		if (!vec) {
			fprintf(stderr, "Can't realloc vector\n");
			FILEINFO
			abort();
		}
		vec = &vec[3]; // Make vec point to start of data
		vec[LEN] = vec[USED]; // Expand listed size
	}

		*vecptr = (void *)vec;
}

void vec_free(void *vector) {
	int *int_vec = (int *)vector;
	int_vec = &int_vec[START];
	free(int_vec);
}


/*	Example of usage:
 *	struct test *testarray = (struct test *)vector((sizeof(struct test)), 5);
 */

