#include <iostream>
#include <vector>
#include <cmath>

class layer {
private:
	std::vector<int> input;
	std::vector<int> output;
	std::vector<double> weight;
public:
	layer() {};
	layer(int,int);
	int setSize(int,int);
	
	int step(int, double);
	
	int update(std::vector<int>);
	int train(std::vector<int>, std::vector<int>, double);
};