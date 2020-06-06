#include "data_read.hpp"
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
	return 0;
}
