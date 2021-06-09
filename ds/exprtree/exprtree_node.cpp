#include "exprtree_node.hpp"
#include "exprtree_operator.hpp"

namespace experis {

NumberNode::NumberNode(Value a_num) : m_num(a_num)
{}

std::string NumberNode::ToString() const {
	return std::to_string(m_num);
}

OperatorNode::OperatorNode(const ExpressionNode& a_left, const exprtree_operators::ExprTreeOperator& a_operator, const ExpressionNode& a_right)
: m_operator(a_operator)
{
	if(typeid(a_left) == typeid(OperatorNode&)) {
		m_left = new OperatorNode(dynamic_cast<const OperatorNode&>(a_left));
	}
	else {
		m_left = new NumberNode(dynamic_cast<const NumberNode&>(a_left));
	}
	
	if(typeid(a_right) == typeid(OperatorNode&)) {
		m_right = new OperatorNode(dynamic_cast<const OperatorNode&>(a_right));
	}
	else {
		m_right = new NumberNode(dynamic_cast<const NumberNode&>(a_right));
	}
}

OperatorNode::~OperatorNode() {
	delete m_left;
	delete m_right;
}

Value OperatorNode::Calc() const {
	//return exprtree_operators::OPERATORS_DEFINITION[m_operator]->Calc(m_left->Calc(), m_right->Calc());
	return m_operator.Calc(m_left->Calc(), m_right->Calc());
}

std::string OperatorNode::ToString() const {
	return "(" + m_left->ToString() + m_operator.GetName() + m_right->ToString() + ")" ;
}

/*
std::string OperatorNode::convertOperatorToChar(exprtree_operators::ExprTreeOperator& a_operator) const {
	return a_operator.GetName();
	//return exprtree_operators::OPERATORS_DEFINITION[a_operator]->GetName();
}
*/

OperatorNode::OperatorNode(const OperatorNode& a_opNode)
: m_operator(a_opNode.m_operator) {
    if(typeid(a_opNode.m_left) == typeid(OperatorNode*)) {
		m_left = new OperatorNode(dynamic_cast<OperatorNode&>(*a_opNode.m_left));
	}
	else {
		m_left = new NumberNode(dynamic_cast<NumberNode&>(*a_opNode.m_left));
	}
	
	if(typeid(a_opNode.m_right) == typeid(OperatorNode&)) {
		m_right = new OperatorNode(dynamic_cast<OperatorNode&>(*a_opNode.m_right));
	}
	else {
		m_right = new NumberNode(dynamic_cast<NumberNode&>(*a_opNode.m_right));
	}
}

/*
OperatorNode::OperatorNode(const OperatorNode& a_opNode) 
: m_operator(a_opNode.m_operator) {
	ExpressionNode* left;
    ExpressionNode* right;
    if(typeid(a_opNode.m_left) == typeid(OperatorNode*)) {
		left = new OperatorNode(dynamic_cast<OperatorNode&>(*a_opNode.m_left));
	}
	else {
		left = new NumberNode(dynamic_cast<NumberNode&>(*a_opNode.m_left));
	}
	
	if(typeid(a_opNode.m_right) == typeid(OperatorNode&)) {
		right = new OperatorNode(dynamic_cast<OperatorNode&>(*a_opNode.m_right));
	}
	else {
		right = new NumberNode(dynamic_cast<NumberNode&>(*a_opNode.m_right));
	}
	delete m_left;
	delete m_right;
	m_left = left;
	m_right = right;
}
*/

} // experis
