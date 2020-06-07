#ifndef CALCULATE_GINI_HPP_
#define CALCULATE_GINI_HPP_

#include <vector>
#include <set>

void gini(std::vector<std::vector<double>> &dataSetTable);
double calculateGini(std::vector<std::vector<double>> &dataSetTable, int rows, int columns, int whatColumn, std::set<double> currentDecidingParameters);

#endif //CALCULATE_GINI_HPP_
