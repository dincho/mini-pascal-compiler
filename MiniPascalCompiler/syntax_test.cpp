//
//  syntax_test.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/15/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include "syntax_test.h"
#include "SyntaxAnalyzer.h"

int syntax_test(int argc, const char *argv[])
{
	const char *filename;
    const char default_filename[] = "sye_test.prg";
    
    if (argc > 1) {
        filename = reinterpret_cast<const char *>(argv[1]);
    } else {
        filename = reinterpret_cast<const char *>(default_filename);
    }
    
	SyntaxAnalyzer analyzer(filename);
	analyzer.programme();
    
    return EXIT_SUCCESS;
}