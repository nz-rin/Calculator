#if not defined MATH_AST_HXX
#define MATH_AST_HXX

#include <iostream>

#include <cstdint>
#include <sys/types.h>

enum NumType{
	I64,
	F64,
	NUM_UNINIT
};

enum OpType{
	ADD,
	SUB,
	MUL,
	DIV,

	NOP,
	UNKOWN// For errors
};

struct SafeValue{
	NumType num_type = NumType::NUM_UNINIT;
	union{
		ssize_t  i64 = 0;
		double 	 f64;
	};
};

class Node{
private:
	Node *m_lhs = nullptr;
	Node *m_rhs = nullptr;

	OpType m_op = OpType::NOP;
	SafeValue m_value;

public:
	Node(Node *lhs, Node *rhs, SafeValue value, OpType op);
	~Node();
	Node() = delete;
	Node(const Node &) = delete;
	Node(Node &&) = delete;
	Node &operator = (Node &) = delete;
	Node &operator = (Node &&) = delete;

	static SafeValue get_f64(SafeValue &s);
	static SafeValue get_i64(SafeValue &s);

	bool check_empty();

	Node *get_lhs();
	Node *get_rhs();

	SafeValue get_safevalue();
	void set_safevalue(SafeValue sv);

	void set_optype(OpType op);

	inline OpType get_optype(){
		return Node::m_op;
	}

	inline void print_optype(){
		switch(Node::m_op){
			case OpType::ADD :{
				std::cout << "ADD" << std::endl;
				break;
			}
			case OpType::SUB :{
				std::cout << "SUB" << std::endl;
				break;
			}
			case OpType::MUL :{
				std::cout << "MUL" << std::endl;
				break;
			}
			case OpType::DIV :{
				std::cout << "DIV" << std::endl;
				break;
			}
			case OpType::NOP :{
				std::cout << "NOP" << std::endl;
				break;
			}
			case OpType::UNKOWN:{
				std::cout << "NOP" << std::endl;
				break;
			}
		}
	}

};

#endif
