#ifndef DATA_READ_HPP_
#define DATA_READ_HPP_

#include <vector>
#include <string>

class data_read
{
public:
	static void read(std::vector<std::vector<double>>& table, std::string filename);
};

#endif //DATA_READ_HPP_
