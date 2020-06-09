#include "make_prediction.hpp"
#include "common.hpp"
#include "decision_tree.hpp"
#include <iostream>

void make_prediction(std::vector<std::vector<double>>& dataSetTable, decision_tree& t, double learning_rate)
{
	for(unsigned int i = 0; i < dataSetTable.size(); ++i)
	{
		dataSetTable[i][static_cast<int>(colType::proposal)]+=t.find_val_in_tree(dataSetTable[i])*learning_rate;
		dataSetTable[i][static_cast<int>(colType::residuum)]=dataSetTable[i][static_cast<int>(colType::medv)]-dataSetTable[i][static_cast<int>(colType::proposal)];
	}
}
