#include "decision_tree.hpp"
#include "common.hpp"
#include <float.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "sort_col.hpp"

decision_tree::decision_tree(std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size)
{
	make_node(&root, first, last, size, giniResult(DBL_MAX, DBL_MAX, static_cast<colType>(0), 0, std::vector<bool>(static_cast<int>(colType::medv), 0)));
	print_tree(root, 0);
}

void decision_tree::make_node(tree_ptr** node, std::vector<std::vector<double>>::iterator first, std::vector<std::vector<double>>::iterator last, unsigned int size, giniResult g)
{
	giniResult temp = gini(first, last, size, g);
	
	/*if(temp.average != DBL_MAX)
		sortCol::sort(first, last, static_cast<colType>(temp.type));
	else
		sortCol::sort(first, last, static_cast<colType>(g.type));*/
	//std::cout<<temp.average<<" "<<g.average<<std::endl;
	if(temp.average == DBL_MAX)
	{
		std::vector<double> data;
		for(int i = 0; i < size; ++i)
			data.push_back(first[i][first[i].size()-2]);
		double average=0;
		std::cout<<"::"<<data.size()<<"::"<<std::endl;
		for(unsigned int i = 0; i < data.size(); ++i)
			average+=data[i];
		average/=data.size();
		*node = new tree_ptr(nodeType::data, average);
	}
	else
	{
		*node = new tree_ptr(nodeType::decision, temp.result, static_cast<colType>(temp.type));
		make_node(&(**node).R, first+temp.idx+1, last, size-temp.idx-1, temp); 
		make_node(&(**node).L, first, first+temp.idx, temp.idx+1, temp);
		
	}
}

void decision_tree::print_tree(tree_ptr* node, int count)
{
	
		
	if(node->R!=nullptr)
	{	
		print_tree(node->R, count+4);
	}
	for(int i = 0; i < count; ++i)
		std::cout<<" ";
	std::cout<<"----";
if(node->is_decision())
	{
		std::cout<<"decision: "<<node->get_decision_node_type()<<" "<<std::fixed<<std::showpoint<<std::setprecision(2)<<node->get_decision_node_val()<<std::endl;
	}
	else
	{
		std::cout<<"data: "<<std::fixed<<std::showpoint<<std::setprecision(2)<<node->get_data_node_val()<<std::endl;;
		
	}
	if(node->L!=nullptr)
	{
		print_tree(node->L, count+4);
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

double decision_tree::find_val_in_tree(std::vector<double>& data)
{
	return find_val(root, data);
		
}

double decision_tree::find_val(tree_ptr* node,std::vector<double>& data)
{
	if(!node->is_decision())
	{
		return node->get_data_node_val();
	}
	if(data[static_cast<int>(node->get_decision_node_type())]<node->get_decision_node_val())
	{
		return find_val(node->L, data);
	}	
	else
	{
		return find_val(node->R, data);
	}
	return 0; //never reached
}
