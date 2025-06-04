#include "MathAST.hxx"

#include <iostream>


Node::Node(Node *lhs, Node *rhs, SafeValue value, OpType op){
	Node::m_lhs = lhs;
	Node::m_rhs = rhs;
	Node::m_value = value;
	Node::m_op = op;
}

Node::~Node(){
	delete Node::m_lhs;
	delete Node::m_rhs;
}

bool Node::check_empty(){
	return Node::m_op == OpType::NOP;
}

Node *Node::get_lhs(){
	return Node::m_lhs;
}

Node *Node::get_rhs(){
	return Node::m_rhs;
}

SafeValue Node::get_safevalue(){
	return Node::m_value;
}

void Node::set_safevalue(SafeValue sv){
	Node::m_value = sv;
}

SafeValue Node::get_f64(SafeValue &s){
	if (s.num_type == I64){
		return {NumType::F64, .f64 = static_cast<double>(s.i64)};
	}else{
		return s;
	}
}

SafeValue Node::get_i64(SafeValue &s){
	if (s.num_type == F64){
		return {NumType::I64, .i64 = static_cast<ssize_t>(s.f64)};
	}else{
		return s;
	}
}

//unused
void Node::set_optype(OpType op){
	Node::m_op = op;
}

