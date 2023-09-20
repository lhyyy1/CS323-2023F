#include<stdio.h>
#include "lex.h"

char* type2string(int token_type){
    switch (token_type){
        case 0:
            return "TYPE";
        case 1:
            return "INT";
        case 2:
            return "ID";
        case 3:
            return "IF";
        case 4:
            return "ELSE";
        case 5:
            return "WHILE";
        case 6:
            return "RET";
        case 7:
            return "SEMI";
        case 8:
            return "ASSIGN";
        case 9:
            return "LT";
        case 10:
            return "LE";
        case 11:
            return "GT";
        case 12:
            return "GE";
        case 13:
            return "NE";
        case 14:
            return "EQ";
        case 15:
            return "PLUS";
        case 16:
            return "LP";
        case 17:
            return "RP";
        case 18:
            return "LC";
        case 19:
            return "RC";
        case 21:
            return "MINUS";
        default:
            return "ERROR";
    }
}

char buf[10],*tp_buf=buf;

char gtchar(){
    if ( tp_buf == buf )
        return getchar();
    else
        return *(tp_buf--);
}

void retract(char c){
    *(++tp_buf) = c;
}

int isld(char c){
    return ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'z' )
        || ( c >= 'A' && c <= 'Z' ) || c == '_';
}

int isl(char c){
    return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || c == '_';
}

int isd(char c){
    return c >= '0' && c <= '9';
}

token_t getnext(){
    int state = 0;
    char c;
    while (1){
        switch (state){
            case 0:
                c = gtchar();
                if ( c == EOF ) return (token_t){TOKEN_END, 0};
                if ( c == ' ' || c == '\n' || c == '\r' ) state = 0;
                else if ( c == '<' ) state = 1;
                else if ( c == '=' ) state = 4;
                else if ( c == '>' ) state = 7;
                else if ( c == '!' ) state = 10;
                else if ( c == ';' ) state = 13;
                else if ( c == '+' ) state = 14;
                else if ( c == '(' ) state = 15;
                else if ( c == ')' ) state = 16;
                else if ( c == '{' ) state = 17;
                else if ( c == '}' ) state = 18;
                else if ( c == 'i' ) state = 21;
                else if ( c == 'e' ) state = 27;
                else if ( c == 'w' ) state = 32;
                else if ( c == 'r' ) state = 38;
                else if ( isl(c) || c == '$' ) state = 19;
                else if ( isd(c) ) state = 45;
                else if ( c == '-' ) state = 48;
                else return (token_t){TOKEN_ERR, 0};
                break;
            case 1:
                c = gtchar();
                if ( c == '=' ) state = 2;
                else state = 3;
                break;
            case 2:
                return (token_t){TOKEN_LE, 0};
            case 3:
                retract(c);
                return (token_t){TOKEN_LT, 0};
            case 4:
                c = gtchar();
                if ( c == '=' ) state = 5;
                else state = 6;
                break;
            case 5:
                return (token_t){TOKEN_EQ, 0};
            case 6:
                retract(c);
                return (token_t){TOKEN_ASSIGN, 0};
            case 7:
                c = gtchar();
                if ( c == '=' ) state = 8;
                else state = 9;
                break;
            case 8:
                return (token_t){TOKEN_GE, 0};
            case 9:
                retract(c);
                return (token_t){TOKEN_GT, 0};
            case 10:
                c = gtchar();
                if ( c == '=' ) state = 11;
                else state = 12;
                break;
            case 11:
                return (token_t){TOKEN_NE, 0};
            case 12:
                retract(c);
                return (token_t){TOKEN_NOT, 0};
            case 13:
                return (token_t){TOKEN_SEMI, 0};
            case 14:
                return (token_t){TOKEN_PLUS, 0};
            case 15:
                return (token_t){TOKEN_LP, 0};
            case 16:
                return (token_t){TOKEN_RP, 0};
            case 17:
                return (token_t){TOKEN_LC, 0};
            case 18:
                return (token_t){TOKEN_RC, 0};
            case 19:
                c = gtchar();
                if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 20:
                retract(c);
                return (token_t){TOKEN_ID, 0};
            case 21:
                c = gtchar();
                if ( c == 'f' ) state = 22;
                else if ( c == 'n' ) state = 24;
                else if ( isld(c) ) state = 19; 
                else state = 20;
                break;
            case 22:
                c = gtchar();
                if ( isld(c) ) state = 19;
                else state = 23;
                break;
            case 23:
                retract(c);
                return (token_t){TOKEN_IF, 0};
            case 24:
                c = gtchar();
                if ( c == 't' ) state = 25;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 25:
                c = gtchar();
                if ( isld(c) ) state = 19;
                else state = 26;
                break;
            case 26:
                retract(c);
                return (token_t){TOKEN_TYPE, 0};
            case 27:
                c = gtchar();
                if ( c == 'l' ) state = 28;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 28:
                c = gtchar();
                if ( c == 's' ) state = 29;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 29:
                c = gtchar();
                if ( c == 'e' ) state = 30;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 30:
                c = gtchar();
                if ( isld(c) ) state = 19;
                else state = 31;
                break;
            case 31:
                retract(c);
                return (token_t){TOKEN_ELSE, 0};
            case 32:
                c = gtchar();
                if ( c == 'h' ) state = 33;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 33:
                c = gtchar();
                if ( c == 'i' ) state = 34;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 34:
                c = gtchar();
                if ( c == 'l' ) state = 35;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 35:
                c = gtchar();
                if ( c == 'e' ) state = 36;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 36:
                c = gtchar();
                if ( isld(c) ) state = 19;
                else state = 37;
                break;
            case 37:
                retract(c);
                return (token_t){TOKEN_WHILE, 0};
            case 38:
                c = gtchar();
                if ( c == 'e' ) state = 39;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 39:
                c = gtchar();
                if ( c == 't' ) state = 40;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 40:
                c = gtchar();
                if ( c == 'u' ) state = 41;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 41:
                c = gtchar();
                if ( c == 'r' ) state = 42;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 42:
                c = gtchar();
                if ( c == 'n' ) state = 43;
                else if ( isld(c) ) state = 19;
                else state = 20;
                break;
            case 43:
                c = gtchar();
                if ( isld(c) ) state = 19;
                else state = 44;
                break;
            case 44:
                retract(c);
                return (token_t){TOKEN_RET, 0};
            case 45:
                c = gtchar();
                if ( isd(c) ) state = 45;
                else if ( isl(c) ) state = 46;
                else state = 47;
                break;
            case 46:
                return (token_t){TOKEN_ERR, 0};
            case 47:
                retract(c);
                return (token_t){TOKEN_INT, 0};
            case 48:
                c = gtchar();
                if ( isd(c) ) state = 45;
                else state = 49;
                break;
            case 49:
                retract(c);
                return (token_t){TOKEN_MINUS, 0};
            default:
                return (token_t){TOKEN_ERR, 0};
        }
    }
}

int main(void)
{
    while (1){
        token_t token = getnext();
        if ( token.type == TOKEN_END )
            break;
        printf("%s",type2string(token.type));
        putchar(' ');
        if ( token.type == TOKEN_ERR )
            break;
    }
    puts("");
}
