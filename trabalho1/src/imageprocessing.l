
%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);

#include "y.tab.h"
%}



%%

[a-z]  {
        yylval.ival = yytext[0] - 'a';
        return VAR;
       }


\" { return ASPA; }

[0-9]+[0-9\.]*	{
	yylval.fltval = atof(yytext);
        printf ("Achei numero: %f\n", yylval.fltval);
        return FLOAT;
       }

[a-zA-Z0-9\.]+  {
        for (int i = 0; i < yyleng; i++ )
          yylval.strval[i] = yytext[i];

        yylval.strval[yyleng] = '\0';
        printf ("Achei nome: %s\n", yylval.strval);
        return STRING;
       }


[=]     {
          return IGUAL;
        }

[*]     {
          return MULT;
        }

[/]     {
          return DIV;
        }

[\[\]]     {
          return BRACKET;
        }

\n   {
         return EOL;
       }

[ \t]+ ;

.     {printf("**%s**\n", yytext);
yyerror("Token nao reconhecido!\n");}

%%

int  yywrap() {
  return 1;
}
