%{#include<stdio.h>
int line_number = 1;
%}

digit        [0-9]
letter       [a-zA-Z]
alphanum     {letter}|{digit}
keyword      "auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"
operator     "<="|"=="|"="|"++"|"-"|"*"|"+"|"/"|"%"|"--"|"<"|">"|">="|"!="|"&&"|"||"|"!"|"&"|"|"|"^"|"<<"|">>"|"~"|"sizeof"  
special_char "["|"]"|"{"|"}"

/* Rules */
%%
"\n" {
line_number++;
}


{keyword} {
    fprintf(yyout,"'%s' : is a KEYWORD, on Line number: %d\n", yytext, line_number);
}

(_|{letter})({letter}|{digit}|_)* {
    fprintf(yyout,"'%s' : is an IDENTIFIER, on Line number: %d\n", yytext, line_number);
}

{operator} {
    fprintf(yyout,"'%s' : is an OPERATOR, on Line number: %d\n", yytext, line_number);
}

{digit}* {
	fprintf(yyout,"'%s' : is a CONSTANT, on Line number: %d\n", yytext, line_number);
}

({special_char}|";"|"("|")"|".") {
    fprintf(yyout,"'%s' : is a SPECIAL CHARACTER, on Line number: %d\n", yytext, line_number);
}


("\"")[^\n\"]*("\"") {
	fprintf(yyout,"%s : is a STRING, on Line number: %d\n",yytext, line_number);
}


"#include"[ ]*"<"{letter}({alphanum})*".h>"   { 
    fprintf(yyout,"'%s' : is a PREPROCESSOR DIRECTIVE, on Line number: %d\n", yytext, line_number); 
}

"#define"[ ]+(_|{letter})({alphanum})*[ ]*(.)+   {
    fprintf(yyout,"'%s' : is a PREPROCESSOR DIRECTIVE, on Line number: %d\n", yytext, line_number);
}

"//".*  { 
    fprintf(yyout,"'%s' : is a SINGLELINE COMMENT, on Line number: %d\n", yytext, line_number);
}

("/*")(([^*]*[*]+[^*/])*([^*]*[*]+[/])) {
	fprintf(yyout,"'%s' : is a MULTILINE COMMENT, on Line number: %d\n", yytext, line_number);
}


[0-9!@`~$#%&*][a-zA-Z0-9_] {
    fprintf(yyout,"ERROR! %s : is an Invalid Identifier, on Line number: %d\n", yytext,line_number);
}

. ;

%%

/* User Routines */

int yywrap(){}

int main()
{   
	yyout = fopen("output.txt", "w");
	yylex();
	return 0;
}