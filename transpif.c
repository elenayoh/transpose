#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
//Elena Oh
//I pledge that I have abided by the Stevens Honor System. -Elena Oh

//Returns the number of blocks needed to traverse the entire matrix
int num_of_blocks(int height, int width, int block_N){
	if(height%block_N > 0 && width%block_N > 0){
		return ((height/block_N) + 1) * ((width/block_N) + 1);
	} else if(height%block_N > 0){
		return ((height/block_N) + 1) * (width/block_N);
	} else if(width%block_N > 0){
		return (height/block_N) * ((width/block_N) + 1);
	} else{
		return (height/block_N) * (width/block_N);
	}
}

//simple transpose that takes in the height and width of the matrix and the block size
//transposes the matrix using the blocks
void simple_transpose(int height,int width, int block_N){
	//allocate the original matrix and the transposed one
	double* A = (double*) malloc(sizeof(double) * height * width);
	double* At = (double*) malloc(sizeof(double) * width * height);
	int num_blocks = num_of_blocks(height, width, block_N);
	int row, col, round, skip_count = 0;

	//populate A with random numbers
	for(int i = 0; i < width * height; i++){
		A[i] = rand();
	}

	int div;

	//Needed because division with an integer rounds down and wanted to round up
	if(width % block_N > 0){
		div = (width/block_N) + 1;
	} else{
		div = width/block_N;
	}


	//Goes through the matrix in blocks making sure that no out of bounds switches are made
	while(round < num_blocks){
		row = block_N * (((block_N * round)-(skip_count/2)) / width);
		col = block_N * (round % div);
		while(row < (block_N * (((block_N * round)-(skip_count/2)) / width)) + block_N){
			while(col < block_N * (round % div) + block_N){
				if(row >= height || col >= width){
					col++;
					skip_count++;
				} else{
					At[col*height + row] = A[row*width + col];
					col++;
				}
			}
			row++;
			col = block_N * (round % div);
		}
		round++;
	}

	//Free both matrix
	free(At);
	free(A);
}



int main(int argc, char **argv){

	//initialize the time variables
	struct timeval start, end;
	gettimeofday(&start, NULL);

	//Make sure there are 3 arguments
	if (argc != 4) {
		fprintf(stderr, "Wrong number of command-line arguments\nThe usage is %s <height of the input matrix> <width of input matrix> <width of block>", argv[0]);
		return -1;
	}

	//Make sure that the height and width of the matrix are integers and the block size is as well
	if(atoi(argv[1]) == 0){
		fprintf(stderr, "Please input a number for the height of the input matrix. %s was inputed.\n", argv[1]);
		return -1;
	}

	if(atoi(argv[2]) == 0){
		fprintf(stderr, "Please input a number for the width of the input matrix. %s was inputed.\n", argv[1]);
		return -1;
	}

	if(atoi(argv[3]) == 0){
		fprintf(stderr, "Please input a number for the width of the block. %s was inputed.\n", argv[1]);
		return -1;
	}

	//save as values
	int N_height = atoi(argv[1]);
	int N_width = atoi(argv[2]);
	int block = atoi(argv[3]);

	//calling the transpose function
	simple_transpose(N_height, N_width, block);

	//get the end time and return how long the whole process took
	gettimeofday(&end, NULL);

	printf("Time diff is: %ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
}