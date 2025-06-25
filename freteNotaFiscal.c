#include <stdio.h>
#include <stdlib.h>
//funcoes que atibuem valores diferentes a variavel frete
//frete com o valor da compra ate 100 reais
 void freteAteCemReais(float valorCompra){
     int frete=30;
      printf("\n----------------\n");
      printf("Frete = R$%d",frete);
      printf("\n----------------\n");
}
//frete com o valor da compra de 100 ate 300 reais
 void freteAteTrezentosReais(float valorCompra){
    int frete=20;
       printf("\n----------------\n");
       printf("Frete = R$%d",frete);
       printf("\n----------------\n");
 }
 //frete com o valor da compra acima de 300 reais
 void freteAcimaTrezentos(float valorCompra){
    int frete=0;
     printf("\n----------------\n");
     printf("Frete = R$%d",frete);
     printf("\n----------------\n");
 }
int main()
{
float valorCompra;
int frete=0;
    //leitura do valor da compra
    printf("Digite o valor da compra\nR$");
    scanf("%f",&valorCompra);
    //condicoes dos valores do frete
    //as condicoes determinam os valores das compras que sao determinados para cada valor de frete
    if(valorCompra>300){
            freteAcimaTrezentos(valorCompra);
    }
    if (valorCompra>100 && valorCompra<=300){
            freteAteTrezentosReais(valorCompra);
        }
    if (valorCompra<=100){
         freteAteCemReais(valorCompra);
        }

    return 0;
}