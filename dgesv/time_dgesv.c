#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"

//extern void dgemm_(char*, char*, int*, int*,int*, double*, double*, int*, double*, int*, double*, double*, int*);i

extern void dgesv_(int *n, int *nrhs, double *A, int *lda, int *ipiv, double *B, int *ldb, int *info);

#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"

//extern void dgemm_(char*, char*, int*, int*,int*, double*, double*, int*, double*, int*, double*, double*, int*);

int main(int argc, char *argv[]) {
    int i;
    printf("test!\n");
    if (argc < 3) {
        printf("Input Error\n");
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int ipiv[m];
    int lda = n;
    int ldb = n;
    int info;
//  int k = atoi(argv[3]);
    int sizeofa = m * m;
    int sizeofb = m * n;
//  int sizeofc = m * n;
//  char ta = 'N';
//  char tb = 'N';
//  double alpha = 1.2;
//  double beta = 0.001;

    struct timeval start, finish;
    double duration;

    double *A = (double *) malloc(sizeof(double) * sizeofa);
    double *B = (double *) malloc(sizeof(double) * sizeofb);
//  double* C = (double*)malloc(sizeof(double) * sizeofc);

    srand((unsigned) time(NULL));

    for (i = 0; i < sizeofa; i++)
        A[i] = i % 3 + 1;//(rand()%100)/10.0;

    for (i = 0; i < sizeofb; i++)
        B[i] = i % 3 + 1;//(rand()%100)/10.0;

//  for (i=0; i<sizeofc; i++)
//    C[i] = i%3+1;//(rand()%100)/10.0;
    //#if 0
//  printf("m=%d,n=%d,k=%d,alpha=%lf,beta=%lf,sizeofc=%d\n",m,n,k,alpha,beta,sizeofc);
    printf("m=%d,n=%d\n", m, n);
    gettimeofday(&start, NULL);
    //dgemm_(&ta, &tb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);

    //extern void dgesv_(int * n, int * nrhs, double * A, int * lda,
    //            int * ipiv, double * B, int * ldb, int * info);
    dgesv_(&m, &n, A, &m, ipiv, B, &m, &info);
    gettimeofday(&finish, NULL);

    duration =
            ((double) (finish.tv_sec - start.tv_sec) * 1000000 + (double) (finish.tv_usec - start.tv_usec)) / 1000000;
    double gflops = 2.0 * m * n;
    gflops = gflops / duration * 1.0e-6;

    FILE *fp;
    fp = fopen("timeDGEMM.txt", "a");
    fprintf(fp, "%dx%dx\t%lf s\t%lf MFLOPS\n", m, n, duration, gflops);
    fclose(fp);

    free(A);
    free(B);

    return 0;
}
