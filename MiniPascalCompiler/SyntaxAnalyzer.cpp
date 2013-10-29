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
        accept(comma);
        outputValue();
    }
    
    accept(rightparent);
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
    accept(leftparent);
    inputVariable();
    
    while (symbol == comma) {
        accept(comma);
        inputVariable();
    }
    
    accept(rightparent);
} // readstatement( )


//<variable>                ::=	<simple variable>
//                              | <index variable>
//<simple variable>         ::=	<identifier of variable>
//<index variable>          ::=	<variable array> 	[ <expression> ]
//<variable array>          ::=	<simple variable>
//<identifier of variable>	::=	<identifier>
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
	simpleExpression();
    
    if(relOps.find(symbol) != relOps.end()) {
        relationOperator();
        simpleExpression();
    }
} // expression( );

//  <relation operator>		::=	= | <> | < | <= | >= | >
void SyntaxAnalyzer::relationOperator()
{
    if(relOps.find(symbol) != relOps.end()) {
        nextsymbol();
    } else {
        error(51, symbolposition);
    }
}

// <simple expression>	::=	<sign><term> { <operator plus><term> }
// <sign>               ::=	+ | - | <empty>
// <operator plus>		::=	+ | - | OR
void SyntaxAnalyzer::simpleExpression()
{
    if (symbol == plus || symbol == minus) {
        nextsymbol();
    }
    
    term();
    
    while (symbol == plus || symbol == minus || symbol == orop) {
        nextsymbol();
        term();
    }
    
} // simpleexpression( )


// <term>               ::=	<factor> { <operator multiply><factor> }
// <operator multiply>	::=	* | DIV | AND
void SyntaxAnalyzer::term()
{
    factor();
    
    while (symbol == times || symbol == divop || symbol == andop) {
        nextsymbol();
        factor();
    }
    
} // term( )


// <factor>                  ::=	<variable>
//                                      | <constant>
//                                      | ( <expression> )
//                                      | NOT <factor>
// <variable>                ::=	<simple variable>
//                                      | <index variable>
// <simple variable>         ::=	<identifier of variable>
// <index variable>          ::=	<variable array> 	[ <expression> ]
// <variable array>          ::=	<simple variable>
// <identifier of variable>	 ::=	<identifier>
// <constant>                ::=	<intconst>
//                                      | <charconst>
//                                      | <identifier of constant>
// <identifier of constant>	 ::=	<identifier>
void SyntaxAnalyzer::factor()
{
    switch (symbol) {
        case ident:
            variable();
            break;
            
        case intconst:
        case charconst:
//        @todo - conflict
//        case ident:
            nextsymbol();
            break;
        case leftparent:
            accept(leftparent);
            expression();
            accept(rightparent);
            break;
        case notop:
            nextsymbol();
            factor();
        default:
            //@todo - what error ?
            break;
    }
} // factor( )


// <procdeclaration>	::=	PROCEDURE <identifier> ; <block>
void SyntaxAnalyzer::procDeclaration()
{
    accept(procsy);
    accept(ident);
    accept(semicolon);
    block();
} // procdeclaration( )


// <procpart>		::=    	{ <procdeclaration> ; }
void SyntaxAnalyzer::procPart()
{
    while (symbol == procsy) {
        procDeclaration();
    }
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


// <simpletype>         ::=	<identifier of type>
// <identifier of type>	::=	<identifier>
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

// <arraytype>          ::=	ARRAY [ <indexrange> ] OF <simpletype>
void SyntaxAnalyzer::arrayType()
{
    accept(arraysy);
    accept(leftbracket);
    indexRange();
    accept(rightbracket);
    accept(ofsy);
    simpleType();
}

// <typ>                ::=	<simpletype> | <arraytype>
// <simpletype>         ::=	<identifier of type>
// <identifier of type>	::=	<identifier>
// <arraytype>          ::=	ARRAY [ <indexrange> ] OF <simpletype>
void SyntaxAnalyzer::typ()
{
    if (symbol == ident) {
        simpleType();
    } else if (symbol == arraysy) {
        arrayType();
    }
} // typ( )