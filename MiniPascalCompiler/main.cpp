//
//  main.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/12/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include <iostream>
#include "source_test.h"
#include "lexer_test.h"
#include "syntax_test.h"

int main(int argc, const char * argv[])
{
//    return source_test(argc, argv);
    return syntax_test(argc, argv);
}

