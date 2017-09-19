%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>

void yyerror(char *c);
int yylex(void);

%}
%union {
  char    strval[50];
  float	  fltval;
  int     ival;
}
%token <strval> STRING
%token <fltval> FLOAT
%token <ival> VAR IGUAL MULT DIV BRACKET EOL ASPA
%left SOMA

%%

PROGRAMA:
        PROGRAMA EXPRESSAO EOL
        |
        ;

EXPRESSAO:
    | STRING IGUAL STRING {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
	printf("Copiado com sucesso");
        liberar_imagem(&I);
                          }

    | STRING IGUAL STRING MULT FLOAT {
        printf("Aumentando o brilho de %s em %f vezes\n", $1, $5);
	imagem I = alterar_brilho($3, $5);
        printf("Li imagem %d por %d\n", I.width, I.height);
	printf("Brilho alterado com sucesso!\n");
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                          }

    | STRING IGUAL STRING DIV FLOAT {
        printf("Aumentando o brilho de %s em %f vezes\n", $1, $5);
	imagem I = alterar_brilho($3, 1/($5));
        printf("Li imagem %d por %d\n", I.width, I.height);
	printf("Brilho alterado com sucesso!\n");
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                          }

    | BRACKET STRING BRACKET {
        printf("Verificando o valor máximo dos pixels de %s\n", $2);
	int max = maximo($2);
	printf("O valor máximo entre todos os valores dos pixels de %s é %d\n", $2, max);
                          }

    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
