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
	
	int getWeight(std::vector<double>&);
	int getDelta(std::vector<double>&);
	int getOutput(std::vector<double>&);
	
	double step(double);
	double sigmoid(double);
	
	int update(std::vector<double>);
	int updateBP(std::vector<double>);
	int train(std::vector<double>, std::vector<double>, double);
	int train();
	int setDelta(std::vector<double>, double, double);				//last layer
	int setDelta(std::vector<double>, std::vector<double>, double, double);
};