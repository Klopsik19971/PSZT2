#include "sort_col.hpp"
#include <algorithm>
#include <iostream>

void sortCol::sort(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, colType type)
{
	std::sort(first, last, sort_col(type));
}

sortCol::sort_col::sort_col(colType type)
{
	if(static_cast<int>(type)>static_cast<int>(colType::proposal)||static_cast<int>(type)<0)
		throw std::runtime_error("Wrong use of sort\n");
	for(int i = 0; i <= static_cast<int>(colType::residuum); ++i)
	{
		if(static_cast<int>(type) == i)
		{
			priority = i;
		}
	}
}

bool sortCol::sort_col::operator() (const std::vector<double>& v1, const std::vector<double>& v2)
{
	if(v1[priority] == v2[priority])
		for(unsigned int i = 0; i < v1.size(); ++i)
		{
			if(priority != i && v1[i] != v2[i])
				return v1[i] < v2[i];
		}
	return v1[priority] < v2[priority];
}
