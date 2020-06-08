#include "data_read.hpp"
#include "sort_col.hpp"
#include "calculate_gini.hpp"
#include "common.hpp"
#include "decision_tree.hpp"
#include <vector>
#include <iostream>
#include <float.h>

int main()
{
	std::vector<std::vector<double>> boston;
	try
	{
		data_read::read(boston, "../data/boston.csv");
	}	
	catch	(const std::exception& e)
	{	
		std::cerr<<e.what()<<std::endl;
	}
	/*std::cout<<boston.size()<<std::endl;
	sortCol::sort(boston.begin(), boston.end(), colType::medv);
	std::vector<double> counting_table;
	double temp;
	counting_table.push_back(1);
	temp = boston[0][static_cast<int>(colType::medv)];
	for(unsigned int i = 1; i < boston.size(); ++i)
	{
		if(temp == boston[i][static_cast<int>(colType::medv)])
			++counting_table[counting_table.size()-1];
		else
		{
			counting_table.push_back(1);
			temp = boston[i][static_cast<int>(colType::medv)];		
		}
	}
	std::cout<<counting_table.size()<<std::endl;*/
	decision_tree test(boston.begin(), boston.end(), boston.size());
	/*giniResult test = gini(boston.begin(), boston.end(), boston.size(), giniResult(DBL_MAX, DBL_MAX, static_cast<colType>(0), 0, std::vector<bool>(static_cast<int>(colType::medv), 0)));
	std::cout<<test.result<<" "<<test.average<<" "<<test.type<<" "<<test.idx<<std::endl;
	for(int i = 0; i < test.vieved.size(); ++i)
	{
		std::cout<<test.vieved[i];
	}
	std::cout<<std::endl;*/
	/*sortCol::sort(boston.begin(), boston.end(), colType::medv);
	for(unsigned int i = 0; i < boston.size(); ++i)
	{
		for(unsigned int j = 0; j < boston[i].size(); ++j)
			std::cout<<boston[i][j]<<" ";
		std::cout<<std::endl;	
	}*/
	/*for(int i = 0; i < boston.size(); ++i)
	{
		for(int j = 0; j < boston[i].size(); ++j)
		{
			std::cout<<boston[i][j]<<" ";
		}
		std::cout<<std::endl;
	}*/
	return 0;
}
