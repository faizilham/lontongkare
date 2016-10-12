#pragma once

#include <memory>
#include <vector>
#include "lexer.h"

class Parser{
private:
	Lexer lexer;
public:

	Parser(std::istream& stream): lexer(stream){}
	~Parser(){}

	void parse();
};

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