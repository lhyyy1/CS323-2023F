#ifndef _LEX_H
#define _LEX_H

typedef struct _token{
    int type;
    int* value;
}token_t;

#define TOKEN_TYPE 0
#define TOKEN_INT 1
#define TOKEN_ID 2
#define TOKEN_IF 3
#define TOKEN_ELSE 4
#define TOKEN_WHILE 5
#define TOKEN_RET 6
#define TOKEN_SEMI 7
#define TOKEN_ASSIGN 8
#define TOKEN_LT 9
#define TOKEN_LE 10
#define TOKEN_GT 11
#define TOKEN_GE 12
#define TOKEN_NE 13
#define TOKEN_EQ 14
#define TOKEN_PLUS 15
#define TOKEN_LP 16
#define TOKEN_RP 17
#define TOKEN_LC 18
#define TOKEN_RC 19
#define TOKEN_NOT 20
#define TOKEN_MINUS 21
#define TOKEN_END 254
#define TOKEN_ERR 255

char* type2string(int token_type);

char gtchar();

void retract(char c);

int isld(char c);

int isl(char c);

int isd(char c);

token_t getnext();

#endif
