#include "Solver.h"

void Rotation(double a, double b, double *c, double *s)
{
    if (fabs(b) < EPS){
        *c = 1.0;
        *s = 0.0;
    } else if (fabs(a) < EPS) {
        *c = 0.0;
        *s = -1.0;
    } else {
        *c = a / hypot(a, b);
        *s = -b / hypot(a, b);
    }
}

void applyRotation(double *A, int n, int i, int j, double c, double s)
{
    int k;
    for (k = 0; k < n; k++) {
        double temp = c * A[i * n + k] - s * A[j * n + k];
        A[j * n + k] = s * A[i * n + k] + c * A[j * n + k];
        A[i * n + k] = temp;
    }
}

void solveRotation(double *A, double *x, double *b, int n)
{
    int i;
    int j;
    double c;
    double s;
    double temp;
    double sum;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (fabs(A[i * n + i]) > EPS || fabs(A[j * n + i]) > EPS) {
                Rotation(A[i * n + i], A[j * n + i], &c, &s);
                applyRotation(A, n, i, j, c, s);
                temp = b[i];
                b[i] = c * temp - s * b[j];
                b[j] = s * temp + c * b[j];
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        sum = 0.0;
        for (j = i + 1; j < n; j++) {
            sum += A[i * n + j] * x[j];
        }
        if (fabs(A[i * n + i]) < EPS) {
            x[i] = (b[i] - sum);
        } else {
            x[i] = (b[i] - sum) / A[i * n + i];
        }
    }
}

double compute_error(int n, double *A, double const *x, double const *b)
{
    int i;
    int j;
    double error;
    double *Ax;
    double *residual;
    Ax = (double *)malloc(n * sizeof(double));

    for (i = 0; i < n; i++) {
        Ax[i] = 0.0;
        for (j = 0; j < n; j++) {
            Ax[i] += A[i * n + j] * x[j];
        }
    }

    residual = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++) {
        residual[i] = b[i] - Ax[i];
    }

    error = 0.0;
    for (i = 0; i < n; i++) {
        error += residual[i] * residual[i];
    }
    error = sqrt(error);

    printf("Error: %10.3e\n", error);

    free(Ax);
    free(residual);

    return error;
}

double compute_residual_norm(int n, const double *A, double const *x,
                             double const *b)
{
    int i;
    int j;
    double res;
    double norm = 0.0;
    for (i = 0; i < n; i++) {
        res = 0.0;
        for (j = 0; j < n; j++) {
            res += A[i * n + j] * x[j];
        }
        res -= b[i];
        norm += res * res;
    }
    return sqrt(norm);
}
