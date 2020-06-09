#include "data_read.hpp"
#include "sort_col.hpp"
#include "calculate_gini.hpp"
#include "common.hpp"
#include "decision_tree.hpp"
#include <vector>
#include <iostream>
#include <float.h>
#include "make_prediction.hpp"
#include <iomanip>

#define MAX_TREES 10

int main()
{
	std::vector<std::vector<double>> boston;
	std::vector<std::vector<double>> tests;
	try
	{
		data_read::read(boston, "../data/boston.csv");
		data_read::read(tests, "../data/tests.csv");
	}	
	catch	(const std::exception& e)
	{	
		std::cerr<<e.what()<<std::endl;
	}
	std::vector<decision_tree> forest;
	forest.reserve(MAX_TREES);
	double average = make_average(boston);
	forest.emplace_back(boston.begin(), boston.end(), boston.size());
	make_prediction(boston, forest[forest.size()-1]);
	std::cout<<"Make 1 tree..."<<std::endl;
	for(int i = 1; i < MAX_TREES; ++i)
	{
		make_new_average(boston);
		forest.emplace_back(boston.begin(), boston.end(), boston.size());
		make_prediction(boston, forest[forest.size()-1]);
		std::cout<<"Make "<<i+1<<" tree..."<<std::endl;
	}
	double prediction;
	std::cout<<"------------------------------------"<<std::endl;
	for(unsigned int i = 0; i < tests.size(); ++i)
	{
		std::cout<<std::fixed<<std::showpoint<<std::setprecision(2);
		prediction = average;
		for(unsigned int j = 0; j < forest.size(); ++j)
		{
			prediction += 0.1*forest[j].find_val_in_tree(tests[i]);
			std::cout<<forest[j].find_val_in_tree(tests[i])<<" ";
		}
		std::cout<<std::endl;
		std::cout<<tests[i][tests[i].size()-1]<<" -> "<<prediction<<"("<<(tests[i][tests[i].size()-1]-prediction)/tests[i][tests[i].size()-1]*100<<"%)"<<std::endl;
	}
	std::cout<<"------------------------------------"<<std::endl;
	return 0;
}
