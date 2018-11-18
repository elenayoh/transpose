#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
//Elena Oh
//I pledge that I have abided by the Stevens Honor System. -Elena Oh

//simple transpose that takes in the size of the matrix and block
void simple_transpose(int N, int block_N){
	//allocate both original matrix and transpose matrix
	double* A = (double*) malloc(sizeof(double) * N * N);
	double* At = (double*) malloc(sizeof(double) * N * N);

	//initialize some variables
	int num_blocks = (N / block_N) * (N / block_N);
	int row, col, round;

	//populate A with random numbers
	for(int i = 0; i < N * N; i++){
		A[i] = rand();
	}

	//Three for loops that traverse the matrix in block sections
	for(round = 0; round < num_blocks; round++){
		for(row = block_N * (block_N * round / N); row < (block_N * (block_N * round / N)) + block_N; row++){
			for(col = block_N * (round % (N/block_N)); col < block_N * (round % (N/block_N)) + block_N; col++){
				At[col*N + row] = A[row*N + col];
			}
		}
	}

	//free both matrix
	free(At);
	free(A);
}



int main(int argc, char **argv){

	//initilize the time variables
	struct timeval start, end;
	gettimeofday(&start, NULL);

	//Make sure there are 3 arguments
	if (argc != 3) {
		fprintf(stderr, "Wrong number of command-line arguments\nThe usage is %s <width of input matrix> <width of block>", argv[0]);
		return -1;
	}

	//Makes sure the matrix and block sizes are integers
	if(atoi(argv[1]) == 0){
		fprintf(stderr, "Please input a number for the width of the input matrix. %s was inputed.\n", argv[1]);
		return -1;
	}

	if(atoi(argv[2]) == 0){
		fprintf(stderr, "Please input a number for the width of the block. %s was inputed.\n", argv[1]);
		return -1;
	}

	//save the matrix and block sizes
	int N = atoi(argv[1]);
	int block = atoi(argv[2]);

	//transpose
	simple_transpose(N, block);

	//Get the end time and calculate how long it took
	gettimeofday(&end, NULL);

	printf("Time diff is: %ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
}