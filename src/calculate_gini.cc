#include "calculate_gini.hpp"

#include <iostream>
#include <algorithm>
#include <math.h>
#include "data_read.hpp"
#include "sort_col.hpp"

double gini(std::vector<std::vector<double>> &dataSetTable)
{
	double average = 0;
	double best = 2;
	for(unsigned int i = 0; i < dataSetTable.size(); ++i)
	{
		average+=dataSetTable[i][static_cast<int>(colType::quality)];
	} 
	average/=dataSetTable.size();
	for(unsigned int i = 0; i < dataSetTable.size(); ++i)
	{
		dataSetTable[i].push_back(dataSetTable[i][static_cast<int>(colType::quality)]-average);
	} 
	for(int i = 0; i < static_cast<int>(colType::quality); ++i)
	{
		best = fmin(best, calculateGini(dataSetTable, i));
	}
	return best;
}

double calculateGini(std::vector<std::vector<double>> &dataSetTable, int type)
{
	sortCol::sort(dataSetTable.begin(), dataSetTable.end(), static_cast<colType>(type));
	std::vector<double> temp (11,0);
	double first_inverval;
	double second_interval;
	double result = 2;
	for(unsigned int i = 0; i < dataSetTable.size()-2; ++i)
	{
		if(dataSetTable[i][type]!=dataSetTable[i+1][type])
		{
			first_inverval = 1;
			second_interval = 1;
			for(unsigned int j = 0; j <=i; ++j)
			{
				++temp[dataSetTable[j][static_cast<int>(colType::quality)]];
			}
			for(unsigned int j = 0; j < temp.size(); ++j)
			{
				first_inverval-=pow(temp[j]/(i+1),2);
				temp[j]=0;
			}
			for(unsigned int j = i+1; j < dataSetTable.size(); ++j)
			{
				++temp[dataSetTable[j][static_cast<int>(colType::quality)]];
			}
			for(unsigned int j = 0; j < temp.size(); ++j)
			{
				second_interval-=pow(temp[j]/(dataSetTable.size()-i-1),2);
				temp[j]=0;
			}
			result = fmin(result, (first_inverval*(i+1)/dataSetTable.size())+(second_interval*(dataSetTable.size()-i-1)/dataSetTable.size()));
		}

	}
	return result;
}
