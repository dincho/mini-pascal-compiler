//
//  LexicalAnalyzer.h
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/13/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

///////////////////////////////////////////////////////////////////
//////////////////////// Lexical Analysis /////////////////////////
///////////////////////////////////////////////////////////////////
//																 //
// The scan module enables the lexical scanning of symbols in	 //
// the source stream through the accesible procedure NEXTSYMBOL. //
//																 //
// When caled, NEXTSYMBOL scans the next language symbol in the  //
// input stream and returns a representation of it in the		 //
// following accessible variables :								 //
//																 //
//																 //
//   SYMBOL		In all cases SYMBOL represents the symbol		 //
//				scanned, as defined by the type SYMBOLTYPE .	 //
//																 //
//																 //
//   SPELLING	When SYMBOL = IDENT , SPELLING holds the		 //
//				(significant) characters of the identifier		 //
//				scanned .										 //
//																 //
//																 //
//   CONSTANT	When SYMBOL = INTCONST or CHARCONST , CONSTANT   //
//				holds the integer representation of the			 //
//				constant .										 //
//																 //
//																 //
// The starting position of the symbol scanned is left in		 //
// the accessible variable SYMBOLPOSITION .						 //
//																 //
// The scanner (lexical analizer) report errors with the		 //
// folowing codes :												 //
//																 //
//  1 .... INTEGER CONSTANT TOO LARGE							 //
//  2 .... CHARACTER CONSTANT INCOMPLETE						 //
//																 //
///////////////////////////////////////////////////////////////////
//////////////////////// Lexical Analysis /////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef MiniPascalCompiler_LexicalAnalyzer_h
#define MiniPascalCompiler_LexicalAnalyzer_h

#include "Source.h"
#include <unordered_map>

///////////////////////////
//// Variables & Types ////
///////////////////////////
// constants
const	int		alfalength		= 9;
const	int		nowordsymbols	= 28;
const	int		maxinteger		= 32767;

// types
typedef char alfa[alfalength+1]; // !!! +1 for the string terminator -> \0

typedef enum symboltype {
	ident, intconst, charconst, //3
	notop, andop, orop, //6
	times, divop, plus, minus, //10
	ltop, leop, geop, gtop, neop, eqop, //25
	rightparent, leftparent, leftbracket, rightbracket, //29
	comma, semicolon, period, colon, becomes, thru, //35
	programsy, varsy, procsy, arraysy, ofsy, //40
	beginsy, endsy, ifsy, thensy, elsesy, whilesy, dosy, //47
	readsy, writesy,
	othersy
} symboltype;

typedef struct wordsymbolsrec {
	symboltype	symbolvalue;
	alfa		symbolspelling;
} wordsymbolsrec;

///////////////////////////
//// Class Declaration ////
///////////////////////////
class LexicalAnalyzer : public Source {
private:	// variables
	// variables for handling symbols and scans
	wordsymbolsrec	wordsymbols[nowordsymbols];
	int				lastoflength[alfalength+1];
    std::unordered_map<std::string, wordsymbolsrec> symbolsMap;
    
public:		// variables
	// variables for handling symbols and scans
	textposition	symbolposition;
	symboltype		symbol;
	int				constant;
	alfa			spelling;
    
private:	// functions
    void analyzeIdentifierOrKeyword();
    void analyzeIntegerConstant();
    void analyzeCharacterConstant();
    
public:		// functions
	LexicalAnalyzer(const char *sourcename);
	~LexicalAnalyzer( );
    
	void	nextsymbol( );
};

#endif
