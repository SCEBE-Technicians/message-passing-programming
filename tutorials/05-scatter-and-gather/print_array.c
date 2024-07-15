#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int array[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    int array_length = sizeof(array)/sizeof(array[0]);

    int subarray_length = array_length / world_size;
    int subarray[subarray_length];
    MPI_Scatter(array, subarray_length, MPI_INT, subarray, subarray_length, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i<subarray_length; i++) {
        printf("Array value is %d on rank %d\n", subarray[i], rank);
    }
    MPI_Finalize();
}
