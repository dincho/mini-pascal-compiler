//
//  source_test.cpp
//  MiniPascalCompiler
//
//  Created by Dincho Todorov on 10/13/13.
//  Copyright (c) 2013 Dincho Todorov. All rights reserved.
//

#include "source_test.h"
#include "Source.h"

int source_test(int argc, const char *argv[])
{
	const char *filename;
    const char default_filename[] = "srctest.prg";
    
    if (argc > 1) {
        filename = reinterpret_cast<const char *>(argv[1]);
    } else {
        filename = reinterpret_cast<const char *>(default_filename);
    }
    
	Source			src(filename);
	textposition	lastquery;
    
	do {
		if ( src.ch == '*' ) {
			src.error( 1, src.positionnow );
		} else {
			if ( src.ch == '?' ) {
				lastquery = src.positionnow;
			} else {
				if ( src.ch == '!' ) {
					src.error( 2, lastquery );
				}
			}
		}
        
		src.nextch();
	} while ( src.ch != 0 );
    
	return 0;
}