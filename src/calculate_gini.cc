#include "calculate_gini.hpp"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <float.h>
#include "data_read.hpp"
#include "sort_col.hpp"
#include <map>

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
	if(size > 10)
		for(unsigned int i = 0; i < prev.vieved.size(); ++i)
		{
			if(!prev.vieved[i])
			{
				//std::cout<<"------------------------------------------------------------------"<<std::endl;
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
	std::map<double, int> counting_table;
	double first_interval;
	double second_interval;
	giniResult result(DBL_MAX, DBL_MAX, static_cast<colType>(0), 0, prev.vieved);
	for(unsigned int i = 10; i < size-10; ++i)
	{
		if(first[i][type]!=first[i+1][type])
		{
			first_interval = 1;
			second_interval = 1;
			for(unsigned int j = 0; j <=i; ++j)
			{
				++counting_table[first[j][static_cast<int>(colType::residuum)]];
			}
			for(auto iter = counting_table.begin(); iter != counting_table.end(); ++iter)
			{
				first_interval-=pow(iter->second/static_cast<double>(i+1),2);
			}
			counting_table.clear();
			for(unsigned int j = i+1; j < size; ++j)
			{
				++counting_table[first[j][static_cast<int>(colType::residuum)]];
			}
			for(auto iter = counting_table.begin(); iter != counting_table.end(); ++iter)
			{
				second_interval-=pow(iter->second/static_cast<double>(size-i-1),2);
				/*std::cout<<second_interval<<" "<<iter->second<<" "<<(size-i-1)<<" "<<iter->second/static_cast<double>(size-i-1)<<std::endl;
				std::cout<<pow(iter->second/static_cast<double>(size-i-1),2)<<std::endl;*/
				
			}
			//exit(-1);
			counting_table.clear();
			double val = first_interval*(i+1)/static_cast<double>(size)+second_interval*(size-i-1)/static_cast<double>(size);
			if(val < result.average)
			{
			result.result = (first[i][type]+first[i+1][type])/2;
			result.type = static_cast<colType>(type);
			result.idx = i;
			result.average = val;
			result.vieved[type] = true;
			}
			//std::cout<<result.average<<" "<<(first_interval*(i+1)/size)/*+(second_interval*(size-i-1)/size*/)<<std::endl;
			//std::cout<<(first_interval*(i+1)/size)<<" "<<(second_interval*(size-i-1)/size)<<std::endl;
			//std::cout<<first_interval<<" "<<second_interval<<std::endl<<std::endl;
		}

	}
	//exit(-1);
	return result;
}

double make_average(std::vector<std::vector<double>>& dataSetTable)
{
	double average = 0;
	for(unsigned int i = 0; i < dataSetTable.size(); ++i)
	{
		average+=dataSetTable[i][static_cast<int>(colType::medv)];
	} 
	average/=dataSetTable.size();
	for(unsigned int i = 0; i < dataSetTable.size(); ++i)
	{
		dataSetTable[i].push_back(dataSetTable[i][static_cast<int>(colType::medv)]-average);
		dataSetTable[i].push_back(average);
	} 
	return average;
}



