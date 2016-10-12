#include "parser.h"
#include "llvm/ADT/STLExtras.h"
#include <cstdio>

void Parser::change_input(std::istream& stream){
	lexer.reset(stream);
}

std::unique_ptr<ExprAST> Parser::error(const char *str){
	fprintf(stderr, "Error: %s\n", str);
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::parse_number(){
	auto result = llvm::make_unique<NumberExprAST>(lexer.number_value);
	lexer.next();
	return std::move(result);
}

std::unique_ptr<ExprAST> Parser::parse_paren(){
	lexer.next(); // eat (
	auto result = parse_expr();
	if (!result)
		return nullptr;

	if (lexer.current != ')')
		return error("expected ')'");
	lexer.next(); // eat )
	return result;
}

std::unique_ptr<ExprAST> Parser::parse_expr(){
	return nullptr;
}

void Parser::parse(){

}