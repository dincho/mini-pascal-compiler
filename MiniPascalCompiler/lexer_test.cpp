//
//  lexer_test.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/13/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include <iostream>
#include "lexer_test.h"
#include "LexicalAnalyzer.h"

int lexer_test(int argc, const char *argv[])
{
	const char *filename;
    const char default_filename[] = "lex_test.prg";
    
    if (argc > 1) {
        filename = reinterpret_cast<const char *>(argv[1]);
    } else {
        filename = reinterpret_cast<const char *>(default_filename);
    }
	
    std::ofstream fout;
	fout.open( "lex_out.txt" );
	
	LexicalAnalyzer	comp(filename);
    
	fout << "SYMBOL SCANNED:" << std::endl << std::endl;
    
	do {
		switch( comp.symbol ) {
			case ident			: fout << "IDENTIFIER: " << comp.spelling << std::endl; break;
			case intconst		: fout << "INTEGER: " << comp.constant << std::endl; break;
			case charconst		: fout << "CHARACTER: " << static_cast<char>(comp.constant) << std::endl; break;
			case notop			: fout << "NOT" << std::endl; break;
			case andop			: fout << "AND" << std::endl; break;
			case orop			: fout << "OR" << std::endl; break;
			case times			: fout << "*" << std::endl; break;
			case divop			: fout << "DIV" << std::endl; break;
			case plus			: fout << "+" << std::endl; break;
			case minus			: fout << "-" << std::endl; break;
			case ltop			: fout << "<" << std::endl; break;
			case leop			: fout << "<=" << std::endl; break;
			case geop			: fout << ">=" << std::endl; break;
			case gtop			: fout << ">" << std::endl; break;
			case neop			: fout << "<>" << std::endl; break;
			case eqop			: fout << "=" << std::endl; break;
			case rightparent	: fout << ")" << std::endl; break;
			case leftparent		: fout << "(" << std::endl; break;
			case rightbracket	: fout << "]" << std::endl; break;
			case leftbracket	: fout << "[" << std::endl; break;
			case comma			: fout << "," << std::endl; break;
			case semicolon		: fout << ";" << std::endl; break;
			case period			: fout << "." << std::endl; break;
			case colon			: fout << ":" << std::endl; break;
			case becomes		: fout << ":=" << std::endl; break;
			case thru			: fout << ".." << std::endl; break;
			case programsy		: fout << "PROGRAM" << std::endl; break;
			case varsy			: fout << "VAR" << std::endl; break;
			case procsy			: fout << "PROCEDURE" << std::endl; break;
			case arraysy		: fout << "ARRAY" << std::endl; break;
			case ofsy			: fout << "OF" << std::endl; break;
			case beginsy		: fout << "BEGIN" << std::endl; break;
			case endsy			: fout << "END" << std::endl; break;
			case ifsy			: fout << "IF" << std::endl; break;
			case thensy			: fout << "THEN" << std::endl; break;
			case elsesy			: fout << "ELSE" << std::endl; break;
			case whilesy		: fout << "WHILE" << std::endl; break;
			case dosy			: fout << "DO" << std::endl; break;
			case readsy			: fout << "READ" << std::endl; break;
			case writesy		: fout << "WRITE" << std::endl; break;
			case othersy		: comp.error(10, comp.symbolposition ); break;
		} // switch
        
		comp.nextsymbol( );
	} while ( comp.symbol != period );
    
	fout << "." << std::endl;
	fout.close( );
    
	return 0;
}