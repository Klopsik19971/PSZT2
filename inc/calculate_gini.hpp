#ifndef CALCULATE_GINI_HPP_
#define CALCULATE_GINI_HPP_

#include <vector>
#include "common.hpp"

class decision_tree;

class giniResult
{
public:
	double result;
	double average;
	colType type;
	int idx;
	explicit giniResult(double res, double avg, colType t, int i, std::vector<bool> v);
	bool operator>(const giniResult& g);
	std::vector<bool> vieved;
};

giniResult gini(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult prev);
giniResult calculateGini(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult prev, int type);
double make_average(std::vector<std::vector<double>>& dataSetT);
void make_new_average(std::vector<std::vector<double>>& dataSetTable);

#endif //CALCULATE_GINI_HPP_
