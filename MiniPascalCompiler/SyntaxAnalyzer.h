//
//  SyntaxAnalyzer.h
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/13/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

///////////////////////////////////////////////////////////////////
///////////////////////// Syntax Analysis /////////////////////////
///////////////////////////////////////////////////////////////////
//																 //
// (A) Syntax analysis											 //
//																 //
//   Sintax analysis of Mini-Pascal programs is implemented		 //
//   as a set of recursive descent functions. These functions	 //
//   are based on the syntax rules given in the language defini- //
//   tion and are nested as tightly as the mutual interaction	 //
//   permits. The order, names, and nesting of the functions	 //
//   is as follows:												 //
//																 //
//	PROGRAMME													 //
//	    BLOCK													 //
//			VARPART												 //
//				VARDECLARATION									 //
//				TYP												 //
//					SIMPLETYPE									 //
//					INDEXRANGE									 //
//			PROCPART											 //
//			    PROCDECLARATION									 //
//			STATPART											 //
//			    COMPOUNDSTATEMENT								 //
//					STATEMENT									 //
//						VARIABLE								 //
//						EXPRESSION								 //
//							SIMPLEEXPRESSION					 //
//								TERM							 //
//									FACTOR						 //
//						ASSIGNMENT								 //
//						READSTATEMENT							 //
//							INPUTVARIABLE						 //
//						WRITESTATEMENT							 //
//							OUTPUTVALUE							 //
//						IFSTATEMENT								 //
//						WHILESTATEMENT							 //
//																 //
//																 //
//   The syntax analyzers are writen on the assumption that the	 //
//   next syntactic goal can always be selected by inspection of //
//   (at most) the next incoming symbol ( i.e. that the under-	 //
//   lying gramar is LL(1) ). This is not so at the following	 //
//   points in the syntax rules actually used:					 //
//																 //
//	1. a statement begining with an identifier may be			 //
//	   either an assignment or a procedure call ;				 //
//	2. a factor beginning with an identifier may be				 //
//	   either a variable or a constant.							 //
//																 //
//   In case 1 to resolve the choise on a purely syntactic		 //
//   basis would require a distortion of the syntax rules.		 //
//   Choice 2 cannot be syntactically resolved in some cases	 //
//   however if parallel semantic analysis is assumed (as in	 //
//   the case of this compiler) these choises can be resolwed	 //
//   without sintax distortion, by inspection of the current	 //
//   semantic attributes of the identifier involved. For this	 //
//   reason syntactic resolution of these choises is not used.	 //
//																 //
//																 //
//   The analyzer generates syntax error codes with the			 //
//   following meanings:										 //
//																 //
//	10 .... SYMBOL EXPECTED WAS IDENTIFIER						 //
//	11 .... SYMBOL EXPECTED WAS INTEGER CONSTANT				 //
//	12 .... SYMBOL EXPECTED WAS CHARACTER CONSTANT				 //
//	13 .... ...													 //
//																 //
//   I.e. one value for each of the values of symboltype.		 //
//   The final value (int)othersy+10 is used to mean			 //
//																 //
//	NN .... UNEXPECTED SYMBOL									 //
//																 //
//																 //
///////////////////////////////////////////////////////////////////
///////////////////////// Syntax Analysis /////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef __MiniPascalCompiler__SyntaxAnalyzer__
#define __MiniPascalCompiler__SyntaxAnalyzer__

#include <set>
#include "LexicalAnalyzer.h"

///////////////////////////
//// Variables & Types ////
///////////////////////////

// types
typedef std::set<symboltype> setofsymbols;

///////////////////////////
//// Class Declaration ////
///////////////////////////
class SyntaxAnalyzer : private LexicalAnalyzer {
private:	// variables
	setofsymbols	statstarters;
	setofsymbols	factorstarters;
	setofsymbols	mulops;
	setofsymbols	signs;
	setofsymbols	addops;
	setofsymbols	relops;
    
public:		// variables
    
private:	// functions
	void	syntaxerror( symboltype expectedsymbol );
	void	accept( symboltype symbolexpected );
    
	void	block( );
	void	varpart( );
    void	vardeclaration( );
    void	typ( );
    void	simpletype( );
    void	indexrange( );
	void	procpart( );
    void	procdeclaration( );
	void	statpart( );
    void	compoundstatement( );
    void	statement( );
    void	variable( );
    void	expression( );
    void	simpleexpression( );
    void	term( );
    void	factor( );
    void	assignment( );
    void	readstatement( );
    void	inputvariable( );
    void	writestatement( );
    void	outputvalue( );
    void	ifstatement( );
    void	whilestatement( );
public:		// functions
	SyntaxAnalyzer(const char *sourcename);
	~SyntaxAnalyzer( );
    
	void	programme( );
};

#endif /* defined(__MiniPascalCompiler__SyntaxAnalyzer__) */
