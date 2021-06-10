%option noyywrap
%{
/*****************声明和选项设置  begin*****************/
#include <stdio.h>
#include <stdlib.h>

#include "lexical_analyzer.h"

int lines = 0;
int pos_start = 1;
int pos_end = 0;

/*****************声明和选项设置  end*****************/

%}
DIGIT [0-9]
LETTER [a-zA-Z]
%%

 /******************TODO*********************/
 /****请在此补全所有flex的模式与动作  start******/
 //STUDENT TO DO
"+" {pos_start = pos_end; pos_end = pos_start + 1; return ADD;}
"-" {pos_start = pos_end ; pos_end = pos_start + 1; return SUB;}
"*" {pos_start = pos_end; pos_end = pos_start + 1; return MUL;}
"/" {pos_start = pos_end; pos_end = pos_start + 1; return DIV;}
"<"	{pos_start = pos_end ; pos_end = pos_start + 1; return LT;}
"<=" {pos_start = pos_end; pos_end = pos_start + 2; return LTE;}
">"  {pos_start = pos_end; pos_end = pos_start + 1; return GT;}
">=" {pos_start = pos_end; pos_end = pos_start + 2; return GTE;}
"==" {pos_start = pos_end; pos_end = pos_start + 2; return EQ;}
"!=" {pos_start = pos_end; pos_end = pos_start + 2; return NEQ;}
"=" {pos_start = pos_end; pos_end = pos_start + 1; return ASSIN;}

";" {pos_start = pos_end; pos_end = pos_start + 1; return SEMICOLON;}
"," {pos_start = pos_end; pos_end = pos_start + 1; return COMMA;}
"(" {pos_start = pos_end; pos_end = pos_start + 1; return LPARENTHESE;}
")" {pos_start = pos_end; pos_end = pos_start + 1; return RPARENTHESE;}
"[" {pos_start = pos_end; pos_end = pos_start + 1; return LBRACKET;}
"]" {pos_start = pos_end; pos_end = pos_start + 1; return RBRACKET;}
"{" {pos_start = pos_end; pos_end = pos_start + 1; return LBRACE;}
"}" {pos_start = pos_end; pos_end = pos_start + 1; return RBRACE;}

"else" {pos_start = pos_end; pos_end = pos_start + 4; return ELSE;}
"if" {pos_start = pos_end; pos_end = pos_start + 2; return IF;}
"int" {pos_start = pos_end; pos_end = pos_start + 3; return INT;}
"float" {pos_start = pos_end; pos_end = pos_start + 5; return FLOAT;}
"return" {pos_start = pos_end; pos_end = pos_start + 6; return RETURN;}
"void" {pos_start = pos_end; pos_end = pos_start + 4; return VOID;}
"while" {pos_start = pos_end ; pos_end = pos_start + 5; return WHILE;}

[ \t]+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); return BLANK;}
{LETTER}+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); return IDENTIFIER;}
{DIGIT}+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext);  return INTEGER;} 
(({DIGIT}+[.])|({DIGIT}*[.]{DIGIT}+)) {pos_start = pos_end; pos_end = pos_start + strlen(yytext); return FLOATPOINT;}
(\[\]) {pos_start = pos_end; pos_end = pos_start + 2;return ARRAY;}
 /*{LETTER} {return LETTER;}*/
[\n] {lines++; pos_end = 1; pos_start = 1; return EOL;}
  /*"/*" {char ch; char prev = '\0'; do { ch = input();if (ch == EOF) break; pos_end ++; pos_start ++; if (ch == '\n') {lines++; pos_start = 1; pos_end = 1;} if (prev == '*' && ch == '/') break; prev = ch; } while (1); return COMMENT;}*/
"/*"([*]+[^/]|[^*])*[*]+"/" {
    pos_start = pos_end; pos_end += yyleng;
    int pre_eol = -1;
    for (int i = 0; i < yyleng; ++i){
        if (yytext[i] == '\n'){
            lines++;
            pos_end -= (pos_start - 1) + (i - pre_eol);
            pos_start = 1;
            pre_eol = i;
        }
    }
    return COMMENT;
}
 /****请在此补全所有flex的模式与动作  end******/
%%
/****************C代码 start*************/

/// \brief analysize a *.cminus file
///
/// \param input_file, 需要分析的文件路径
/// \param token stream, Token_Node结构体数组，用于存储分析结果，具体定义参考lexical_analyer.h

void analyzer(char* input_file, Token_Node* token_stream){
    lines = 1;
    pos_start = 1;
    pos_end = 1;
    if(!(yyin = fopen(input_file,"r"))){
        printf("[ERR] No input file\n");
        exit(1);
    }
    printf("[START]: Read from: %s\n", input_file);

    int token;
    int index = 0;

    while(token = yylex()){
        switch(token){
            case COMMENT:
                break;
            case BLANK:
                break;
            case EOL:
                //STUDENT TO DO
                break;
            case ERROR:
                printf("[ERR]: unable to analysize %s at %d line, from %d to %d\n", yytext, lines, pos_start, pos_end);
                break;
            default :
                if (token == ERROR){
                    sprintf(token_stream[index].text, "[ERR]: unable to analysize %s at %d line, from %d to %d", yytext, lines, pos_start, pos_end);
                } else {
                    //printf("%-*s%-4d%-4d%-4d%-4d\n", w, yytext, token, lines, pos_start, pos_end);
                    printf("%s\t%d\t%d\t%d\t%d\n", yytext, token, lines, pos_start, pos_end);
                    strcpy(token_stream[index].text, yytext);
                }
                token_stream[index].token = token;
                token_stream[index].lines = lines;
                token_stream[index].pos_start = pos_start;
                token_stream[index].pos_end = pos_end;
                index++;
                if (index >= MAX_NUM_TOKEN_NODE){
                    printf("%s has too many tokens (> %d)", input_file, MAX_NUM_TOKEN_NODE);
                    exit(1);
                }
        }
    }
    printf("[END]: Analysis completed.\n");
    return;
}



/****************C代码 end*************/
