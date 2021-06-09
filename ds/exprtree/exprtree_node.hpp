#ifndef _EXPRETREE_NODE_
#define _EXPRETREE_NODE_

#include <string>
#include "exprtree_operator.hpp"

namespace experis {

typedef exprtree_operators::Value Value;

class ExpressionNode {
public:
    //ExpressionNode(); = default;
    virtual ~ExpressionNode() {}
    //ExpressionNode(const ExpressionNode&) = default;

    virtual Value Calc() const = 0;
    virtual std::string ToString() const = 0;
    
private:
    ExpressionNode& operator=(const ExpressionNode&);
};

class NumberNode : public ExpressionNode {
public:
    NumberNode(Value a_num);
    ~NumberNode() {}
    //NumberNode(const NumberNode&);
    //NumberNode& operator=(const NumberNode&);
    
    virtual std::string ToString() const;
    virtual Value Calc() const { return m_num; };
private:
    Value m_num;
};

class OperatorNode : public ExpressionNode {
public:
	friend class ExprTree; 

    OperatorNode(const ExpressionNode& a_left, const exprtree_operators::ExprTreeOperator& a_operator, const ExpressionNode& a_right);
    ~OperatorNode();
    OperatorNode(const OperatorNode& a_opNode);

    virtual std::string ToString() const;
    virtual Value Calc() const;
    
private:
	OperatorNode& operator=(const OperatorNode&);
	std::string convertOperatorToChar(exprtree_operators::ExprTreeOperator& a_operator) const;
	
    ExpressionNode* m_left;
    ExpressionNode* m_right;
    const exprtree_operators::ExprTreeOperator& m_operator;
};


} //experis

#endif // _EXPRETREE_NODE_

