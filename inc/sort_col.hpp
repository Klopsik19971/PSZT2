#ifndef SORT_COL_HPP_
#define SORT_COL_HPP_

#include "common.hpp"

#include <vector>

class sortCol
{
public:
	static void sort(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, colType type);
	class sort_col
	{
	public:
		explicit sort_col(colType type);
		bool operator() (const std::vector<double>& v1, const std::vector<double>& v2);
	private:
		unsigned int priority;
	};
};

#endif //SORT_COL_HPP_
