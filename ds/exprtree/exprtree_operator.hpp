#ifndef _EXPRTREE_OPERATOR_
#define _EXPRTREE_OPERATOR_

namespace experis {

namespace exprtree_operators {

typedef int Value;

//enum Operator { PLUS, MUL, MODULO };

class ExprTreeOperator {
public:
	virtual ~ExprTreeOperator() {}
	virtual const char* GetName() const = 0;
	virtual Value Calc(Value a_left, Value a_right) const = 0;
};

class ExprTreePlus : public ExprTreeOperator {
	const char* GetName() const;
	Value Calc(Value a_left, Value a_right) const;
};

class ExprTreeMul : public ExprTreeOperator {
	const char* GetName() const;
	Value Calc(Value a_left, Value a_right) const;
};

class ExprTreeModulo : public ExprTreeOperator {
	const char* GetName() const;
	Value Calc(Value a_left, Value a_right) const;
};

extern ExprTreePlus PLUS;
extern ExprTreeMul MUL;
extern ExprTreeModulo MODULO;

} // exprtree_operators

} // experis


#endif // _EXPRTREE_OPERATORS_
