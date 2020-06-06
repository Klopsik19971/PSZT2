#include "data_read.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

void data_read::read(std::vector<std::vector<double>>& table, std::string filename)
{
	if(filename.compare(filename.size() - 4, 4, ".csv"))
		throw std::runtime_error("Unable to open file");
	std::fstream fs;
	fs.open(filename.c_str(), std::fstream::in);
	
	if(!fs.is_open())
		throw std::runtime_error("Unable to open file");

	std::string line;
	std::getline(fs, line);
	while(std::getline(fs, line))
	{
		std::istringstream buf(line);
		std::string token;
		table.resize(table.size()+1);
		while(std::getline(buf, token, ';'))
		{
			table[table.size()-1].push_back(atof(token.c_str()));
		}
	}
}
