#include "exprtree_operator.hpp"

namespace experis {

namespace exprtree_operators {

const char* ExprTreePlus::GetName() const { return " + "; }
Value ExprTreePlus::Calc(Value a_left, Value a_right) const { return a_left + a_right; }

const char* ExprTreeMul::GetName() const { return " * "; }
Value ExprTreeMul::Calc(Value a_left, Value a_right) const { return a_left * a_right; }

const char* ExprTreeModulo::GetName() const { return " % "; }
Value ExprTreeModulo::Calc(Value a_left, Value a_right) const { return a_left % a_right; }

ExprTreePlus PLUS;
ExprTreeMul MUL;
ExprTreeModulo MODULO;

} // exprtree_operators

} // experis
