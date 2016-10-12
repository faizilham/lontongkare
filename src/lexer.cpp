#include "lexer.h"

int Lexer::next(){
	return current = gettoken();
}

int Lexer::gettoken(){
	int prev_char;

	while(isspace(last_char)){
		last_char = stream.get();
	}

	// identifier & command tokens
	if (isalpha(last_char)){
		identifier = last_char;

		while (isalnum(last_char = stream.get())){
			identifier += last_char;
		}

		if (identifier == "def") return Token::DEF;
		if (identifier == "extern") return Token::EXTERN;

		return Token::IDENTIFIER;
	}

	// number token
	if (isdigit(last_char)){
		std::string numstr;

		// read before .
		do{
			numstr += last_char;
		} while (isdigit(last_char = stream.get()));
		

		// read after .
		if (last_char == '.'){
			numstr += last_char;

			while (isdigit(last_char = stream.get())){
				numstr += last_char;
			}
		}

		number_value = strtod(numstr.c_str(), 0);
		return Token::NUMBER;
	}

	// number token starts from comma or member operator
	if (last_char == '.'){
		prev_char = last_char;
		last_char = stream.get();

		// number token
		if (isdigit(last_char)){
			std::string numstr;

			numstr += prev_char + last_char;

			while (isdigit(last_char = stream.get())){
				numstr += last_char;
			}
		
			number_value = strtod(numstr.c_str(), 0);
			return Token::NUMBER;
		}

		return '.';
	}

	// skip comment until line break or EOF
	if (last_char == '#') {
		do {
			last_char = stream.get();
		} while (last_char != EOF && last_char != '\n' && last_char != '\r');

		if (last_char != EOF)
			return gettoken();
	}

	// skip EOF
	if (last_char == EOF) return Token::_EOF;

	// output other as its char value
	prev_char = last_char;
	last_char = stream.get();
  	return prev_char;
}