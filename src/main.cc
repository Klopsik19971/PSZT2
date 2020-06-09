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
#include <chrono>
#include <math.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int MAX_TREES;
	double LEARNING_RATE;
	if(argc == 1)
	{
		MAX_TREES = 10;
		LEARNING_RATE = 0.5;
	}
	else if(argc == 2)
		MAX_TREES = atoi(argv[1]);
	else if(argc == 3)
	{
		MAX_TREES = atoi(argv[1]);
		LEARNING_RATE = atoi(argv[2]);
	}
		
	std::vector<std::vector<double>> boston;
	std::vector<std::vector<double>> tests;
	try
	{
		if(MAX_TREES < 1 || LEARNING_RATE < 0 || LEARNING_RATE > 1)
			throw std::runtime_error("Wrong parameters");
		data_read::read(boston, "../data/boston.csv");
		data_read::read(tests, "../data/tests.csv");
	}	
	catch	(const std::exception& e)
	{	
		std::cerr<<e.what()<<std::endl;
		return -1;
	}
	std::vector<decision_tree> forest;
	forest.reserve(MAX_TREES);
	
	auto start = std::chrono::steady_clock::now();
	
	double average = make_average(boston);
	for(int i = 0; i < MAX_TREES; ++i)
	{
		forest.emplace_back(boston.begin(), boston.end(), boston.size());
		make_prediction(boston, forest[forest.size()-1], LEARNING_RATE);
		std::cout<<"Make "<<i+1<<" tree..."<<std::endl;
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout<<"elapsed time:"<<elapsed_seconds.count()<<"s"<<std::endl;

	std::vector<double> prediction;
	double average_error = 0;
	std::vector<double> percent;
	std::vector<double> val;
	double max_percent = DBL_MIN;
	double absolute_error = 0;
	std::cout<<"------------------------------------"<<std::endl;
	for(unsigned int i = 0; i < tests.size(); ++i)
	{
		std::cout<<std::fixed<<std::showpoint<<std::setprecision(2);
		prediction.push_back(average);
		std::cout<<average<<" ";
		for(unsigned int j = 0; j < forest.size(); ++j)
		{
			prediction[prediction.size()-1] += LEARNING_RATE*forest[j].find_val_in_tree(tests[i]);
			std::cout<<forest[j].find_val_in_tree(tests[i])<<" ";
		}
		std::cout<<std::endl;
		percent.push_back((tests[i][tests[i].size()-1]-prediction[prediction.size()-1])/tests[i][tests[i].size()-1]*100);
		std::cout<<tests[i][tests[i].size()-1]<<" -> "<<prediction[prediction.size()-1]<<"("<<percent[percent.size()-1]<<"%)"<<std::endl;
		average_error += fabs(percent[percent.size()-1]);
		max_percent = fmax(max_percent, fabs(tests[i][tests[i].size()-1]-prediction[prediction.size()-1]));
		absolute_error +=fabs(tests[i][tests[i].size()-1]-prediction[prediction.size()-1]);
	}
	std::cout<<"------------------------------------"<<std::endl;
	average_error/=tests.size();
	std::cout<<"average_error: "<<average_error<<std::endl;
	double standard_deviation=0;
	for(unsigned int i = 0; i < percent.size(); ++i)
	{
		standard_deviation += pow(percent[percent.size()-1]-average_error,2);
	}
	standard_deviation /= tests.size();
	standard_deviation = sqrt(standard_deviation);
	std::cout<<"standard_deviation: "<<standard_deviation<<"%"<<std::endl;
	std::cout<<"max_error_precent: "<<max_percent<<"%"<<std::endl;
	absolute_error/=tests.size();
	std::cout<<"absolute_error: "<<absolute_error<<std::endl;
	return 0;
}
