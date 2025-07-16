#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

double compute_residual_norm(int, const double *, double const *, double const *);
double compute_error(int, double *, double const *, double const *);
void Rotation(double, double, double *, double *);
void applyRotation(double *, int, int, int, double, double);
void solveRotation(double *, double *, double *, int);
