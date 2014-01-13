#include <stdlib.h>
int main(int argc, char const *argv[])
{
    // int dziala, double sie wywala
    //double tablica[2048][512];
    //double *tablica[2048];
    int n, s, i;
    n = 1024;
    s = 1024;
    double **a = malloc(sizeof *a * n);
    for (i = 0; i < n; i++){
        a[i] = malloc(sizeof *a[i] * s);
    }

    return 0;
}
