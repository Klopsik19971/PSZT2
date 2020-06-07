#ifndef TREE_PTR_HPP_
#define TREE_PTR_HPP_

#include <vector>

#include "common.hpp"

enum nodeType{data, decision};

class tree_ptr
{
public:
	explicit tree_ptr(nodeType t, std::vector<double>& d);
	explicit tree_ptr(nodeType t, double d, colType type);
	colType get_decision_node_type();
	double get_decision_node_val();
	std::vector<double>& get_data_node_val();
	void add_to_data_node(double d);
private:
	const nodeType node_type;
	std::vector<double> data;
	const colType col_type;
	tree_ptr* L;
	tree_ptr* R;

	void check_node_type(nodeType t);
};

#endif //TREE_PTR_HPP_
