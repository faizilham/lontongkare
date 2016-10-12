#pragma once

#include <cctype>
#include <cstdlib>
#include <string>
#include <istream>


namespace Token{
	enum token {
		_EOF = -1,

		// definitions
		DEF = -2,
		EXTERN = -3,

		// primary expression
		IDENTIFIER = -4,
		NUMBER = -5,
		IF = -6,
		ELSE = -7
	};
}

class Lexer{
public:
	std::istream& stream;

	std::string identifier;
	double number_value;

	int last_char;
	int current;

	Lexer(std::istream& _stream) : stream(_stream), last_char(' ') {}
	~Lexer(){}
	int next();

private:
	int gettoken();
};