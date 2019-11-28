#include <stdio.h>
#include <stdlib.h>

#include "projetoImagens.h"

/*----------------------------------------------------------------------------*/
/** Negativo. Considera apenas o primeiro canal da imagem dada.
 *
 * Parâmetros: Imagem* img: imagem a processar. Olhamos somente o 1o canal.
 *             Imagem* out: imagem de saída
 *
 * Valor de retorno: a saída esperada é armazenada em out. */
void negativo(Imagem* img, Imagem* out)
{
    int i, j;

    for (i = 0; i < img->altura; i++)
        for (j = 0; j < img->largura; j++)
            out->dados[0][i][j] = 255 - img->dados[0][i][j];
}

/*----------------------------------------------------------------------------*/
/** Binarização. Considera apenas o primeiro canal da imagem dada.
 *
 * Parâmetros: Imagem* img: imagem a binarizar. Olhamos somente o 1o canal.
 *             Imagem* out: imagem de saída. Processa apenas o 1o canal.
 *             unsigned char threshold: threshold.
 *
 * Valor de retorno: a saída esperada é armazenada em out. */
void binariza (Imagem* img, Imagem* out, unsigned char threshold) {
    int i, j;
    for(i = 0; i < img->altura; i++)
        for(j = 0; j < img->largura; j++)
            out->dados[0][i][j] = img->dados[0][i][j] >= threshold ? 255 : 0;
}

void rgbParaEscalaDeCinza(Imagem *img, Imagem *out) {
    int i, j;
    for(i = 0; i < img->altura; i++)
        for(j = 0; j < img->largura; j++)
            out->dados[0][i][j] = img->dados[0][i][j] * 0.3 + img->dados[1][i][j] * 0.59 + img->dados[2][i][j] * 0.11;
}

int forwardScan(Imagem *img, int l, int c) {
    int i, j, menor = 255;
    for(i = l-1; i <= l; i++) {
        for(j = c-1; j <= (i == l ? c-1 : c+1); j++) {
            if(i < 0 || i >= img->altura || j < 0 || j >= img->largura)
                break;
            if(img->dados[0][i][j] != 0 && img->dados[0][i][j] < menor)
                menor = img->dados[0][i][j];
        }
    }
    return menor;
}

int backwardScan(Imagem *img, int l, int c) {
    int i, j, menor = 255;
    for(i = l+1; i >= l; --i) {
        for(j = c+1; j >= (i == c ? c+1 : c-1); --j) {
            if(i < 0 || i >= img->altura || j < 0 || j >= img->largura)
                break;
            else if(img->dados[0][i][j] != 0 && img->dados[0][i][j] < menor)
                menor = img->dados[0][i][j];
        }
    }
    return menor;
}

void componentesConexos(Imagem *img, Imagem *out) {
    int i, j, menorRotulo, r = 1;
    char tipoDeScan = -1, modificou = 0;

    *out = *img;

    for(i = 0; i < out->altura; ++i) {
        for(j = 0; j < out->largura; ++j)
            if(out->dados[0][i][j] != 0) {
                menorRotulo = forwardScan(out, i, j);
                if(menorRotulo == 255)
                    out->dados[0][i][j] = r++;
                else
                    out->dados[0][i][j] = menorRotulo;
            } else
                out->dados[0][i][j] = 0;
    }

    do {
        if(tipoDeScan == -1)
            for(i = out->altura-1; i >= 0; --i) {
                for(j = out->largura-1; j >= 0; --j)
                    if(out->dados[0][i][j] != 0) {
                        menorRotulo = backwardScan(out, i, j);
                        if(out->dados[0][i][j] != menorRotulo) {
                            out->dados[0][i][j] = menorRotulo;
                            modificou = 1;
                            tipoDeScan = -tipoDeScan;
                        }
                    }
            }
        else
            for(i = 0; i < out->altura; ++i)
                for(j = 0; j < out->largura; ++j)
                    if(out->dados[0][i][j] != 0) {
                        menorRotulo = forwardScan(out, i, j);
                        if(out->dados[0][i][j] != menorRotulo) {
                            out->dados[0][i][j] = menorRotulo;
                            modificou = 1;
                            tipoDeScan = -tipoDeScan;
                        }
                    }
    } while(modificou == 1);
}
