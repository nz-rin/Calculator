
#include "MathAST.hxx"

#include <vector>
#include <string>
#include <iostream>

#include "MathParser.hxx"


MathParser::~MathParser(){
	MathParser::m_tokens = nullptr;
}

SafeValue MathParser::get_safevalue(){
	const std::string * _current_token = MathParser::get_current_token();
	SafeValue _sret;
	for(size_t i = 0; i < _current_token->length(); i++){
		if( (*_current_token)[i] == '.'){
			_sret.num_type = NumType::F64;
			_sret.f64 = std::stod(*_current_token);
			return _sret;
		}
	}
	_sret.num_type = NumType::I64;
	_sret.i64 = std::stol(*_current_token);
	return _sret;
}

Node * MathParser::parse_expression(){
	Node *_node = MathParser::parse_factor();

	while(MathParser::in_bounds() && MathParser::check_token_add_or_sub() ){
		OpType _optype = MathParser::get_optype();
		inc();
		Node * _rhs = MathParser::parse_factor();
		_node = new Node(_node, _rhs, {}, _optype);
	}
	return _node;
}

Node * MathParser::parse_factor(){
	Node *_node = MathParser::parse_term();

	while(MathParser::in_bounds() && MathParser::check_token_mul_or_div() ){
		OpType _optype = MathParser::get_optype();
		inc();
		Node * _rhs = MathParser::parse_term();
		_node = new Node(_node, _rhs, {}, _optype);
	}
	return _node;
}

Node * MathParser::parse_term(){
	if((*MathParser::get_current_token())[0] == '('){
		inc();
		Node *_node = MathParser::parse_expression();

		//Inc needed to Skip ')'
		inc();
		return _node;
	}else{
		auto _sv = MathParser::get_safevalue();
		inc();
		return new Node(nullptr, nullptr, _sv, OpType::NOP);
	}
}
