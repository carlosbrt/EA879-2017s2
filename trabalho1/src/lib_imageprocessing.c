
#include <stdlib.h>
#include <stdio.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
imagem alterar_brilho(char *nome_do_arquivo, float brilho)
int maximo(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *i);
 */

imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   }
  return I;

}

imagem alterar_brilho(char *nome_do_arquivo, float brilho) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = (color.rgbRed);
      I.g[idx] = (color.rgbGreen);
      I.b[idx] = (color.rgbBlue);
    }
   }

   for (int k=0; k<x; k++) {
     for (int l=0; l <y; l++) {
      int idx, valor_max, brilho_max;
      FreeImage_GetPixelColor(bitmapIn, k, l, &color);

      idx = k + (l*x);
      valor_max = 255;
      brilho_max = valor_max/brilho;
      
      if (I.r[idx] < brilho_max) {
       I.r[idx] = brilho*I.r[idx];
      }
      else I.r[idx] = valor_max;

      if (I.g[idx] < brilho_max){
       I.g[idx] = brilho*I.g[idx];
      }
      else I.g[idx] = valor_max;

      if (I.b[idx] < brilho_max){
       I.b[idx] = brilho*I.b[idx];
      }
      else I.b[idx] = valor_max;

     }
   }
  return I;

}

int maximo(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  int max_r, max_g, max_b, max;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = (color.rgbRed);
      I.g[idx] = (color.rgbGreen);
      I.b[idx] = (color.rgbBlue);
    }
   }

   for (int k=0; k<x; k++) {
     for (int l=0; l<y; l++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, k, l, &color);

      idx = k + (l*x);
            
      if (idx != 0) {
       if (I.r[idx] > I.r[idx-1])
        max_r = I.r[idx];
      }
      else max_r = I.r[idx];

      if (idx != 0) {
       if (I.g[idx] > I.g[idx-1])
        max_g = I.g[idx];
      }
      else max_g = I.g[idx];

      if (idx != 0) {
       if (I.b[idx] > I.b[idx-1])
        max_b = I.b[idx];
      }
      else max_b = I.b[idx];

     }
   }

     if (max_r > max_g){
      if (max_r > max_b)
	max = max_r;
      else max = max_b; 
     }
     else if (max_g > max_b)
      max = max_g;
     else max = max_b;

  return max;

}

void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}

