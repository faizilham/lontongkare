#include <iostream>
#include "lexer.h"

int main(){
	Lexer lexer(std::cin);

	int tok;

	while(1){
		std::cerr<<">> ";

		while ((tok = lexer.next()) != Token::_EOF){
			std::cout<<tok<<" ";
		}

		std::cout<<"\n";
	}

	return 0;
}