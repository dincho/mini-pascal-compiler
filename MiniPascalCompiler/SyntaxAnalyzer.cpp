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
	statementStarters	= {ident, beginsy, readsy, writesy, ifsy, whilesy};
	factorStarters	= {ident, intconst, charconst, notop, leftparent};
	mulOps			= {times, divop, andop};
    signs			= {plus, minus};
    addOps			= {plus, minus, orop};
    relOps			= {eqop, neop, ltop, leop, geop, gtop};
} // syntax( )

SyntaxAnalyzer::~SyntaxAnalyzer()
{
	// empty
} // ~syntax( )

//////////////////////////
//// Public Functions ////
//////////////////////////
void SyntaxAnalyzer::programme()
{
    accept(programsy);
    accept(ident);
    accept(semicolon);
    block();
} // programme( )

///////////////////////////
//// Private Functions ////
///////////////////////////
void SyntaxAnalyzer::syntaxerror(symboltype expectedsymbol)
{
	error((int)expectedsymbol + 10, symbolposition);
} // syntaxerror( )


void SyntaxAnalyzer::accept(symboltype symbolexpected)
{
	symbol == symbolexpected ? nextsymbol() : syntaxerror(symbolexpected);
} // accept( )


// <block>			::=	<varpart><procpart><statpart>
void SyntaxAnalyzer::block()
{
	varPart();
	procPart();
	statementPart();
} // block( )


// <statpart>		::=	<compoundstatement>
void SyntaxAnalyzer::statementPart()
{
    compoundStatement();
} // statpart( )


// <compoundstatement>	::=	BEGIN <statement> { ; <statement> } END
void SyntaxAnalyzer::compoundStatement()
{
    accept(beginsy);
    statement();
    
    while (symbol == semicolon) {
        accept(semicolon);
        statement();
    }
    
    accept(endsy);
} // compoundstatement( );


// <statement>		::=	<simple statement>
//                      | <complex statement>
void SyntaxAnalyzer::statement()
{
    if (statementStarters.find(symbol) != statementStarters.end()) {
        switch(symbol) {
            case ident: assignment(); break;
            case beginsy: compoundStatement(); break;
            case ifsy: ifStatement(); break;
            case whilesy: whileStatement(); break;
            case readsy: readStatement(); break;
            case writesy: writeStatement(); break;
            default:
                break;
        } // swtich
    } else {
        syntaxerror(othersy);
    }
} // statement()


// <ifstatement>		::=	IF <expression> THEN <statement>
//                          | IF <expression> THEN <statement> ELSE <statement>
void SyntaxAnalyzer::ifStatement()
{
    accept(ifsy);
    expression();
    accept(thensy);
    statement();
    if (symbol == elsesy) {
        accept(elsesy);
        statement();
    }
} // ifstatement( )


// <whilestatement>		::=	 WHILE <expression> DO <statement>
void SyntaxAnalyzer::whileStatement()
{
    accept(whilesy);
    expression();
    accept(dosy);
    statement();
} // whilestatement( )


// <output value>		::=	<expression>
void SyntaxAnalyzer::outputValue()
{
    expression();
} // outputvalue( )


// <writestatement>		::=	WRITE ( <output value> { , <output value> } )
void SyntaxAnalyzer::writeStatement()
{
    accept(writesy);
    accept(leftparent);
    outputValue();
    while (symbol == comma) {
        outputValue();
    }
} // writestatement( )


// <input variable>		::=	<variable>
void SyntaxAnalyzer::inputVariable()
{
	variable();
} // inputvariable( )


// <readstatement>		::=	READ ( <input variable> { , <input variable> } )
void SyntaxAnalyzer::readStatement()
{
	accept(readsy);
    inputVariable();
    
    while (symbol == comma) {
        inputVariable();
    }
} // readstatement( )


//       <variable>		::=	<simple variable>
//                          | <index variable>
void SyntaxAnalyzer::variable()
{
    accept(ident);
    
    if (symbol == leftbracket) {
        accept(leftbracket);
        expression();
        accept(rightbracket);
    }
} // variable( )


// <assignment>		::= <variable> := <expression>
void SyntaxAnalyzer::assignment()
{
    variable();
    accept(becomes);
    expression();
} // assignment( )


// <expression>         ::=	<simple expression>
//                          | <simple expression> <ifstatement><simple expression>
void SyntaxAnalyzer::expression()
{
	// ToDo
} // expression( );


// <simple expression>	::=	<sign><term> { <operator plus><term> }
void SyntaxAnalyzer::simpleExpression()
{

} // simpleexpression( )


// <term>			::=	<factor> { <operator multiply><factor> }
void SyntaxAnalyzer::term()
{
	// ToDo
} // term( )


// <factor>			::=	<variable>
//                      | <constant>
//                      | ( <expression> )
//                      | NOT <factor>
void SyntaxAnalyzer::factor()
{
    
} // factor( )


// <procdeclaration>	::=	PROCEDURE <identifier> ; <block>
void SyntaxAnalyzer::procDeclaration()
{
	// ToDo
} // procdeclaration( )


// <procpart>		::=    	{ <procdeclaration> ; }
void SyntaxAnalyzer::procPart()
{
	// ToDo
} // procpart( )


//  <varpart> 		::=		<empty>
//                          | VAR <vardeclaration> ; { <vardeclaration> ; }
void SyntaxAnalyzer::varPart()
{
    //it's optional
	if (symbol != varsy) {
        return;
    }
    
    accept(varsy);
    
    //at least one declaration is required
    do {
        varDeclaration();
        accept(semicolon);
    } while (symbol == ident);
} // varpart( )


// <vardeclaration>		::=	<identifier>{ ,<identifier> } : <typ>
void SyntaxAnalyzer::varDeclaration()
{
    accept(ident);
    
    while (symbol == comma) {
        accept(comma);
        accept(ident);
    }
    
    accept(colon);
    typ();
} // vardeclaration( )


// <simpletype>		::=	<identifier of type>
void SyntaxAnalyzer::simpleType()
{
    accept(ident);
} // simpletype( )


// <indexrange>		::=	<intconst> .. <intconst>
void SyntaxAnalyzer::indexRange()
{
    accept(intconst);
    accept(thru);
    accept(intconst);
} // indexrange( )


// <typ>			::=	<simpletype> | <arraytype>
void SyntaxAnalyzer::typ()
{
	// ToDo
} // typ( )