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


void SyntaxAnalyzer::block()
{
	varPart();
	procPart();
	statementPart();
} // block( )

void SyntaxAnalyzer::statementPart()
{
    compoundStatement();
} // statpart( )

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

void SyntaxAnalyzer::whileStatement()
{
    accept(whilesy);
    expression();
    accept(dosy);
    statement();
} // whilestatement( )

void SyntaxAnalyzer::outputValue()
{
    expression();
} // outputvalue( )

void SyntaxAnalyzer::writeStatement()
{
    accept(writesy);
    accept(leftparent);
    outputValue();
    while (symbol == comma) {
        outputValue();
    }
} // writestatement( )

void SyntaxAnalyzer::inputVariable()
{
	variable();
} // inputvariable( )

void SyntaxAnalyzer::readStatement()
{
	accept(readsy);
    inputVariable();
    
    while (symbol == comma) {
        inputVariable();
    }
} // readstatement( )

void SyntaxAnalyzer::variable()
{
    accept(ident);
    
    if (symbol == leftbracket) {
        accept(leftbracket);
        expression();
        accept(rightbracket);
    }
} // variable( )

void SyntaxAnalyzer::assignment()
{
    variable();
    accept(becomes);
    expression();
} // assignment( )

void SyntaxAnalyzer::expression()
{
	// ToDo
} // expression( );

void SyntaxAnalyzer::simpleExpression()
{

} // simpleexpression( )

void SyntaxAnalyzer::term()
{
	// ToDo
} // term( )

void SyntaxAnalyzer::factor()
{
    
} // factor( )


void SyntaxAnalyzer::procDeclaration()
{
	// ToDo
} // procdeclaration( )

void SyntaxAnalyzer::procPart()
{
	// ToDo
} // procpart( )


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

void SyntaxAnalyzer::simpleType()
{
    accept(ident);
} // simpletype( )

void SyntaxAnalyzer::indexRange()
{
    accept(intconst);
    accept(thru);
    accept(intconst);
} // indexrange( )

void SyntaxAnalyzer::typ()
{
	// ToDo
} // typ( )