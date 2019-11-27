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


