#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int rank, namelen, size, message;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);
	if (rank == 0) {
		MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Process %d from node %s sent %d to process %d", rank, processor_name, message, 1);
	} else if (rank != size - 1) {
		MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Process %d from node %s sent %d to process %d", rank, processor_name, message, rank + 1);
	} else {
	}
	MPI_Finalize();
}
