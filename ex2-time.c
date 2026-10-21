#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rank, size, value;
    double t0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Barrier(MPI_COMM_WORLD);
    t0 = MPI_Wtime();

    if(rank == 0){
        value = 100;
        MPI_Send(&value, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        printf("[%.6f] process 0 sent %d to process 1 with tag 1\n", MPI_Wtime()-t0, value);
        fflush(stdout);
        MPI_Recv(&value, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
        printf("[%.6f] process 0 received %d from process 1 with tag 2\n", MPI_Wtime()-t0, value);
        fflush(stdout);
    }
    else if(rank==1){
        MPI_Recv(&value, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("[%.6f] process 1 received %d from process 0\n", MPI_Wtime()-t0, value);
        fflush(stdout);
        value = value*2;
        MPI_Send(&value, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        printf("[%.6f] process 1 sent %d back to process 0 with tag 2\n", MPI_Wtime()-t0, value);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
