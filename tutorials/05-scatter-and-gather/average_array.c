#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>

#define ARRAY_SIZE 1200000000

void fill_array(int *arr) {
    int sum = 0;
    for (int i = 0; i<ARRAY_SIZE; i++) {
        arr[i] = rand() % 10;
    }
}

double average_array(int  *arr, int arr_size) {
    double avg = 0;
    for (int i = 0; i<arr_size; i++) {
        avg += (double)arr[i] / (double)ARRAY_SIZE;
    }
    return avg;
}

double sum_array(double *arr, int arr_size) {
    double sum = 0;
    for (int i = 0; i<arr_size; i++) {
        sum += arr[i];
    }
    return sum;
}

void mpi_setup(int *world_size, int *rank) {
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, world_size);
}

int array[ARRAY_SIZE];
int main(int argc, char** argv) {
    int rank, world_size;
    mpi_setup(&world_size, &rank);

    if (rank == 0) {
        fill_array(array);
    }

    int elements_per_proc = ARRAY_SIZE/world_size;
    int *sub_array = malloc(sizeof(int) * elements_per_proc);

    MPI_Scatter(array, elements_per_proc, MPI_INT, sub_array, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    double avg = average_array(sub_array, elements_per_proc);

    double *sub_avgs;
    if (rank==0) {
        sub_avgs = (double *)malloc(sizeof(double) * world_size);
    }
    MPI_Gather(&avg, 1, MPI_DOUBLE, sub_avgs, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank==0) {
        double total_avg = sum_array(sub_avgs, world_size);
        printf("%f\n", total_avg);
        free(sub_avgs);
    }
    free(sub_array);
    MPI_Finalize();
}
