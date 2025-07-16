#define _POSIX_C_SOURCE 199309L 

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOL
#define TOL 1e-6
#endif

#ifndef ITER
#define ITER 1000
#endif

#ifndef eps
#define eps 1e-16
#endif

#ifndef GIGA_MODIFIER
#define GIGA_MODIFIER 1e9
#endif

#ifndef FIVE
#define FIVE 5
#endif

#ifndef EPS
#define EPS 1e-21
#endif

void print_matrix(int, int, double *, double *);
unsigned long long currentTimeNano(void);
double f(int, int, int, int);
int input_from_file(int, double *, double *, char *);
void input_matrix(int, int, double *, double *);
