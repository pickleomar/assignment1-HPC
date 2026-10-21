#include <stdio.h>
#include <mpi.h>

int main(int argc ,char *argv[]){
        int rank,size,token;
        MPI_Status status;
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        int next=(rank+1)%size;
        int prev=(rank-1+size)%size;

        if (rank == 0){
                token=0;
                MPI_Send(&token,1,MPI_INT,next,1,MPI_COMM_WORLD);
                printf("process 0 created the token %d and sent it to %d\n",token,next);
                MPI_Recv(&token,1,MPI_INT,prev,1,MPI_COMM_WORLD,&status);
                printf("process 0 received the final token %d\n",token);
        }
        else{
                MPI_Recv(&token,1,MPI_INT,prev,1,MPI_COMM_WORLD,&status);
                printf("process %d received the token %d\n",rank,token);
                token+=rank;
                MPI_Send(&token,1,MPI_INT,next,1,MPI_COMM_WORLD);
                printf("process %d added its rank and sent the token %d to %d\n",rank,token,next);
        }

        MPI_Finalize();
        return 0;
}
