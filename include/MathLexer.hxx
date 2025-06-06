
#ifndef MATH_LEXER_HXX
#define MATH_LEXER_HXX

#include <cstring>
#include <cassert>

#include <optional>
#include <cstring>
#include <iostream>
#include <vector>


namespace MathLexer{

	inline bool _bracket(char c){
		return c == '(' || c == ')';
	}

	inline bool _operator(char c){
		return c == '+' || c == '-' || c == '*' || c == '/';
	}

	inline bool _whitespace(char c){
		return c == ' ' || c == '\t' || c == '\n';
	}
	inline bool _numeric(char c){
		return c >= '0' && c <= '9';
	}
	inline bool _numeric_exception(char c){
		return c == '.' || c == 'e' || c == ',';
	}
	inline bool _valid_number(char c){
		return _numeric(c)  || _numeric_exception(c);
	}

	inline void fold_tokens(std::vector<std::string> &tokens){
		size_t i = 0;
		while(i < tokens.size()){
			if(tokens[i][0] == '+' || tokens[i][0] == '-'){
				i++;
				//fold ++ int +
				if(tokens[i][0] == '+' && tokens[i-1][0] == '+'){
					tokens.erase(tokens.begin() + i);
				//fold -- int +
				}else if(tokens[i][0] == '-' && tokens[i-1][0] == '-'){
					tokens.erase(tokens.begin() + i);
					tokens[i-1] = '+';
				// remove unnecessary + sign
				}else if(tokens[i][0] == '+' ){
					tokens.erase(tokens.begin() + i);
				// change '-' 'NUMBER' into '-NUMBER', i.e negative number
				}else if (tokens[i][0] == '-'){
					tokens.erase(tokens.begin() + i);
					tokens[i-1] = '-';
				}
			}else if (tokens[i][0] == '('){
				i++;
				// remove unnecessary + sign
				if(tokens[i][0] == '+' ){
					tokens.erase(tokens.begin() + i);
				// change '(' '-' 'NUMBER' into '(' '-NUMBER', i.e negative number inside of bracketed expr
				}else if (tokens[i][0] == '-'){
					char c = tokens[i][0];
					tokens.erase(tokens.begin() + i);
					tokens[i] = c + tokens[i];
					i++;
				}
			}else{
				i++;
			}
		}
	}

	inline bool validate_expressions(const std::vector<std::string> &tokens){
		size_t _bracket_count = 0, i=0;
		while(i < tokens.size()){
			if(tokens[i][0] == '('){
				_bracket_count++;
				i++;

				//if true, failed, incomplete EXPRESSION
				if(i >= tokens.size()){
					return false;
				}

				if(_numeric(tokens[i][0])){
					continue;
				//sign
				}else if(tokens[i][0] == '+' || tokens[i][0] == '-'){
					i++;
					continue;
				}

			}else if(tokens[i][0] == ')'){
				_bracket_count--;
				i++;

				if(i >= tokens.size()){
					return _bracket_count == 0;
				}

				//next must be and operator
				if( !_operator(tokens[i][0]) ){
					return false;
				}
				i++;
				//if true, failed, stray operator, ') OPERATOR'
				if(i >= tokens.size()){
					return false;
				}

				//NUMBER, -+ OPERATOR or EXPRS fine
				if( (tokens[i][0] == '/' || tokens[i][0] == '*') ){
					return false;
				}
				//operator if it falls throught
				if(_operator(tokens[i][0]))
					i++;

			//NUMBER
			}else if ( _numeric(tokens[i][0]) ){
				i++;
				if(i >= tokens.size()){
					return _bracket_count == 0;
				}

				if(tokens[i][0] == ')'){
					continue;
				}

				//next must be OPERATOR
				if( !_operator(tokens[i][0]) ){
					return false;
				}
				i++;
				//if true, failed, stray operator, 'EXPR OPERATOR'
				if(i >= tokens.size()){
					return false;
				}

				//number or -+operator or exprs fine
				if( (tokens[i][0] == '/' || tokens[i][0] == '*') ){
					return false;
				}
				//operator if it falls throught
				if(_operator(tokens[i][0])){
					i++;
					//stray OPERATOR
					if(i >= tokens.size()){
						return false;
					}
				}
			}else{
				return false;
			}
		}
		//assert(false && __FILE__" __validate_expressions() fell through");
		return _bracket_count==0;
	}

	inline std::optional<std::vector<std::string>> __lex(const char *math, size_t string_size){
		std::vector<std::string> token = std::vector<std::string>();

		std::string sb = "";
		sb.reserve(128);
		// if ur number string is larger than 10^128, what are you doing??? get some help

		size_t i=0;
		while (i < string_size){
			if( _whitespace( math[i] ) ){
				i++;
			}else if( _numeric( math[i] ) ){
				sb.clear();
				while( _valid_number(math[i]) && i < string_size){
					sb += math[i];
					i++;
				}
				token.push_back(sb);
			}
			//For Tokens that are single size
			else if( _operator( math[i] ) || _bracket( math[i] ) ){
				sb.clear();
				sb += math[i];
				token.push_back(sb);
				i++;
			}else{
#if defined LOG_ERROR
				std::cerr << "\t[ERROR] Invalid Token: \"" << math[i] << "\"\n";
#endif
				return std::nullopt;
				i++;
			}
		}

		return token;
	}

	///NOTE, Ensure string is null terminated, use the variant with str_len for safe working with segments
	inline std::optional<std::vector<std::string>> c_str(const char *math){
		size_t str_len= strlen(math);
		return __lex(math, str_len);
	}

	inline std::optional<std::vector<std::string>> lex_segment(const char *math, size_t str_len){
		return __lex(math, str_len);
	}

	inline std::optional<std::vector<std::string>> lex_string(std::string math){
		return __lex(math.data(), math.length());
	}

	inline std::optional<std::vector<std::string>> lex_string(std::string_view math){
		return __lex(math.data(), math.length());
	}

};
#endif
