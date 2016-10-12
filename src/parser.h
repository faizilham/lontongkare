#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include "lexer.h"

/*** AST ***/

class ExprAST {
public:
	virtual ~ExprAST() {}
};

// number
class NumberExprAST : public ExprAST {
public:
	double val;
	NumberExprAST(double val) : val(val) {}
};

// variable reference
class VariableExprAST : public ExprAST {
public:
	std::string name;
	VariableExprAST(const std::string &name) : name(name) {}
};

// binary operator expression
class BinaryExprAST : public ExprAST {
public:
	char op;
	std::unique_ptr<ExprAST> lhs, rhs;
	BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
	: op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

// function call
class CallExprAST : public ExprAST {
public:
	std::string callee;
	std::vector<std::unique_ptr<ExprAST>> args;
	CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST>> args)
 	: callee(callee), args(std::move(args)) {}
};

// function prototype
class PrototypeAST {
public:
	std::string name;
	std::vector<std::string> args;

	PrototypeAST(const std::string &name, std::vector<std::string> args)
	: name(name), args(std::move(args)) {}
};

// function declaration with body
class FunctionAST {
public:
	std::unique_ptr<PrototypeAST> proto;
	std::unique_ptr<ExprAST> body;
	FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body)
	: proto(std::move(proto)), body(std::move(body)) {}
};

/*** AST ***/

class Parser{
private:
	Lexer lexer;
	std::unique_ptr<ExprAST> error(const char *str);
	std::unique_ptr<PrototypeAST> errorp(const char *str);
	
	std::unique_ptr<ExprAST> parse_number();
	std::unique_ptr<ExprAST> parse_paren();
	std::unique_ptr<ExprAST> parse_variable();
	std::unique_ptr<ExprAST> parse_call_expr();
	std::unique_ptr<ExprAST> parse_primary_expr();

	std::unique_ptr<ExprAST> parse_binary_expr();
	std::unique_ptr<ExprAST> parse_expr();
	

	std::unique_ptr<PrototypeAST> parse_proto();
	std::unique_ptr<FunctionAST> parse_def();
public:

	Parser(std::istream& stream): lexer(stream){}
	~Parser(){}

	void change_input(std::istream& stream);

	void parse();
};