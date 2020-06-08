#ifndef DECISION_TREE_HPP_
#define DECISION_TREE_HPP_

#include <vector>
#include "tree_ptr.hpp"
#include "calculate_gini.hpp"

class decision_tree
{
public:
	explicit decision_tree(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size);
	void print_tree(tree_ptr* node);
	~decision_tree();
	double find_val_in_tree(std::vector<double>& data);
	
private:
	tree_ptr* root;
	void make_node(tree_ptr** node, std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult g);
	void destroy_node(tree_ptr* node);
	double find_val(tree_ptr* node,std::vector<double>& data);
};

#endif //DECISION_TREE_HPP_
