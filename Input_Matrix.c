#include "Input_Matrix.h"


 
void print_matrix(int n, int m, double *mas, double *b)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf(" %10.3e", mas[i * n + j]);
        }
        printf(" %10.3e\n", b[i]);
    }
}

unsigned long long currentTimeNano(void)
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (unsigned long long)(t.tv_sec * GIGA_MODIFIER + t.tv_nsec);
}

double f(int k, int n, int i, int j)
{
    double result = 0;
    switch (k) {
		case 1: {
			result = n - fmax(i + 1, j + 1) + 1;
			break;
		}
		case 2: {
			result = fmax(i + 1, j + 1);
			break;
		}
		case 3: {
			result = fabs((double)i - (double)j);
			break;
		}
		case 4: {
			double one = 1.0;
			result = one / (i + j + 1);
			break;
		}
    }
    return result;
}

void input_matrix(int k, int n, double *mas, double *b)
{
    int i;
    int j;
    double sum;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            mas[i * n + j] = f(k, n, i, j);
        }
    }
    for (i = 0; i < n; i++) {
        sum = 0.0;
        for (j = 0; j < (n + 1) / 2; j++) {
            sum += mas[i * n + 2 * j];
        }
        b[i] = sum;
    }
}

int input_from_file(int n, double *mas, double *b, char *name)
{
    FILE *f;
    int i;
    int j;
    int code = 0;
    int res = 0;
    double sum;
    f = fopen(name, "r");

    if (f) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                res = fscanf(f, "%lf", &mas[i * n + j]);
                if (res != 1) {
                    code = -3;
                    break;
                }
            }
            if (code == -3) {
                break;
            }
        }
    } else {
        return -3;
    }
    for (i = 0; i < n; i++) {
        sum = 0.0;
        for (j = 0; j < (n + 1) / 2; j++) {
            sum += mas[i * n + 2 * j];
        }
        b[i] = sum;
    }
    return code;
}

