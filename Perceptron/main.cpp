#include <fstream>
#include <string>
#include <stdlib.h>
#include "pct.hpp"

#define MAX_DATA_DIM	(12)
#define TRAIN_DATA_SIZE (4)
#define LAYER_SIZE		(2)
#define VEC_DIM			(3)			//input + bias
#define OUT_DIM			(1)
#define ETA				(0.1)
#define ALP				(0.1)

int setTrainData(char fname[], int n, std::vector<double> &d) {
	std::ifstream ifs(fname);
	std::string str;
	
	if (ifs.fail())	return -1;
	
	for (int c=0; c<n; c++) {
		std::cout<<"c="<<c<<", ";
		std::getline(ifs, str);
		std::sscanf(str.data(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
					 &d[MAX_DATA_DIM*c+0], &d[MAX_DATA_DIM*c+1], &d[MAX_DATA_DIM*c+2], &d[MAX_DATA_DIM*c+3],
					 &d[MAX_DATA_DIM*c+4], &d[MAX_DATA_DIM*c+5], &d[MAX_DATA_DIM*c+6], &d[MAX_DATA_DIM*c+7],
					 &d[MAX_DATA_DIM*c+8], &d[MAX_DATA_DIM*c+9], &d[MAX_DATA_DIM*c+10], &d[MAX_DATA_DIM*c+11]);
		// debag message start
		for(int e=0; e<MAX_DATA_DIM; e++) {
			std::cout<<d[MAX_DATA_DIM*c+e]<<",";
		}
		std::cout<<std::endl;
		//debag message end
	}
	return 0;
}

int main() {
	layer bpnetwork[LAYER_SIZE];
	std::vector<double> buff_x;
	std::vector<double> buff_y;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> out;
	std::vector<double> result;
	std::vector<double> w;
	std::vector<double> del;
	bpnetwork[0].setSize(VEC_DIM, OUT_DIM);
	bpnetwork[1].setSize(OUT_DIM, OUT_DIM);
	buff_x.resize(TRAIN_DATA_SIZE*MAX_DATA_DIM);
	buff_y.resize(TRAIN_DATA_SIZE*MAX_DATA_DIM);
	x.resize(VEC_DIM);
	y.resize(OUT_DIM);
	out.resize(OUT_DIM);
	result.resize(OUT_DIM);
	w.resize(OUT_DIM*OUT_DIM);
	setTrainData("train_data_x.txt", TRAIN_DATA_SIZE, buff_x);
	setTrainData("train_data_y.txt", TRAIN_DATA_SIZE, buff_y);
	
	if (MAX_DATA_DIM < VEC_DIM)	return -1;
	
	for (int c=0; c<50; c++) {
		for (int d=0; d<TRAIN_DATA_SIZE; d++) {
			std::cout<<"x:";
			for (int e=0; e<VEC_DIM; e++) {
				x[e] = buff_x[MAX_DATA_DIM*d + e];
				std::cout<<x[e]<<",";
			}
			std::cout<<"y:";
			for (int e=0; e<OUT_DIM; e++) {
				y[e] = buff_y[MAX_DATA_DIM*d + e];
				std::cout<<y[e]<<",";
			}
			//update
			bpnetwork[0].updateBP(x);
			bpnetwork[0].getOutput(out);
			bpnetwork[1].updateBP(out);
			bpnetwork[1].getOutput(result);
			
			//train
			bpnetwork[LAYER_SIZE-1].setDelta(y, ETA, ALP);
			for (int e=LAYER_SIZE-2; e>=0; e--) {
				bpnetwork[e+1].getWeight(w);
				bpnetwork[e+1].getDelta(del);
				bpnetwork[e].setDelta(w, del, ETA, ALP);
			}
			for (int e=LAYER_SIZE-1; e>=0; e--) {
				bpnetwork[e].train();
			}
		}
	}
	return 0;
}