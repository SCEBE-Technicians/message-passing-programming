#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    srand(time(NULL));

    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int i;
    if (rank == 0) {
        i = rand();
        printf("sending %d to all processes\n", i);
    }

    MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("%d\n", i);
    MPI_Finalize();
}
