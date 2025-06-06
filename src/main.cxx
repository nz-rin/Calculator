
#include <iostream>
#include <string>
#include <vector>

#include "MathLexer.hxx"
#include "MathParser.hxx"
#include "MathAST.hxx"
#include "MathEvaluate.hxx"

void eval(std::string expr){
	std::optional<std::vector<std::string>> token = MathLexer::lex_string(expr);
	if(token.has_value()){
		if( !MathLexer::validate_expressions(*token)){
			std::cerr << "Invalid Expression" << std::endl;
			return;
		}
		MathLexer::fold_tokens(*token);

		MathParser p = MathParser();
		p.set_tokens(&*token);
		Node *node = p.run();

		if(!node){
			return;
		}
		SafeValue val = evaluate(node);
		std::string answer = (val.num_type == NumType::I64)? std::to_string(val.i64) : std::to_string(val.f64);
		std::cout << " Answer: " << answer << "\n";
		delete node;
	}else{
		std::cerr << "Invalid Token Found" << std::endl;
	}
}

int main(int argc, const char * argv[]){

	if(argc <= 1){
		std::cerr <<
			"  Insufficiate Arguements\n"
			"  Usage:\n"
			"     calcxx \"EXPRESSION\"    - Evaluates math expression\n"
			"     calcxx -i                - creates an interactive session for evaluting expression until you quit" <<
		std::endl;
		return 1;
	}

	if(argv[1][0] == '-' && argv[1][1] == 'i'){
		std::cout << "  Q to Quit" <<std::endl;
		std::string expr = "";
		expr.reserve(1024);
		while(true){
			std::cout << " > ";
			std::getline(std::cin, expr);
			if(expr.c_str()[0] == 'q' || expr.c_str()[0] == 'Q' ){
				break;
			}

			eval(expr);
		}
	}else{
		eval(argv[1]);
	}

	return 0;
}
