#include "decision_tree.hpp"
#include "common.hpp"
#include <float.h>
#include <iostream>

decision_tree::decision_tree(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size)
{
	make_node(&root, first, last, size, giniResult(DBL_MAX, DBL_MAX, static_cast<colType>(0), 0, std::vector<bool>(static_cast<int>(colType::medv), 0)));
	print_tree(root);
}

void decision_tree::make_node(tree_ptr** node, std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult g)
{
	giniResult temp = gini(first, last, size, g);
	/*std::cout<<"---------------------------------------------"<<std::endl;
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < first[i].size(); ++j)
		{
			std::cout<<first[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"---------------------------------------------"<<std::endl<<std::endl;*/
	if(temp.average == DBL_MAX)
	{
		std::vector<double> data;
		for(int i = 0; i < size; ++i)
			data.push_back(first[i][first[i].size()-1]);
		*node = new tree_ptr(nodeType::data, data);
	}
	else
	{
		*node = new tree_ptr(nodeType::decision, temp.result, static_cast<colType>(temp.type));
		make_node(&(**node).L, first, first+temp.idx, temp.idx+1, temp);
		make_node(&(**node).R, first+temp.idx+1, last, size-temp.idx-1, temp); 
	}
}

void decision_tree::print_tree(tree_ptr* node)
{
	if(node->is_decision())
	{
		std::cout<<"decision: "<<node->get_decision_node_type()<<" "<<node->get_decision_node_val()<<std::endl;
	}
	else
	{
		std::vector<double> temp = node->get_data_node_val();
		std::cout<<"data: "<<temp.size()<<std::endl;;
		for(int i = 0; i < temp.size(); ++i)
		{
			std::cout<<temp[i]<<" ";
		}
		std::cout<<std::endl;
	}
	if(node->L!=nullptr)
	{
		std::cout<<"L: ";
		print_tree(node->L);
	}	
	if(node->R!=nullptr)
	{	
		std::cout<<"R: ";
		print_tree(node->R);
	}
}

decision_tree::~decision_tree()
{
	destroy_node(root);
}

void decision_tree::destroy_node(tree_ptr* node)
{
	if(node->L!=nullptr)
		destroy_node(node->L);
	if(node->R!=nullptr)
		destroy_node(node->R);
	delete node;
}
