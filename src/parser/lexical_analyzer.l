%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>

#include "syntax_tree.h"
#include "syntax_analyzer.h"

int files_count;
int lines = 1;
int pos_start = 1;
int pos_end = 1;

void pass_node(char *text){
     yylval.node = new_syntax_tree_node(text);
}
%}
DIGIT [0-9]
LETTER [a-zA-Z]
%%

 /******************TODO*********************/
 /****请在此补全所有flex的模式与动作  start******/
 //STUDENT TO DO
"+" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("+"); return ADD;}
"-" {pos_start = pos_end ; pos_end = pos_start + 1; pass_node("-"); return SUB;}
"*" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("*"); return MUL;}
"/" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("/"); return DIV;}
"<"	{pos_start = pos_end ; pos_end = pos_start + 1; pass_node("<"); return LT;}
"<=" {pos_start = pos_end; pos_end = pos_start + 2; pass_node("<="); return LTE;}
">"  {pos_start = pos_end; pos_end = pos_start + 1; pass_node(">"); return GT;}
">=" {pos_start = pos_end; pos_end = pos_start + 2; pass_node(">="); return GTE;}
"==" {pos_start = pos_end; pos_end = pos_start + 2; pass_node("=="); return EQ;}
"!=" {pos_start = pos_end; pos_end = pos_start + 2; pass_node("!="); return NEQ;}
"=" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("=");  return ASSIGN;}

";" {pos_start = pos_end; pos_end = pos_start + 1; pass_node(";"); return SEMICOLON;}
"," {pos_start = pos_end; pos_end = pos_start + 1; pass_node(","); return COMMA;}
"(" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("("); return LPARENTHESE;}
")" {pos_start = pos_end; pos_end = pos_start + 1; pass_node(")"); return RPARENTHESE;}
"[" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("["); return LBRACKET;}
"]" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("]"); return RBRACKET;}
"{" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("{"); return LBRACE;}
"}" {pos_start = pos_end; pos_end = pos_start + 1; pass_node("}"); return RBRACE;}

"else" {pos_start = pos_end; pos_end = pos_start + 4; pass_node("else"); return ELSE;}
"if" {pos_start = pos_end; pos_end = pos_start + 2; pass_node("if"); return IF;}
"int" {pos_start = pos_end; pos_end = pos_start + 3; pass_node("int"); return INT;}
"float" {pos_start = pos_end; pos_end = pos_start + 5; pass_node("float"); return FLOAT;}
"return" {pos_start = pos_end; pos_end = pos_start + 6; pass_node("return"); return RETURN;}
"void" {pos_start = pos_end; pos_end = pos_start + 4; pass_node("void"); return VOID;}
"while" {pos_start = pos_end ; pos_end = pos_start + 5; pass_node("while"); return WHILE;}

[ \t]+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); /*return BLANK;*/}
{LETTER}+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); yylval.string = strdup(yytext); return IDENTIFIER;}
{DIGIT}+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); yylval.int_number = atoi(yytext); return INTEGER;} 
(({DIGIT}+[.])|({DIGIT}*[.]{DIGIT}+)) {pos_start = pos_end; pos_end = pos_start + strlen(yytext); yylval.string = strdup(yytext); return FLOATPOINT;}
(\[\]) {pos_start = pos_end; pos_end = pos_start + 2; pass_node("[]"); return ARRAY;}
 /*{LETTER} {return LETTER;}*/
[\n] {lines++; pos_end = 1; pos_start = 1; /*return EOL;*/}
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
    /*return COMMENT;*/
}
 /****请在此补全所有flex的模式与动作  end******/
%%