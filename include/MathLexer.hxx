
#ifndef MATH_LEXER_HXX
#define MATH_LEXER_HXX

#include <string.h>
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

	inline std::vector<std::string> __lex(const char *math, size_t string_size){
		bool failed = false;
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
				std::cerr << "\t[ERROR] Invalid Token: \"" << math[i] << "\n";
				failed = true;
				i++;
			}
		}

		if(failed){
			std::cerr << "\t[ERROR] Invalid Tokens where found, Lexing Aborted\n";
			exit(EXIT_FAILURE);
		}

		return token;
	}

	///NOTE, Ensure string is null terminated, use the variant with str_len for safe working with segments
	inline std::vector<std::string> c_str(const char *math){
		size_t str_len= strlen(math);
		return __lex(math, str_len);
	}

	inline std::vector<std::string> lex_segment(const char *math, size_t str_len){
		return __lex(math, str_len);
	}

	inline std::vector<std::string> lex_string(std::string math){
		return __lex(math.data(), math.length());
	}

	inline std::vector<std::string> lex_string(std::string_view math){
		return __lex(math.data(), math.length());
	}

};
#endif
