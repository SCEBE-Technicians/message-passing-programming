#include <mpi.h>
#include <stdio.h>
#define PING_PONG_LIMIT 5

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        printf("World size must be 2. Exiting...\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ping_pong_count = 0;
    int partner_rank = (rank + 1) % 2;

    while(ping_pong_count < PING_PONG_LIMIT) {
        if (rank == ping_pong_count % 2) {
            ping_pong_count ++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("ping\n");
        } else {
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("pong\n");
        }
    }

    MPI_Finalize();
}
