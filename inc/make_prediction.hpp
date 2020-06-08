#ifndef MAKE_PREDICTION_HPP_
#define MAKE_PREDICTION_HPP_

#include <vector>
#include "decision_tree.hpp"

void make_prediction(std::vector<std::vector<double>>& dataSetTable, decision_tree& t);

#endif //MAKE_PREDICTION_HPP_
