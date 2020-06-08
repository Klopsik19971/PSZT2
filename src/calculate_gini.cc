#include "calculate_gini.hpp"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <float.h>
#include "data_read.hpp"
#include "sort_col.hpp"

giniResult::giniResult(double res, double avg, colType t, int i, std::vector<bool> v)
	:result(res),
	 average(avg),
	 type(t),
	 idx(i)
{
	for(unsigned int i = 0; i < v.size(); ++i)
	{
		vieved.push_back(v[i]);
	}
}

bool giniResult::operator>(const giniResult& g)
{
	if(average > g.average)
		return true;
	return false;
}

giniResult gini(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult prev)
{
	giniResult best(DBL_MAX, DBL_MAX, static_cast<colType>(0), 0, std::vector<bool>(static_cast<int>(colType::medv), 0));
	if(size > 1)
		for(unsigned int i = 0; i < prev.vieved.size(); ++i)
		{
			if(!prev.vieved[i])
			{
				giniResult temp = calculateGini(first, last, size, prev, i);
				if(best>temp)
					best=temp;
			}
		}
	return best;
}

giniResult calculateGini(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult prev, int type)
{
	sortCol::sort(first, last, static_cast<colType>(type));
	std::vector<double> counting_table;
	double first_interval;
	double second_interval;
	double temp;
	giniResult result(DBL_MAX, DBL_MAX, static_cast<colType>(0), 0, prev.vieved);
	for(unsigned int i = 0; i < size-1; ++i)
	{
		if(first[i][type]!=first[i+1][type])
		{
			first_interval = 1;
			second_interval = 1;
			sortCol::sort(first, first+i, static_cast<colType>(type));
			counting_table.push_back(1);
			temp = first[0][static_cast<int>(colType::medv)];
			for(unsigned int j = 1; j <=i; ++j)
			{
				if(temp == first[j][static_cast<int>(colType::medv)])
					++counting_table[counting_table.size()-1];
				else
				{
					counting_table.push_back(1);
					temp = first[j][static_cast<int>(colType::medv)];		
				}
			}
			for(unsigned int j = 0; j < counting_table.size(); ++j)
			{
				first_interval-=pow(counting_table[j]/(i+1),2);
			}
			counting_table.clear();
			sortCol::sort(first+i+1, last, static_cast<colType>(type));
			counting_table.push_back(1);
			temp = first[i+1][static_cast<int>(colType::medv)];
			for(unsigned int j = i+2; j < size; ++j)
			{
				if(temp == first[j][static_cast<int>(colType::medv)])
					++counting_table[counting_table.size()-1];
				else
				{
					counting_table.push_back(1);
					temp = first[j][static_cast<int>(colType::medv)];		
				}
			}
			for(unsigned int j = 0; j < counting_table.size(); ++j)
			{
				second_interval-=pow(counting_table[j]/(size-i-1),2);
			}
			counting_table.clear();
			result.result = (first[i][type]+first[i+1][type])/2;
			result.type = static_cast<colType>(type);
			result.idx = i;
			result.average = fmin(result.average, (first_interval*(i+1)/size)+(second_interval*(size-i-1)/size));
			result.vieved[type] = true;
			sortCol::sort(first, last, static_cast<colType>(type));
		}

	}
	return result;
}
