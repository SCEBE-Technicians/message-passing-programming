#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (rank == 0) {
        // Choose one of four animals
        srand(time(NULL));
        char animals[4][10] = {"dog", "cat", "rat", "gorilla"};
        char animal[10];
        int index = rand() % 4;
        strcpy(animal, animals[index]);
        printf("Sending %s of size %d\n", animal, strlen(animal));
        MPI_Send(animal, strlen(animal), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else {
        // Get status
        MPI_Status stat;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &stat);

        int message_length;
        MPI_Get_count(&stat, MPI_CHAR, &message_length);
        printf("Receiving message of length %d\n", message_length);

        // Receive message
        char message[message_length];
        MPI_Recv(&message, message_length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received %s from sender\n", message);
    
    }
    MPI_Finalize();
}
