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
	// ToDo
} // statpart( )

void SyntaxAnalyzer::compoundStatement()
{
	// ToDo
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
	// ToDo
} // whilestatement( )

void SyntaxAnalyzer::outputValue()
{
	// ToDo
} // outputvalue( )

void SyntaxAnalyzer::writeStatement()
{
	// ToDo
} // writestatement( )

void SyntaxAnalyzer::inputVariable()
{
	// ToDo
} // inputvariable( )

void SyntaxAnalyzer::readStatement()
{
	// ToDo
} // readstatement( )

void SyntaxAnalyzer::variable()
{
	// ToDo
} // variable( )

void SyntaxAnalyzer::assignment()
{
	// ToDo
} // assignment( )

void SyntaxAnalyzer::expression()
{
	// ToDo
} // expression( );

void SyntaxAnalyzer::simpleExpression()
{
	// ToDo
} // simpleexpression( )

void SyntaxAnalyzer::term()
{
	// ToDo
} // term( )

void SyntaxAnalyzer::factor()
{
	// ToDo
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
	// ToDo
} // varpart( )

void SyntaxAnalyzer::varDeclaration()
{
	// ToDo
} // vardeclaration( )

void SyntaxAnalyzer::simpleType()
{
	// ToDo
} // simpletype( )

void SyntaxAnalyzer::indexRange()
{
	// ToDo
} // indexrange( )

void SyntaxAnalyzer::typ()
{
	// ToDo
} // typ( )