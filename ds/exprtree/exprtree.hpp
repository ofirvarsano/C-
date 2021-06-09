#ifndef _EXPRESSION_TREE_
#define _EXPRESSION_TREE_

#include "exprtree_node.hpp"
#include <string>

namespace experis {

class ExprTree {
public:
    ExprTree(const Value a_ex);
    ExprTree(const ExprTree& a_ex1, const exprtree_operators::ExprTreeOperator& a_op, const ExprTree& a_ex2);
    ~ExprTree();
    ExprTree(const ExprTree&);
	
	ExpressionNode& Get() const { return *m_tree; }
    exprtree_operators::Value Calc() const;
    std::string ToString() const;
    void ChangeLeftValue(const ExprTree& a_ex1);
    void ChangeRightValue(const ExprTree& a_ex1);

private:
	ExprTree& operator=(const ExprTree&);
	
	ExpressionNode* m_tree;
};

} //experis

#endif // _EXPRESSION_TREE_

