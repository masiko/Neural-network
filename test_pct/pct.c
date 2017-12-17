#include<stdio.h>
#include<math.h>

#define TRAIN_DATA_SIZE (4)
#define VEC_SIZE        (3)

int dot(int size, int v0[], double v1[]) {
	int c = 0;
	double result = 0;
	
	for (c=0; c<size; c++) {
		result += v0[c] * v1[c];
	}
	return (int)(result);
}

int step(int i) {
	if(i > 0)	return 1;
	else		return 0;
}

int output(int size, int input[], double weight[]) {
	return step(dot(size, input, weight));
}

int train(int size, int input[], int y, double weight[], double eta) {
	int out = 0;
	int c = 0;
	
	//printf("in: %d,%d,%d, y: %d, w: %.2f,%.2f,%.2f    ", input[0],input[1],input[2], y, weight[0], weight[1], weight[2]);
	
	out = output(size, input, weight);
	
	printf("y=%d, out=%d ", y, out);
	
	for (c=0; c<size; c++) {
		weight[c] = weight[c] + (y - out) * input[c] * eta;
	}
	printf("w: %.2f,%.2f,%.2f\n",weight[0], weight[1], weight[2]);
	
	return 0;
}


int main() {
	int c = 0;
	int d = 0;
	int result = 0;
	int train_x[TRAIN_DATA_SIZE][VEC_SIZE] = {{0,0,1}, {0,1,1}, {1,0,1}, {1,1,1}};
	int train_y[TRAIN_DATA_SIZE] = {0,0,0,1};
	double weight[VEC_SIZE] = {.0,.0,.0};
	double eta = 0.1;
	
	for (c=0; c<50; c++) {
		for (d=0; d<TRAIN_DATA_SIZE; d++) {
			train(VEC_SIZE, train_x[d], train_y[d], weight, eta);
		}
	}
	
	for (d=0; d<TRAIN_DATA_SIZE; d++) {
		result = output(VEC_SIZE, train_x[d], weight);
		printf("%d, ", result);
	}
	
	return 0;
}