//
//  Source.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/12/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include "Source.h"
#include <iostream>
#include <iomanip>

Source::Source(const char *sourcename) {
	fin.open( sourcename );
    
	if (! fin.is_open( ) ) {
		std::cerr << "*****   ERROR: Could not open file: "
        << sourcename << std::endl;
		exit( EXIT_FAILURE );
	}
    
	std::cout << "LISTING PRODUCED BY MINI-PASCAL COMPILER  MPC-1";
	std::cout << std::endl << std::endl;
    
    loadErrorMap();
    readnextline();
	
	positionnow.linenumber = 1;
	positionnow.charnumber = firstinline;
    
	ch = line[positionnow.charnumber];
    
    errorcount		= 0;
    errinx			= 0;
    erroroverflow	= false;
} // source( )

Source::~Source( ) {
	listthisline( );
    
	std::cout << std::endl << std::endl;
	std::cout << "COMPILATION COMPLETED :";
	errorcount == 0	? std::cout << " NO"
    : std::cout << std::setw(5) << errorcount;
	std::cout << " ERROR(S) REPORTED." << std::endl;
    
	fin.close( );
} // ~source( )

//////////////////////////
//// Public Functions ////
//////////////////////////
void Source::nextch( ) {
	if ( positionnow.charnumber == lastinline ) {
		listthisline( );
		readnextline( );
        
		positionnow.charnumber = firstinline;
		positionnow.linenumber++;
	} else {
		positionnow.charnumber++;
	}
    
	ch = line[positionnow.charnumber];
} // nextch( )

void Source::error( int code, textposition position ) {
	if ( errinx == MAX_ERRORS ) {
		erroroverflow = true;
	} else {
		errlist[errinx].errorcode = code;
		errlist[errinx].errorposition = position;
		errinx++;
	}
} // error( )

///////////////////////////
//// Private Functions ////
///////////////////////////
void Source::readnextline( ) {
	char	inChar;
	int		i = 0;
    
	firstinline = 0;
	
	while (fin.get(inChar) && inChar != '\n' && !fin.eof()) {
		line[i] = inChar;
		i++;
		if ( i > MAX_CHARACTERS ) {
			std::cerr << "*****   ERROR: Line too long! Aborting..." << std::endl;
			exit( EXIT_FAILURE );
		}
	}
    
	fin.eof() ? line[i] = 0 : line[i] = ' ';
    
	lastinline = i;
} // readnextline( )

void Source::listerrors( ) {
	errorcount += errinx;
    
	for (int k=0; k<errinx; k++) {
		std::cout << "*****   ";
		if ( errlist[k].errorposition.linenumber != positionnow.linenumber ) {
			int tempVar = errlist[k].errorposition.charnumber - firstinline + 1;
			std::cout << "ERROR"
            << std::setw(10) << errlist[k].errorcode
            << " AT CHARACTER"
            << std::setw(3) << tempVar
            << " OF LINE"
            << std::setw(6) << errlist[k].errorposition.linenumber;
		} else {
			int tempVar = errlist[k].errorposition.charnumber - firstinline + 6;
			std::cout << std::setw(tempVar) << "^ERROR"
            << std::setw(4) << errlist[k].errorcode
            << " - " << errorMap[errlist[k].errorcode];
		}
		std::cout << std::endl;
	}
    
	if ( erroroverflow ) {
		std::cout << "*****   FURTHER ERRORS SUPPRESSED";
		std::cout << std::endl;
	}
    std::cout << std::endl;
    
    errinx			= 0;
    erroroverflow	= false;
} // listerrors( )

void Source::listthisline( ) {
	std::cout << std::setw(5) << positionnow.linenumber << "   ";
	for (int i=firstinline; i<=lastinline; i++) {
		std::cout << line[i];
	}
    std::cout << std::endl;
    
	if ( errinx > 0 ) { 
		listerrors( ); 
		//cin.get();
	}
} // listthisline( )

void Source::loadErrorMap()
{
    std::ifstream file("errors.dat");
	if (!file.is_open( ) ) {
		std::cerr << "*****   ERROR: Could not open file: "
        << "errors.dat" << std::endl;
		exit( EXIT_FAILURE );
	}
    
    char tmp_error[100];
    char tmp_error_code[3];
    
    while(!file.getline(tmp_error_code, 10, '|').eof()) {
        file.getline(tmp_error, 100);
        errorMap.insert(std::make_pair(atoi(tmp_error_code), tmp_error));
    }
}