#ifndef _UTIL_H_
#define _UTIL_H_

void check_loop_iterative(void (*generate)(int, int, int, int *), int , int , int *, int *);
void generate_sequence (int , int, int , int *);
int has_loop(int *arr, int n, int looplen, int *ls, int *le);
void hist_of_firstdigits(void (*generate)(int, int, int, int *), int xs, int seqlen, int *h, int digit);
int ilk_basamak(int);

#endif /* _UTIL_H_ */
