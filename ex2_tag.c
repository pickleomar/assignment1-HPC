#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rank, size, value;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size < 2){
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if(rank == 0){
        value = 100;
        MPI_Send(&value, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        printf("process 0 sent %d to process 1 with tag 1\n", value);
	fflush(stdout);
        MPI_Recv(&value, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
        printf("process 0 received %d from process 1 with tag 2\n", value);
	fflush(stdout);
    }
    else if(rank==1){
        MPI_Recv(&value, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        printf("process 1 received %d from process 0\n", value);
	fflush(stdout);
        value = value*2;   // double it
        MPI_Send(&value, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        printf("process 1 sent %d back to process 0 with tag 2\n", value);
	fflush(stdout);
    }
    // rank >= 2 does nothing

    MPI_Finalize();
    return 0;
}


//the print order is not the real execution order.
//That fits output buffering. When stdout isn’t a terminal 
//(here mpiexec captures it and forwards it), printf output usually sits in a buffer and is only written out later, 
//often at exit. So each process dumps its lines in one chunk,
//and the chunks reach the terminal in whatever order mpiexec forwards them.
//so here we added fflush(stdout) to each  printf 
