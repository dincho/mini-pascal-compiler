//
//  SyntaxAnalyzer.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/13/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include "SyntaxAnalyzer.h"

//////////////////////////////////
//// Constructor & Destructor ////
//////////////////////////////////
SyntaxAnalyzer::SyntaxAnalyzer(const char *sourcename) : LexicalAnalyzer(sourcename)
{
	statstarters	=	setofsymbols{ident, beginsy, readsy, writesy, ifsy, whilesy};
	factorstarters	=	setofsymbols{ident, intconst, charconst, notop, leftparent};
	mulops			=	setofsymbols{times, divop, andop};
    signs			=	setofsymbols{plus, minus};
    addops			=	setofsymbols{plus, minus, orop};
    relops			=	setofsymbols{eqop, neop, ltop, leop, geop, gtop};
} // syntax( )

SyntaxAnalyzer::~SyntaxAnalyzer( ) {
	// empty
} // ~syntax( )

//////////////////////////
//// Public Functions ////
//////////////////////////
void SyntaxAnalyzer::programme( ) {
	accept( programsy );
	accept( ident );
	accept( semicolon );
	block( );
} // programme( )

///////////////////////////
//// Private Functions ////
///////////////////////////
void SyntaxAnalyzer::syntaxerror( symboltype expectedsymbol ) {
	error( (int)expectedsymbol + 10, symbolposition );
} // syntaxerror( )

void SyntaxAnalyzer::accept( symboltype symbolexpected ) {
	symbol == symbolexpected	? nextsymbol( )
    : syntaxerror( symbolexpected );
} // accept( )


void SyntaxAnalyzer::block( ) {
	varpart( );
	procpart( );
	statpart( );
} // block( )

void SyntaxAnalyzer::statpart( ) {
	// ToDo
} // statpart( )

void SyntaxAnalyzer::compoundstatement( ) {
	// ToDo
} // compoundstatement( );

void SyntaxAnalyzer::statement( ) {
    //@question - ask the instructor what is setoff >> operator and replace it with stl::set operator
    
//	if ( symbol >> statstarters ) {
//		switch( symbol ) {
//			case ident	:	assignment( ); break;
//			case beginsy:	compoundstatement( ); break;
//			case ifsy	:	ifstatement( ); break;
//			case whilesy:	whilestatement( ); break;
//			case readsy	:	readstatement( ); break;
//			case writesy:	writestatement( ); break;
//		} // swtich
//	} else {
//		syntaxerror( othersy );
//	}
} // statement( )

void SyntaxAnalyzer::ifstatement( ) {
	accept( ifsy );
	expression( );
	accept( thensy );
	statement( );
	if ( symbol == elsesy ) {
		accept( elsesy );
		statement( );
	}
} // ifstatement( )

void SyntaxAnalyzer::whilestatement( ) {
	// ToDo
} // whilestatement( )

void SyntaxAnalyzer::outputvalue( ) {
	// ToDo
} // outputvalue( )

void SyntaxAnalyzer::writestatement( ) {
	// ToDo
} // writestatement( )

void SyntaxAnalyzer::inputvariable( ) {
	// ToDo
} // inputvariable( )

void SyntaxAnalyzer::readstatement( ) {
	// ToDo
} // readstatement( )

void SyntaxAnalyzer::variable( ) {
	// ToDo
} // variable( )

void SyntaxAnalyzer::assignment( ) {
	// ToDo
} // assignment( )

void SyntaxAnalyzer::expression( ) {
	// ToDo
} // expression( );

void SyntaxAnalyzer::simpleexpression( ) {
	// ToDo
} // simpleexpression( )

void SyntaxAnalyzer::term( ) {
	// ToDo
} // term( )

void SyntaxAnalyzer::factor( ) {
	// ToDo
} // factor( )


void SyntaxAnalyzer::procdeclaration( ) {
	// ToDo
} // procdeclaration( )

void SyntaxAnalyzer::procpart( ) {
	// ToDo
} // procpart( )


void SyntaxAnalyzer::varpart( ) {
	// ToDo
} // varpart( )

void SyntaxAnalyzer::vardeclaration( ) {
	// ToDo
} // vardeclaration( )

void SyntaxAnalyzer::simpletype( ) {
	// ToDo
} // simpletype( )

void SyntaxAnalyzer::indexrange( ) {
	// ToDo
} // indexrange( )
void SyntaxAnalyzer::typ( ) {
	// ToDo
} // typ( )