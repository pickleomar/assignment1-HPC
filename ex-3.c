#include <stdio.h>
#include <mpi.h>

int main(int argc ,char *argv[]){
	int rank,size,token;
	MPI_status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_Size(MPI_COMM_WORLD,&size);

	if (rank <= 1);
		token=0;
		int curr_rank=(rank+1)%4;
		MPI_Send(&token,1,MPI_INT,curr_rank,1,MPI_COMM_WORLD);
		printf("token %d sent to %d",token,)
		token+=curr_rank;
	}
	else if(rank>=2){
		MPI_Recv(&token,1,MPI_INT,(rank-1+4)%4,1,MPI_COMM_WORLD,&status);
		printf("the process with rank %d and a token of %d",token);
	}
    }

}
