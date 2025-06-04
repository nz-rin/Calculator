
#include <cassert>
#include <iostream>

#include "MathEvaluate.hxx"

#define SILENCE_COMPILER(x) x

SafeValue evaluate(Node *node){
	SafeValue __lhs = (node->get_lhs()->check_empty()) ?
		node->get_lhs()->get_safevalue() :
		evaluate(node->get_lhs());
	;
	SafeValue __rhs = (node->get_rhs()->check_empty()) ?
		node->get_rhs()->get_safevalue() :
		evaluate(node->get_rhs())
	;

	if(__lhs.num_type == F64 || __rhs.num_type == F64 ){
		__lhs = Node::get_f64(__lhs);
		__rhs = Node::get_f64(__rhs);
		switch(node->get_optype()){
			case OpType::ADD : return { NumType::F64, .f64 = ( __lhs.f64 + __rhs.f64) };
			case OpType::SUB : return { NumType::F64, .f64 = ( __lhs.f64 - __rhs.f64) };
			case OpType::MUL : return { NumType::F64, .f64 = ( __lhs.f64 * __rhs.f64) };
			case OpType::DIV : return { NumType::F64, .f64 = ( __lhs.f64 / __rhs.f64) };
			case OpType::NOP : {
				std::cerr << "  ERROR : Attempted to Evaluate a NOP in I64 Evaluate in : " __FILE__ << std::endl;
				exit(EXIT_FAILURE);
			};
			case OpType::UNKOWN:
			{
				std::cerr << "  FATAL ERROR : UNKOWN OPERATOR reached in I64 Evaluate in : " __FILE__ << std::endl;
				exit(EXIT_FAILURE);
			};
		}
	}else{
		__lhs = Node::get_i64(__lhs);
		__rhs = Node::get_i64(__rhs);

		switch(node->get_optype()){
			case OpType::ADD : return { NumType::I64, .i64 = ( __lhs.i64 + __rhs.i64) };
			case OpType::SUB : return { NumType::I64, .i64 = ( __lhs.i64 - __rhs.i64) };
			case OpType::MUL : return { NumType::I64, .i64 = ( __lhs.i64 * __rhs.i64) };
			case OpType::DIV :
			{
				if(__lhs.i64 % __rhs.i64 != 0){
					return { NumType::F64, .f64 = ( Node::get_f64(__lhs).f64 / Node::get_f64(__rhs).f64 ) };
				}
				else{
					return { NumType::I64, .i64 = ( __lhs.i64 / __rhs.i64) };
				}
			};
			case OpType::NOP : {
				std::cerr << "  ERROR : Attempted to Evaluate a NOP in F64 Evaluate in : " __FILE__ << std::endl;
				exit(EXIT_FAILURE);
			};
			case OpType::UNKOWN: {
				std::cerr << "  FATAL ERROR : UNKOWN OPERATOR reached in F64 Evaluate in : " __FILE__ << std::endl;
				exit(EXIT_FAILURE);
			};
		}

	}
	//THIS STATEMENT SHOULD BE UNREACHABLE
	assert(false && "  Evaluate Fell through, likely do to a SafeValue not been an F64 or I64");
	SILENCE_COMPILER(return {});
}
