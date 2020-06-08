#include "tree_ptr.hpp"

#include <iostream>

tree_ptr::tree_ptr(nodeType t, double d)
	:node_type(t),
	 col_type(static_cast<colType>(0))
{
	data = d;
	L = nullptr;
	R = nullptr;
}

tree_ptr::tree_ptr(nodeType t, double d, colType type)
	:node_type(t),
	 col_type(type)
{
	data = d;
}

colType tree_ptr::get_decision_node_type()
{
	check_node_type(nodeType::decision);
	return col_type;
}

double tree_ptr::get_decision_node_val()
{
	check_node_type(nodeType::decision);
	return data;
}

double tree_ptr::get_data_node_val()
{
	check_node_type(nodeType::data);
	return data;
}

bool tree_ptr::is_decision()
{
	if(node_type == nodeType::decision)
		return true;	
	return false;
}

void tree_ptr::check_node_type(nodeType t)
{
	if(node_type != t)
	{
		throw std::runtime_error("Wrong use of tree_ptr\n");
	}
}
