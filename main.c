#include "Input_Matrix.h"
#include "Solver.h"

int main(int argc, char **argv)
{
    int r;
    int n;
    int size;
    int s;
    int code = 0;
    unsigned long long time = 0;
    double *A;
    double *b;
    double *x;
    double res;
    double residual;

    if (argc < 4 || argc > FIVE) {
        printf("Неверное количество аргументов командной строки\n");
        return -1;
    }

    n = atoi(argv[1]);
    r = atoi(argv[2]);
    s = atoi(argv[3]);

    if ((argc < 4 && s == 0) || (s != 0 && argc != 4)) {
        printf("Неверное количество аргументов командной строки\n");
        return -1;
    }
    if (s > 4 || s < 0) {
        printf("Неверно указан параметр k\n");
        return -1;
    }
    if (r > n || r <= 0 || n <= 0) {
        printf("Неверно указаны параметры m & n\n");
        return -1;
    }
    if (s == 0 && argv[4] == NULL) {
        printf("Не введено имя файла\n");
        return -1;
    }

    size = n * n;
    A = (double *)malloc(size * sizeof(double));
    b = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));

    if (A != NULL && b != NULL && x != NULL) {
        switch (argc) {
        case 4: {
            input_matrix(s, n, A, b);
            print_matrix(n, r, A, b);
            break;
        }
        case FIVE: {
            code = input_from_file(n, A, b, argv[4]);
            if (code == -3) {
                printf("Ошибка чтения файла\n");
                free(A);
                free(b);
                free(x);
                return -3;
            }
            print_matrix(n, r, A, b);
            break;
        }
        }
        time = currentTimeNano();
        solveRotation(A, x, b, n);
        time = currentTimeNano() - time;
        printf("Time: %llu ns\n", time);

        residual = compute_residual_norm(n, A, x, b);
        printf("Residual: %10.3e\n", residual);

        printf("Solution:\n");
        for (int i = 0; i < r; i++) {
            printf("%10.3e\n", x[i]);
        }

        res = compute_error(n, A, x, b);

        if (res + 4 < eps) {
            printf("Матрица вырожденная\n");
            return -4;
        }
        free(A);
        free(b);
        free(x);
        return 0;
    }

    printf("Ошибка выделения памяти\n");
    return -2;
}
