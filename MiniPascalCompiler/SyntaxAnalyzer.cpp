//
//  SyntaxAnalyzer.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/13/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include "SyntaxAnalyzer.h"
#include <algorithm>
#include <iostream>

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

void SyntaxAnalyzer::skipto(std::set<symboltype> &relevantsymbols)
{
    while (relevantsymbols.find(symbol) == relevantsymbols.end()) {
        nextsymbol();
        //std::cout << "skip: " << symbol << "\n";
    }
}

void SyntaxAnalyzer::skipto(std::set<symboltype> &starters,
                            std::set<symboltype> &followers)
{
    std::set<symboltype> skipsymbols;
    std::set_union(starters.begin(), starters.end(),
                   followers.begin(), followers.end(),
                   std::inserter(skipsymbols, skipsymbols.begin())
                   );
    skipto(skipsymbols);
}

bool SyntaxAnalyzer::startcheck(
    std::set<symboltype> &starters,
    std::set<symboltype> &followers
) {
    if (starters.find(symbol) == starters.end()) {
        syntaxerror(othersy);
        skipto(starters, followers);
        return false; //symbol not in starters
    } else {
        return true; //symbol in starters
    }
}

void SyntaxAnalyzer::endcheck(std::set<symboltype> &followers)
{
    if (followers.find(symbol) == followers.end()) {
        syntaxerror(othersy);
        skipto(followers);
    }
}

//////////////////////////
//// Public Functions ////
//////////////////////////

//<programme>		::=	PROGRAM <identifier> ; <block> .
void SyntaxAnalyzer::programme()
{
    accept(programsy);
    accept(ident);
    accept(semicolon);
    block({period});
    accept(period);
} // programme( )

///////////////////////////
//// Private Functions ////
///////////////////////////
void SyntaxAnalyzer::syntaxerror(symboltype expectedsymbol)
{
	error((int)expectedsymbol + 10, symbolposition);
    std::cout << "espected: " << expectedsymbol << ", got: " << symbol << "\n";
} // syntaxerror( )


void SyntaxAnalyzer::accept(symboltype symbolexpected)
{
	symbol == symbolexpected ? nextsymbol() : syntaxerror(symbolexpected);
} // accept( )


// <block>			::=	<varpart><procpart><statpart>
void SyntaxAnalyzer::block(std::set<symboltype> followers)
{
    followers.insert(procsy);
	varPart(followers);
    
    std::set<symboltype> followers2 (followers);
    followers.insert(beginsy);
	procPart(followers2);
    
	statementPart(followers);
} // block( )


// <statpart>		::=	<compoundstatement>
void SyntaxAnalyzer::statementPart(std::set<symboltype> followers)
{
    compoundStatement(followers);
} // statpart( )


// <compoundstatement>	::=	BEGIN <statement> { ; <statement> } END
void SyntaxAnalyzer::compoundStatement(std::set<symboltype> followers)
{
    
    accept(beginsy);
    statement(followers);
    
    while (symbol == semicolon) {
        accept(semicolon);
        statement(followers);
    }
    
    accept(endsy);
} // compoundstatement( );


// <statement>		::=	<simple statement>
//                      | <complex statement>
void SyntaxAnalyzer::statement(std::set<symboltype> followers)
{
    //ako neterminala ne se vika ot drugo mqsto
    //ne se pravi startcheck & endcheck v tqh a samo v parenta
    if (statementStarters.find(symbol) != statementStarters.end()) {
        switch(symbol) {
            case ident: assignment(followers); break;
            case beginsy: compoundStatement(followers); break;
            case ifsy: ifStatement(followers); break;
            case whilesy: whileStatement(followers); break;
            case readsy: readStatement(followers); break;
            case writesy: writeStatement(followers); break;
            default:
                break;
        } // swtich
    } else {
        syntaxerror(othersy);
    }
} // statement()


// <ifstatement>		::=	IF <expression> THEN <statement>
//                          | IF <expression> THEN <statement> ELSE <statement>
void SyntaxAnalyzer::ifStatement(std::set<symboltype> followers)
{
    accept(ifsy);
    expression();
    accept(thensy);
    statement(followers);
    if (symbol == elsesy) {
        accept(elsesy);
        statement(followers);
    }
} // ifstatement( )


// <whilestatement>		::=	 WHILE <expression> DO <statement>
void SyntaxAnalyzer::whileStatement(std::set<symboltype> followers)
{
    accept(whilesy);
    expression();
    accept(dosy);
    statement(followers);
} // whilestatement( )


// <output value>		::=	<expression>
void SyntaxAnalyzer::outputValue()
{
    expression();
} // outputvalue( )


// <writestatement>		::=	WRITE ( <output value> { , <output value> } )
void SyntaxAnalyzer::writeStatement(std::set<symboltype> followers)
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
void SyntaxAnalyzer::readStatement(std::set<symboltype> followers)
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
void SyntaxAnalyzer::assignment(std::set<symboltype> followers)
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
void SyntaxAnalyzer::procDeclaration(std::set<symboltype> followers)
{
    accept(procsy);
    accept(ident);
    accept(semicolon);
    
    block(followers);
} // procdeclaration( )


// <procpart>		::=    	{ <procdeclaration> ; }
void SyntaxAnalyzer::procPart(std::set<symboltype> followers)
{
    while (symbol == procsy) {
        procDeclaration(followers);
    }
} // procpart( )


//  <varpart> 		::=		<empty>
//                          | VAR <vardeclaration> ; { <vardeclaration> ; }
void SyntaxAnalyzer::varPart(std::set<symboltype> followers)
{
    std::set<symboltype> starters(followers); //copy followers
    starters.insert(varsy);
    
    //symbol not found in starters, do nothing
    if(!startcheck(starters, followers)) {
        return;
    }
    
    //it's optional
	if (symbol == varsy) {
        accept(varsy);
        
        //at least one declaration is required
        do {
            varDeclaration();
            accept(semicolon);
        } while (symbol == ident);
    }
    
    endcheck(followers);
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