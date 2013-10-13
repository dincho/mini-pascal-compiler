#include "LexicalAnalyzer.h"

//////////////////////////////////
//// Constructor & Destructor ////
//////////////////////////////////
LexicalAnalyzer::LexicalAnalyzer(const char *sourcename) : Source(sourcename) {
    symbolsMap = {
        {"PROGRAM", {programsy, "PROGRAM"}},
        {"PROCEDURE", {procsy, "PROCEDURE"}},
        
        {"VAR", {varsy, "VAR"}},
        {"ARRAY", {arraysy, "ARRAY"}},
        
        {"BEGIN", {beginsy, "BEGIN"}},
        {"END", {endsy, "END"}},
        
        {"READ", {readsy, "READ"}},
        {"WRITE", {writesy, "WRITE"}},
        
        {"DO", {dosy, "DO"}},
        {"WHILE", {whilesy, "WHILE"}},

        {"IF", {ifsy, "IF"}},
        {"THEN", {thensy, "THEN"}},
        {"ELSE", {elsesy, "ELSE"}},
        
        {"OR", {orop, "OR"}},
        {"AND", {andop, "AND"}},
        {"NOT", {notop, "NOT"}},
        
        {"OF", {ofsy, "OF"}},
        {"DIV", {divop, "DIV"}}
    };
    
	nextsymbol( );
} // scan( )

LexicalAnalyzer::~LexicalAnalyzer( ) {
	// empty
} // ~LexicalAnalyzer( )

//////////////////////////
//// Public Functions ////
//////////////////////////
void LexicalAnalyzer::nextsymbol()
{
	// read character by character until next significant character
	while (ch == ' ' || ch == '\t') {
        nextch();
    }
    
	// ToDo: handle tabs and comments
    memset(spelling, '\0', alfalength); //reset spelling
    symbolposition = positionnow;
    
	switch ( ch ) {
		// Analysis of an identifier or word symbol
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
		case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
		case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
		case 'Y': case 'Z':
		// ToDo: handle 'a' .. 'z'
            
            analyzeIdentifierOrKeyword();
        break;
            
		// Analysis of an integer constant
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
            analyzeIntegerConstant();
		break;
            
		//  Analysis of a character constant
		case '\'':
            analyzeCharacterConstant();
		break;
            
		// 2-character operator/delimiter
		case ':':
            {
                nextch( );
                if ( ch == '=' ) {
                    symbol = becomes; 
                    nextch( );
                } else { symbol = colon; }
            }
            break;
		case '.':
            {
                nextch( );
                if (ch == '.') {
                    symbol = thru;
                    nextch();
                } else {
                    symbol = period;
                }
            }
            break;
		case '<':
            {
                nextch( );
                if ( ch == '=' ) {
                    symbol = leop;
                    nextch( );
                } else if ( ch == '>' ) {
                    symbol = neop;
                    nextch( );
                } else {
                    symbol = ltop;
                }
            }
            break;
		case '>':
            {
                nextch();
                if (ch == '=') {
                    symbol = geop;
                    nextch();
                } else {
                    symbol = gtop;
                }
            }
            break;
		// 1-character operator delimiter
		case '+': { symbol = plus; nextch( ); } break;
		case '-': { symbol = minus; nextch( ); } break;
		case '*': { symbol = times; nextch( ); } break;
		case '=': { symbol = eqop; nextch( ); } break;
		case '(': { symbol = leftparent; nextch( ); } break;
		case ')': { symbol = rightparent; nextch( ); } break;
		case '[': { symbol = leftbracket; nextch( ); } break;
		case ']': { symbol = rightbracket; nextch( ); } break;
		case ',': { symbol = comma; nextch( ); } break;
		case ';': { symbol = semicolon; nextch( ); } break;
		// Other illegal characters
		default: { symbol = othersy; nextch( ); } break;
	} // switch
    

} // nextsymbol( )

void LexicalAnalyzer::analyzeIdentifierOrKeyword()
{
    int len = 0;
    
    do {
        //read "alfalength" significant chars
        if (len < alfalength) {
            spelling[len] = toupper(ch);
            len++;
        }
        
        //keep reading unsignificant chars
        nextch( );
    } while ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z'));
    // ToDo: handle 'a' .. 'z'
    
    //keyword
    if (symbolsMap.find(spelling) != symbolsMap.end()) {
        symbol = symbolsMap[spelling].symbolvalue;
    } else {
        //identificator
        symbol = ident;
    }
    
}

void LexicalAnalyzer::analyzeIntegerConstant()
{
    int digit;
    constant = 0;
    
    do {
        digit = static_cast<unsigned int>(ch - '0');
        if ( ( constant < ( maxinteger / 10 ) )
            || ( ( constant == ( maxinteger / 10 ) )
                && ( digit <= ( maxinteger % 10 ) ) ) ) {
                constant = ( 10 * constant ) + digit;
            } else {
                error( 1, positionnow );
                constant = 0;
            }
        nextch( );
    } while (ch >= '0' && ch <= '9');
    
    symbol = intconst;
}

void LexicalAnalyzer::analyzeCharacterConstant()
{
    nextch();
    
    if (ch == '\'') {
        nextch( );
        if (ch != '\'') {
            error( 2, positionnow );
        }
    }
    
    constant = static_cast<unsigned int>(ch);
    nextch();
    
    if(ch != '\'') {
        error( 2, positionnow );
    } else {
        nextch();
    }
    
    symbol = charconst;
}
