#include "tree_ptr.hpp"

#include <iostream>

tree_ptr::tree_ptr(nodeType t, std::vector<double>& d)
	:node_type(t),
	 col_type(static_cast<colType>(0))
{
	data = d;
}

tree_ptr::tree_ptr(nodeType t, double d, colType type)
	:node_type(t),
	 col_type(type)
{
	data.push_back(d);
}

colType tree_ptr::get_decision_node_type()
{
	check_node_type(nodeType::decision);
	return col_type;
}

double tree_ptr::get_decision_node_val()
{
	check_node_type(nodeType::decision);
	return data[0];
}

std::vector<double>& tree_ptr::get_data_node_val()
{
	check_node_type(nodeType::data);
	return data;
}

void tree_ptr::add_to_data_node(double d)
{
	check_node_type(nodeType::data);
	data.push_back(d);
}

void tree_ptr::check_node_type(nodeType t)
{
	if(node_type != t)
		throw std::runtime_error("Wrong use of tree_ptr\n");
}
