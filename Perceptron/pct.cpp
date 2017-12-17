#include "pct.hpp"

layer::layer(int in, int out) {
	input.resize(in);
	output.resize(out);
	weight.resize(in*out);
	delta.resize(in*out);
	dweight.resize(in*out);
	for (int c=0; c<weight.size(); c++) {
		weight[c] = .0;//rand() % 201 -100;		//-100 < w23 < +100
		delta[c] = .0;
		dweight[c] = .0;
	}
}

int layer::setSize(int in, int out) {
	input.resize(in);
	output.resize(out);
	weight.resize(in*out);
	delta.resize(in*out);
	dweight.resize(in*out);
	for (int c=0; c<weight.size(); c++) {
		weight[c] = 0;
		delta[c] = .0;
		dweight[c] = .0;
	}
	return 0;
}

double layer::step(double x) {
	if (x > 0)	return 1.0;
	else		return 0.0;
}

double layer::sigmoid(double x) {
	return (1.0 / (1.0 + exp(-20*x)));
}

int layer::update(std::vector<double> x) {
	double result = 0;
	
	std::cout<<"update: ";
	//Layer S start
	if( x.size() != input.size())			return -1;
	for (int c=0; c<input.size(); c++) 		input[c] = x[c];
	//Layer S end
	
	//Layer R start
	std::cout<<" lr: ";
	for (int c=0; c<output.size(); c++) {
		result = 0;
		for (int d=0; d<input.size(); d++) {
			result += input[d] * weight[output.size()*c + d];
		}
		output[c] = step(result);
		std::cout<<output[c]<<",";
	}
	//Layer R end
	return 0;
}

int layer::updateBP(std::vector<double> x) {
	double result = 0;
	
	std::cout<<"updateBP: ";
	//Layer S start
	if( x.size() != input.size())			return -1;
	for (int c=0; c<input.size(); c++) 		input[c] = x[c];
	//Layer S end
	
	//Layer R start
	std::cout<<" lr: ";
	for (int c=0; c<output.size(); c++) {
		result = 0;
		for (int d=0; d<input.size(); d++) {
			result += input[d] * weight[output.size()*c + d];
		}
		output[c] = sigmoid(result);
		std::cout<<output[c]<<",";
	}
	//Layer R end
	return 0;
}

int layer::train(std::vector<double> x, std::vector<double> y, double eta) {
	double err = 0;
	
	std::cout<<"train: ";
	if (x.size() != input.size())	return 0;
	if (y.size() != output.size())	return 0;
	
	update(x);
	
	std::cout<<" w: ";
	for (int c=0; c<output.size(); c++) {
		err = (y[c] - output[c]);
		for (int d=0; d<input.size(); d++) {
			weight[output.size()*c + d] = weight[output.size()*c + d] + err * input[d] * eta;
			std::cout<<weight[output.size()*c + d]<<",";
		}
	}
	std::cout<<std::endl;
	return 0;
}

int layer::trainBP(std::vector<double> x, std::vector<double> y, double eta) {
	double err = 0;
	
	std::cout<<"train: ";
	if (x.size() != input.size())	return 0;
	if (y.size() != output.size())	return 0;
	
	updateBP(x);
	
	std::cout<<" w: ";
	for (int c=0; c<output.size(); c++) {
		err = (y[c] - output[c]);
		for (int d=0; d<input.size(); d++) {
			weight[output.size()*c + d] = weight[output.size()*c + d] + err * input[d] * eta;
			std::cout<<weight[output.size()*c + d]<<",";
		}
	}
	std::cout<<std::endl;
	return 0;
}
