//
//  Source.h
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/12/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#ifndef MiniPascalCompiler_Source_h
#define MiniPascalCompiler_Source_h

#include <fstream>
#include <map>

// types
typedef struct textposition {
	int		linenumber;
	int		charnumber;
} textposition;

typedef struct errlistrec {
	int				errorcode;
	textposition	errorposition;
} errlistrec;

class Source {
private:	// variables
	// line processing variables
    static const int MAX_CHARACTERS = 81;
    static const int MAX_ERRORS = 6;
    
	char			line[MAX_CHARACTERS];
	int				firstinline;
	int				lastinline;
    
	// error handling variables
	int				errorcount;
	int				errinx;
	bool			erroroverflow;
	errlistrec		errlist[MAX_ERRORS];
    std::map<int, std::string> errorMap;
    
public:		// variables
	// file-stream variables
    std::ifstream fin;
    
	// variables keeping track of sourcer position
	char			ch;
	textposition	positionnow;
    
private:	// functions
	void	readnextline();
	void	listerrors();
	void	listthisline();
    void    loadErrorMap();
    
public:		// functions
	Source(const char *filename);
	~Source();
    
	void	nextch();
	void	error(int code, textposition position);
};

#endif
