#include "pct.hpp"

layer::layer(int in, int out) {
	input.resize(in);
	output.resize(out);
	weight.resize(in*out);
	delta.resize(out);
	dweight.resize(in*out);
	for (int c=0; c<weight.size(); c++) {
		weight[c] = .0;//rand() % 201 -100;		//-100 < w23 < +100
		dweight[c] = .0;
	}
	for (int c=0; c<out; c++)	delta[c] = .0;
}

int layer::setSize(int in, int out) {
	input.resize(in);
	output.resize(out);
	weight.resize(in*out);
	delta.resize(out);
	dweight.resize(in*out);
	for (int c=0; c<weight.size(); c++) {
		weight[c] = 0;
		dweight[c] = .0;
	}
	for (int c=0; c<out; c++)	delta[c] = .0;
	return 0;
}

int layer::getWeight(std::vector<double> &w) {
	if (w.size() < weight.size())	w.resize(weight.size());
	for (int c=0; c<weight.size(); c++) {
		w[c] = weight[c];
	}
	return 0;
}
int layer::getDelta(std::vector<double> &d) {
	if (d.size() < delta.size())	d.resize(delta.size());
	for (int c=0; c<delta.size(); c++) {
		d[c] = delta[c];
	}
	return 0;
}
int layer::getOutput(std::vector<double> &o) {
	if (o.size() < output.size())	o.resize(output.size());
	for (int c=0; c<output.size(); c++) {
		o[c] = output[c];
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


int layer::setDelta(std::vector<double> y, double eta, double alp) {
	if (y.size() != output.size())	return -1;
	
	for (int c=0; c<output.size(); c++) {
		delta[c] = (output[c] - y[c]) * output[c] * (1.0 - output[c]);
		for (int e=0; e<input.size(); e++) {
			dweight[output.size()*c + e] = -eta * delta[c] * input[e] + alp * dweight[output.size()*c + e];
			//weight[output.size()*c + e] = weight[output.size()*c + e] + dweight[output.size()*c + e];
		}
	}
	return 0;
}

int layer::setDelta(std::vector<double> w, std::vector<double> d,  double eta, double alp) {
	for (int c=0; c<output.size(); c++) {
		delta[c] = 0;
		for (int e=0; e<d.size(); e++) {
			delta[c] += w[d.size()*e + c] * d[e];
		}
		delta[c] *= output[c] * (1.0 - output[c]);
		
		for (int e=0; e<input.size(); e++) {
			dweight[output.size()*c + e] = -eta * delta[c] * input[e] + alp * dweight[output.size()*c + e];
			//weight[output.size()*c + e] = weight[output.size()*c + e] + dweight[output.size()*c + e];
		}
	}
	return 0;
}

int layer::train() {
	for (int c=0; c<output.size(); c++) {
		for (int e=0; e<input.size(); e++) {
			weight[output.size()*c + e] = weight[output.size()*c + e] + dweight[output.size()*c + e];
	//		std::cout<<weight[output.size()*c + e]<<",";
		}
	}
	return 0;
}