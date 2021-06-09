#include "exprtree.hpp"

namespace experis {

ExprTree::ExprTree(const Value a_ex)
: m_tree(new NumberNode(a_ex))
{}


ExprTree::ExprTree(const ExprTree& a_ex1, const exprtree_operators::ExprTreeOperator& a_op, const ExprTree& a_ex2)
: m_tree(new OperatorNode(a_ex1.Get(), a_op, a_ex2.Get()))
{}

ExprTree::ExprTree(const ExprTree& a_ex) {
	if(typeid(*a_ex.m_tree) == typeid(OperatorNode&)) {
		m_tree = new OperatorNode(dynamic_cast<OperatorNode&>(*a_ex.m_tree));
	}
	else {
		m_tree = new NumberNode(dynamic_cast<NumberNode&>(*a_ex.m_tree));
	}
}

ExprTree::~ExprTree() {
	delete m_tree;
}

Value ExprTree::Calc() const {
	return m_tree->Calc();
}

std::string ExprTree::ToString() const {
	return m_tree->ToString();
}

void ExprTree::ChangeLeftValue(const ExprTree& a_ex) {
	ExpressionNode* tempLeft;
	if(typeid(*m_tree) == typeid(OperatorNode)) {
		tempLeft = new NumberNode(a_ex.Calc());
		
		delete ((OperatorNode*)m_tree)->m_left;
		((OperatorNode*)m_tree)->m_left = tempLeft;
	}
}

void ExprTree::ChangeRightValue(const ExprTree& a_ex) {
	ExpressionNode* tempRight;
	if(typeid(*m_tree) == typeid(OperatorNode)) {
		tempRight = new NumberNode(a_ex.Calc());
		
		delete ((OperatorNode*)m_tree)->m_right;
		((OperatorNode*)m_tree)->m_right = tempRight;
	}
}

} // experis

