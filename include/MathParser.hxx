#if not defined MATH_PARSER_HXX
#define MATH_PARSER_HXX

#include <vector>
#include <string>

#include "MathAST.hxx"

class MathParser{
private:
	std::vector<std::string> * m_tokens;
	size_t m_index = 0;

public:
	MathParser() = default;
	MathParser(const MathParser &) = delete;
	MathParser(MathParser &&) = delete;

	MathParser &operator= (const MathParser &) = delete;
	MathParser &operator= (MathParser &&) = delete;

	inline MathParser(std::vector<std::string> *tokens){
		MathParser::m_tokens = tokens;
	}

	~MathParser();

	Node *parse_expression();
	Node *parse_factor();
	Node *parse_term();

	SafeValue get_safevalue();

	inline Node * run(){
		MathParser::m_index = 0;
		if(MathParser::m_tokens == nullptr){
			std::cerr << "  [WARNING] Tokens are null, nothing to Evaluate, Retuning Nullptr" <<std::endl;
			return nullptr;
		}else if(MathParser::m_tokens->size() == 0){
			std::cerr << "  [WARNING] Empty Tokens, nothing to Evaluate, Retuning Nullptr" <<std::endl;
			return nullptr;
		}else{
			if(MathParser::m_tokens->size() == 1){
				return MathParser::parse_term();
			}else{
				return MathParser::parse_expression();
			}
		}
	}

	inline void set_tokens(std::vector<std::string> *tokens){
		MathParser::m_tokens = tokens;
	}

	inline OpType get_optype(){
		switch(MathParser::get_current_token()->data()[0]){
			case '+': return OpType::ADD;
			case '-': return OpType::SUB;
			case '*': return OpType::MUL;
			case '/': return OpType::DIV;
			default: return OpType::UNKOWN;
		}
	}

	inline bool check_token_mul_or_div(){
		char c = (*MathParser::get_current_token())[0];
		return c == '*' || c == '/';
	}

	inline bool check_token_add_or_sub(){
		char c = (*MathParser::get_current_token())[0];
		return c == '+' || c == '-';
	}

	inline void inc(){
		MathParser::m_index++;
	}

	inline void dec(){
		MathParser::m_index--;
	}

	inline const std::string * peak(){
 		return &((*MathParser::m_tokens)[MathParser::m_index+1]);
	}

	inline const std::string * get_current_token(){
		return &((*MathParser::m_tokens)[MathParser::m_index]);
	}

	inline bool out_of_bounds(){
		return MathParser::m_index >= MathParser::m_tokens->size();
	}

	inline bool in_bounds(){
		return MathParser::m_index < MathParser::m_tokens->size();
	}
};

#endif
