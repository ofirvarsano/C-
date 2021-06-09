#include "exprtree.hpp"

#include <iostream>

int main() {
	experis::ExprTree t(5);
	
	std::cout << t.ToString() << std::endl;
	experis::ExprTree z(t);
	
	t.ChangeLeftValue(8);
	std::cout << z.ToString() << std::endl;
	
	experis::ExprTree v1(2);
	
	experis::ExprTree v2(3);
	experis::ExprTree v3(4);
	experis::ExprTree v4(4, experis::exprtree_operators::MUL, 2);
	std::cout << v4.ToString() << std::endl;

	experis::ExprTree mul(v2, experis::exprtree_operators::MUL, v3);
	experis::ExprTree finalEx(v1, experis::exprtree_operators::PLUS, mul);
	
	std::cout << finalEx.ToString() << " = " << finalEx.Calc() << std::endl;
	
	finalEx.ChangeLeftValue(v4);
	finalEx.ChangeRightValue(5);
	
	experis::ExprTree v6(finalEx);
	std::cout << finalEx.ToString() << " = " << finalEx.Calc() << std::endl;
	
	return 0;
}
