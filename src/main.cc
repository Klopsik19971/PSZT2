#include "data_read.hpp"
#include "sort_col.hpp"
#include "calculate_gini.hpp"
#include <vector>
#include <iostream>

int main()
{
	std::vector<std::vector<double>> vineWhite;
	std::vector<std::vector<double>> vineRed;
	try
	{
		data_read::read(vineWhite, "../data/winequality-white.csv");
		data_read::read(vineRed, "../data/winequality-red.csv");

	}	
	catch	(const std::exception& e)
	{	
		std::cerr<<e.what()<<std::endl;
	}
	/*sortCol::sort(vineWhite.begin(), vineWhite.end(), colType::quality);
	for(unsigned int i = 0; i < vineWhite.size(); ++i)
	{
		for(unsigned int j = 0; j < vineWhite[i].size(); ++j)
			std::cout<<vineWhite[i][j]<<" ";
		std::cout<<std::endl;	
	}*/
	gini(vineWhite);	
	return 0;
}
