#include <stdio.h>
#include <stdlib.h>
#include "imagem.h" //Desenvolvida pelo prof. Bogdan.
/*============================================================================*/

char* ARQUIVOS [] = //imagens da pasta img foram geradas pelo prof. Bogdan.
{
    "img2/exemplo-01.bmp",
    "img2/VEI2.bmp",
    "img2/back.bmp",
    "img2/lenna.bmp",
    "img2/celula01.bmp",
    "img2/celula02.bmp",
    "img2/tulipNoise2.bmp",
    "img2/borboleta.bmp",
};

#define N_ARQUIVOS 1 //está testando apenas as 3 primeiras imagens da lista
#define TAM_JANELA 3
#define DEBUG_MODE /* Setar para gravar imagens intermediárias. */


void imprimeMatriz(Imagem *img) {
    int i, j;
    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            printf("%d ", img->dados[0][i][j]);
        }
        putchar('\n');
    }
}


/******************************************************************
Função principal
*******************************************************************/
int main ()
{
    int i, op, limiar;
    Imagem *img, *out; // Imagem de entrada/saida
    char nome_saida [25]; // String usada para armazenar os nomes das saídas

    printf("\nO que deseja fazer?\n");
    printf("1 - negativo\n");
    printf("2 - binarizacao\n");
    printf("3 - filtro da media\n");
    printf("4 - RGB para escala de cinza\n");
    printf("5 - contagem de componentes conexos\n");
    scanf("%d", &op);

    for (i = 0; i < N_ARQUIVOS; i++)
    {
        img = abreImagem (ARQUIVOS [i]);
        if (!img)
        {
            printf ("Nao conseguiu abrir %s\n", ARQUIVOS [i]);
            return (1);
        }
        printf ("Processando imagem %s...\n", ARQUIVOS [i]);

        switch(op)
        {
            case 1:
                out = criaImagem(img->largura, img->altura, 1);
                negativo(img, out);

                #ifdef DEBUG_MODE
                Imagem* debug = criaImagem (img->largura, img->altura, 1); //poderia salvar direto a out, mas vamos ilustrar como seria uma cópia!
                for (int row = 0; row < img->altura; row++)
                    for (int col = 0; col < img->largura; col++)
                        debug->dados [0][row][col] = out->dados [0][row][col];
                char outFile[50];
                sprintf(outFile,"1-negative-%d.bmp", i);
                salvaImagem (debug, outFile);
                destroiImagem (debug);
                #endif
                break;
            case 2:
                out = criaImagem(img->largura, img->altura, 1);
                binariza(img, out, 128);

                #ifdef DEBUG_MODE
                sprintf(outFile,"2-bin-%d.bmp", i); //aqui salva direto out
                salvaImagem (out, outFile);
                #endif
                break;
            case 3:
                out = criaImagem(img->largura, img->altura, 1);
                //filtroMedia(img, out, TAM_JANELA);

                #ifdef DEBUG_MODE
                sprintf(outFile,"3-filtro-%d.bmp", i); //aqui salva direto out
                salvaImagem (out, outFile);
                #endif
                break;
            case 4:
                out = criaImagem(img->largura, img->altura, 1);
                rgbParaEscalaDeCinza(img, out);

                #ifdef DEBUG_MODE
                sprintf(outFile,"4-cinza-%d.bmp", i); //aqui salva direto out
                salvaImagem (out, outFile);
                #endif
                break;
            case 5:

                break;
            default:
                printf("Opcao invalida!");
        }
        destroiImagem (img);
    }


    return (0);
}




