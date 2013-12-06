// Copyright (c) 2013 Rafał Selewońko <rafal@selewonko.com>.

#include <mpi.h>

#define ILE 65536
#define BUFFER_SIZE 1024
#define WRITE_TO_FILE 1


int main(int argc, char *argv[]) {
    int npes;
    int myrank;
    int otherrank;

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    double t1;
    double t2;

    short int v;
    int i;
    unsigned int j;



    // Inicjalizacja podsystemu MPI
    MPI_Init(&argc, &argv);

    // Pobierz rozmiar globalnego komunikatora
    MPI_Comm_size(MPI_COMM_WORLD, &npes);

    // Pobierz numer procesu w globalnym komunikatorze
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    otherrank = myrank ? 0 : 1;


    FILE *file;

    if (WRITE_TO_FILE) {

        if (myrank == 0) {
            file = fopen("wyniki_proces_1.txt", "w+");
        } else if (myrank == 1) {
            file = fopen("wyniki_proces_2.txt", "w+");
        }
    } else {
        file = stdout;
    }
    fprintf(file, "id procesu, czy nieblokujacy, dlugosc, czas, przepustowosc\n");

    for (v = 0; v < 2; v += 1) {
        for (i = 1; i <= BUFFER_SIZE; i <<= 1) {
            t1 = MPI_Wtime();

            for (j = 1; j <= ILE; j += 1) {
                MPI_Status status[2];
                if (v == 0) {
                    MPI_Request request[2];
                    MPI_Isend(&buffer1, i, MPI_BYTE, otherrank, 13, MPI_COMM_WORLD, &request[0]);
                    MPI_Irecv(&buffer2, i, MPI_BYTE, otherrank, 13, MPI_COMM_WORLD, &request[1]);
                    MPI_Waitall(2, request, status);
                } else if (v == 1) {
                    MPI_Send(&buffer1, i, MPI_BYTE, otherrank, 13, MPI_COMM_WORLD);
                    MPI_Recv(&buffer2, i, MPI_BYTE, otherrank, 13, MPI_COMM_WORLD, status);
                }
            }

            t2 = MPI_Wtime();

            fprintf(file, "%d, %d, %d, %e, %f\n", myrank, v, i, (t2 - t1) / (ILE * 2), i / (t2 - t1));
        }
    }

    if (WRITE_TO_FILE) {
        fclose(file);
    }

    MPI_Finalize();
    return 0;
}
