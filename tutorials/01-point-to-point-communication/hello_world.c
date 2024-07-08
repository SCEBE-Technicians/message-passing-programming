#include <stdio.h>
#include <mpi.h>

int main (int argc, char **argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    printf("Hello world from rank %d of %d\n", rank, world_size);

    return MPI_Finalize();
}
