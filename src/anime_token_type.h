#ifndef ANIME_TOKEN_TYPE_H
#define ANIME_TOKEN_TYPE_H

// RL: All those tokens should be ordered by priorities: 
//     the lowest priority first, the highest priority last. 
enum { 
  ANIME_TOKEN_NULL, // It's the invalid token. 
  ANIME_TOKEN_EOF, 
  // RL: Syntatic sugar // Very low priority, i.e. outmost nodes  
  ANIME_TOKEN_OF, 
  ANIME_TOKEN_TO, 
  ANIME_TOKEN_DOWNTO, 
  ANIME_TOKEN_STEP, 
  ANIME_TOKEN_PTVIRG, 
  ANIME_TOKEN_OPENPAR, 
  ANIME_TOKEN_CLOSEPAR, 
  ANIME_TOKEN_OPENBRACKET, 
  ANIME_TOKEN_CLOSEBRACKET, 
  ANIME_TOKEN_OPENBRACE, 
  ANIME_TOKEN_CLOSEBRACE, 
  ANIME_TOKEN_DEUXPOINTS, 
  ANIME_TOKEN_VIRGULE, 
  ANIME_TOKEN_AS, 
  ANIME_TOKEN_HUH, 
  // RL: EXPR 
  ANIME_TOKEN_AFFECTATION, 
  ANIME_TOKEN_AFFECTATION_SIMPLE, 
  ANIME_TOKEN_AFFECTATION_IADD, 
  ANIME_TOKEN_AFFECTATION_RADD, 
  ANIME_TOKEN_AFFECTATION_ISUB, 
  ANIME_TOKEN_AFFECTATION_RSUB, 
  ANIME_TOKEN_AFFECTATION_IMULT, 
  ANIME_TOKEN_AFFECTATION_RMULT, 
  ANIME_TOKEN_AFFECTATION_IDIV, 
  ANIME_TOKEN_AFFECTATION_RDIV, 
  ANIME_TOKEN_AFFECTATION_IMOD, 
  ANIME_TOKEN_AFFECTATION_L_AND, 
  ANIME_TOKEN_AFFECTATION_L_OR, 
  ANIME_TOKEN_AFFECTATION_L_XOR, 
  ANIME_TOKEN_AFFECTATION_L_NOT, 
  ANIME_TOKEN_AFFECTATION_B_AND, 
  ANIME_TOKEN_AFFECTATION_B_OR, 
  ANIME_TOKEN_AFFECTATION_B_XOR, 
  ANIME_TOKEN_AFFECTATION_B_NOT, 
  ANIME_TOKEN_AFFECTATION_B_RSHIFT, 
  ANIME_TOKEN_AFFECTATION_B_LSHIFT, 
  ANIME_TOKEN_LOGICAL_AND, 
  ANIME_TOKEN_LOGICAL_OR, 
  ANIME_TOKEN_LOGICAL_XOR, // RL: BITWISE_XOR is definitely different. 
  ANIME_TOKEN_LOGICAL_NOT, 
  ANIME_TOKEN_EQUAL, // RL: The question is the interpretation of "a == b and d != e". 
  ANIME_TOKEN_DIFF, 
  ANIME_TOKEN_INF, // RL: The question is the interpretation of "a < b and d >= e". 
  ANIME_TOKEN_SUP, 
  ANIME_TOKEN_INFEQ, 
  ANIME_TOKEN_SUPEQ, 
  ANIME_TOKEN_IDIV, // RL: This thing has definitely a low priority: "1 + 2 div 4 + 3" 
  ANIME_TOKEN_IMOD, 
  ANIME_TOKEN_BITWISE_AND, 
  ANIME_TOKEN_BITWISE_OR, 
  ANIME_TOKEN_BITWISE_XOR, // RL: BOOL_XOR is definitely different. 
  ANIME_TOKEN_BITWISE_NOT, 
  ANIME_TOKEN_BITWISE_SHIFT_LEFT, 
  ANIME_TOKEN_BITWISE_SHIFT_RIGHT, 
  ANIME_TOKEN_IPLUS, 
  ANIME_TOKEN_RPLUS, 
  ANIME_TOKEN_IMOINS, 
  ANIME_TOKEN_RMOINS, 
  ANIME_TOKEN_IMULT, 
  ANIME_TOKEN_RMULT, 
  ANIME_TOKEN_RDIV, 
  ANIME_TOKEN_POINT, 
  ANIME_TOKEN_FLECHE, 
  ANIME_TOKEN_PTR, 
  ANIME_TOKEN_REF, 
  ANIME_TOKEN_IPLUS_UNAIRE, 
  ANIME_TOKEN_RPLUS_UNAIRE, 
  ANIME_TOKEN_IMOINS_UNAIRE, 
  ANIME_TOKEN_RMOINS_UNAIRE, 
  ANIME_TOKEN_INC, 
  ANIME_TOKEN_DEC, 
  // RL: Constant values, which have the upmost priorities 
  ANIME_TOKEN_TRUE, 
  ANIME_TOKEN_FALSE, 
  ANIME_TOKEN_ENTIER, 
  ANIME_TOKEN_REEL__VIRG, 
  ANIME_TOKEN_REEL__DOT, 
  ANIME_TOKEN_REEL__E, 
  ANIME_TOKEN_STRING_C, 
  ANIME_TOKEN_STRING_C__EOL, 
  ANIME_TOKEN_STRING_C__EOF, 
  ANIME_TOKEN_STRING_P, 
  ANIME_TOKEN_STRING_P__EOL, 
  ANIME_TOKEN_STRING_P__EOF, 
  ANIME_TOKEN_NIL, 
  ANIME_TOKEN_NULL_PTR, 
  // RL: LL(1) type 
  ANIME_TOKEN_TYPE, 
  ANIME_TOKEN_TYPE_ALIAS, 
  ANIME_TOKEN_BOOLEAN, 
  ANIME_TOKEN_INTEGER, 
  ANIME_TOKEN_FLOAT, 
  ANIME_TOKEN_STRING, 
  ANIME_TOKEN_SUBRANGE, 
  ANIME_TOKEN_ARRAY, 
  ANIME_TOKEN_RECORD, 
  ANIME_TOKEN_VARIANT, 
  // RL: LL(1) control flow 
  ANIME_TOKEN_IF, 
  ANIME_TOKEN_WHEN, 
  ANIME_TOKEN_UNLESS, 
  ANIME_TOKEN_WHILE, 
  ANIME_TOKEN_FOR, 
  ANIME_TOKEN_REPEAT, 
  ANIME_TOKEN_BEGIN, 
  ANIME_TOKEN_PROCEDURE, 
  ANIME_TOKEN_FONCTION, 
  ANIME_TOKEN_METHODE, 
  ANIME_TOKEN_LAMBDA, 
  ANIME_TOKEN_CONST, 
  ANIME_TOKEN_VAR, 
  //ANIME_TOKEN_REC, // RL: Needless. 'This' is not a token as well. 
  // RL: control flow others 
  ANIME_TOKEN_DONE, 
  ANIME_TOKEN_DO, 
  ANIME_TOKEN_THEN, 
  ANIME_TOKEN_ELSE, 
  ANIME_TOKEN_FI, 
  ANIME_TOKEN_UNTIL, 
  ANIME_TOKEN_END, 
  // RL: Other qualifying keywords 
  ANIME_TOKEN_BYREF, 
  ANIME_TOKEN_BYVAL, 
  // RL: Ident 
  ANIME_TOKEN_SYNTAX_MASTER, 
  ANIME_TOKEN_SYNTAX_KEYWORD, // RL: Could be handled like a regular ident by the parser? 
  ANIME_TOKEN_IDENT, 
  // RL: Ignored tokens 
  ANIME_TOKEN_EOL, 
  ANIME_TOKEN_BLANC, 
  ANIME_TOKEN_COMMENT__ONE_LINE_CPP, 
  ANIME_TOKEN_COMMENT__ONE_LINE_SCRIPT, 
  ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE, 
  ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF, 
  ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__LONELY_ENDING, 
  ANIME_TOKEN_TYPE_COUNT  
}; 

enum { ANIME_TOKEN__SYNTAX_MASTER__BASE  = ANIME_TOKEN_TYPE_COUNT }; 
enum { ANIME_TOKEN__SYNTAX_MASTER__SIZE  = 16 }; 
enum { ANIME_TOKEN__SYNTAX_MASTER__TOP   = ANIME_TOKEN__SYNTAX_MASTER__BASE + ANIME_TOKEN__SYNTAX_MASTER__SIZE }; 

enum { ANIME_TOKEN__SYNTAX_KEYWORD__BASE = ANIME_TOKEN__SYNTAX_MASTER__TOP }; 
enum { ANIME_TOKEN__SYNTAX_KEYWORD__SIZE = 16 }; 
enum { ANIME_TOKEN__SYNTAX_KEYWORD__TOP  = ANIME_TOKEN__SYNTAX_KEYWORD__BASE + ANIME_TOKEN__SYNTAX_KEYWORD__SIZE }; 

//#define TOKEN_MAX ANIME_TOKEN_COUNT 
enum { TOKEN_MAX = ANIME_TOKEN__SYNTAX_KEYWORD__TOP }; 



 
// RL: Token aliases. 
enum { 
  ANIME_TOKEN_TYPE_INVALID  = ANIME_TOKEN_NULL, 
  ANIME_TOKEN_ASSIGN        = ANIME_TOKEN_AFFECTATION, 
  ANIME_TOKEN_METHOD        = ANIME_TOKEN_METHODE, 
  ANIME_TOKEN_COMMA         = ANIME_TOKEN_VIRGULE, 
  ANIME_TOKEN_COLON         = ANIME_TOKEN_DEUXPOINTS, 
  ANIME_TOKEN_SEMICOLON     = ANIME_TOKEN_PTVIRG, 
  ANIME_TOKEN_POINTVIRGULE  = ANIME_TOKEN_PTVIRG, 
  ANIME_TOKEN_POINT_VIRGULE = ANIME_TOKEN_PTVIRG, 
  ANIME_TOKEN_FUNCTION      = ANIME_TOKEN_FONCTION, 
  ANIME_TOKEN_IMINUS        = ANIME_TOKEN_IMOINS, 
  ANIME_TOKEN_RMINUS        = ANIME_TOKEN_RMOINS, 
  ANIME_TOKEN_DOT           = ANIME_TOKEN_POINT, 
  ANIME_TOKEN_ARROW         = ANIME_TOKEN_FLECHE, 
  ANIME_TOKEN_CHAINE_C      = ANIME_TOKEN_STRING_C, 
  ANIME_TOKEN_CHAINE_P      = ANIME_TOKEN_STRING_P, 
  ANIME_TOKEN_REAL          = ANIME_TOKEN_FLOAT, 
}; 

typedef       uint8_t                 int_anime_token_type_t; 
extern  const int_anime_token_type_t  int_anime_token_type_max; // RL: Use for storage, where data should be packed. Anywhere else, 'int' is good. The property ensures that a token_type will fit into a 'int_anime_token_type_t'. 

extern const int_anime_token_type_t anime_token_type_count; 

extern const char * anime_token__type_get_cstr(const int_anime_token_type_t token_type); 
#define anime_token__type_cstr anime_token__type_get_cstr



#endif /* ANIME_TOKEN_TYPE_H */

