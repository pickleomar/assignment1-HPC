#include <mpi.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("process %d of %d: Therank is %s\n", rank, size, (rank%2== 0) ? "even" :"odd");
    if (rank == 0){
        printf("total number of processes: %d\n", size);
    }
    MPI_Finalize();
    return 0;}
