#include <iostream>
#include <vector>
#include <cmath>

class layer {
private:
	std::vector<double> input;
	std::vector<double> output;
	std::vector<double> weight;
	
	std::vector<double> delta;
	std::vector<double> dweight;
public:
	layer() {};
	layer(int,int);
	int setSize(int,int);
	
	double step(double);
	double sigmoid(double);
	
	int update(std::vector<double>);
	int updateBP(std::vector<double>);
	int train(std::vector<double>, std::vector<double>, double);
	int trainBP(std::vector<double>, std::vector<double>, double);
};