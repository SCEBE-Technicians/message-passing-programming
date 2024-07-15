#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

double integrate_sin(int ntrials) {
    double sum = 0;
    for (int i = 0; i < ntrials; i++) {
        double rand_int = (double)(rand()) / (double)(RAND_MAX) * M_PI;
        sum += sin(rand_int);
    }
    return sum * M_PI / ntrials;
}

int main()
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    srand(time(NULL) * rank);

    double sin_estimate = integrate_sin(1000000000);

    double *results;
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        results = malloc(sizeof(double) * world_size);
    }

    MPI_Gather(
        &sin_estimate,  // Send `sin_estimate`
        1,              // which is of length 1
        MPI_DOUBLE,     // and is type double.
        results,        // Receive messages to `results`.
        1,              // Each message consists of 1
        MPI_DOUBLE,     // double.
        0,              // Gather to rank 0
        MPI_COMM_WORLD  // on COMM_WORLD.
    );
    
    if (rank == 0) {
        double aggregate_estimate = 0;
        for (int i = 0; i < world_size; i++) {
            aggregate_estimate += results[i];
        }
        aggregate_estimate /= world_size;
        printf("Aggregate estimate = %f \n", aggregate_estimate);
    }

    MPI_Finalize();
}
