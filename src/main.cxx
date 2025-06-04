#include <iostream>
#include <string>
#include <vector>

#include "MathLexer.hxx"
#include "MathParser.hxx"
#include "MathAST.hxx"
#include "MathEvaluate.hxx"

int main(void){
	std::vector<std::string> token = MathLexer::c_str("10/2/(5+5)*3");

	MathParser p = MathParser();
	p.set_tokens(&token);
	Node *node = p.run();

	if(!node){
		return 0;
	}

	SafeValue val = evaluate(node);
	delete node;

	std::string answer = (val.num_type == NumType::I64)? std::to_string(val.i64) : std::to_string(val.f64);
	std::cout << "Answer: " << answer << "\n";

	std::cout << "Run Successfull" << std::endl;
	return 0;
}
