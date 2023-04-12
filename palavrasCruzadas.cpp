#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

char matriz_palavras[25][25];
char consoante[22] = {"BCDFGHJKLMNPQRSTVWXYZ"};
char vogal[6] = {"AEIOU"};
char pala[113][20];
int i;
char v1[20];
char pala_info[20];
//
char copia_todos_caracteres_tabela_vertical[626];
char copia_todos_caracteres_tabela_horizontal[626];
char *avaliador;
char *avaliador2;
//
int tamanho;
int sorteia_x;
int sorteia_y;
int horizounoun;
char sentido[20];
//
int x,y,n;
int continuar;
int num_tentativas;
int dica;
//
void sorteia_tabela();
void mostra_tab();
void arquivo();
void sorteia_palavra();
void procurador();

//
int main(){
	continuar = 0;
	num_tentativas = 5;
	while(continuar != 1){
		setlocale(LC_ALL,"PORTUGUESE");
		srand(time(NULL));
		sorteia_tabela();
		arquivo();
		sorteia_palavra();
		printf("\nSentido : %s ",sentido);
		printf("Primeira letra:%c ",v1[0]);
		printf("Tamanho da palavra: %i\n",tamanho);
		mostra_tab();
		do{
			
			printf("\nNumeros de tentativas restantes: %i",num_tentativas);
			printf("\nAcho a palavra-sorteada : ");
			
		
			procurador();
			if(strcmp(pala_info,v1) != 0){
				printf("\nEstá  não é a palavra-sorteada na matriz ");
				num_tentativas--;
				if(num_tentativas == 3){
					printf("\nDeseja uma dica: \n");
					printf("(0)SIM (1)Não ");
					scanf("%d",&dica);
					if(dica == 0){
						for(x=0;x<3;x++){
							printf("%c",v1[x]);
						}	
					}
					
				}

				if(num_tentativas == 0){
					if(strcmp(sentido,"Vertical")){
						printf("\nPosição X: %d Posição Y: %i ",sorteia_x,sorteia_y);
					}
					if(strcmp(sentido,"Horizontal")){
						printf("\nPosição X : %d Posição Y: %i ",sorteia_y,sorteia_x);
					}	
					printf("\nPERDEU!!!Numeros de tentativas excedido");
					printf("\n\npalavra-sorteada: %s",v1);
					break;
				}
					
			}
			
		}while(strcmp(pala_info,v1) != 0);
		if(strcmp(pala_info,v1) == 0){
			printf("\nACERTOU!!!");
			printf("\n\npalavra-sorteada: %s",v1);
		}

		printf("\n\nDeseja jogar novamente  \n(0)SIM (1)NÃO :");
		scanf("%d",&continuar);
		num_tentativas = 5;
		system("clean || cls");	
	}

	return(0);
}
//inicializa (sorteia letras) tabela sem palavras do documento
void sorteia_tabela(){
	
	n = 0;
	//adiciona letras a tabela 25x25
	for(x=0;x<25;x++){
		for(y=0;y<25;y++){
			//adicionando letras vogais e consoantes na proporção 3/1
			if((n==0 )|| (n==2)){
				matriz_palavras[x][y] = vogal[rand()%5];
				
			}
			if(n==1){
				matriz_palavras[x][y] = consoante[rand()%21];
				
			}
			if(n==3){
				matriz_palavras[x][y] = vogal[rand()%5];
				n = 0;
			}
			n++;
			//printf("%d",n);
		}
	
	}	
}


//mostra a matriz 25x25 
void mostra_tab(){
	for(x=0;x<25;x++){
		for(y=0;y<25;y++){
		
			printf("%c ",matriz_palavras[x][y]);
		
		}
		printf("\n");
	}
}

void arquivo(){
	//faz leitura do arquivo e adiciona no vetor as palavras encontradas
	FILE * arquivo;
	arquivo = fopen("palavras.txt","r");
	
	if(arquivo ==NULL){
		printf("Não foi possivel abrir o arquivo");
		exit(1);
	}
	i =0;
	while(!feof(arquivo)){
		fgets(pala[i],500,arquivo);
		if(pala[i][strlen(pala[i])-1]=='\n'){
			pala[i][strlen(pala[i])-1]='\0';
		i++;	
		}
			
	}
	fclose(arquivo);
	
}
void sorteia_palavra(){

	
	//sorteia a posição da palavra na tabela
	horizounoun = rand()%2;
	
	if(horizounoun == 0 || horizounoun ==2){
		strcpy(sentido,"Vertical");
		strcat(sentido,"\0");
		sorteia_x = rand()%13;
		sorteia_y = rand()%25;
		strcpy(v1, pala[rand()%113]);
		strcat(v1,"\0");
		//matriz_palavras[x][y]
		tamanho = strlen(v1);
		y = tamanho;
		i = sorteia_y;
		//posiciona a palavra na tabela
		for(x=sorteia_x;x<(sorteia_x + tamanho );x++){
			matriz_palavras[x][i] = v1[tamanho - y];
			y--;
		}	
	}
	if(horizounoun == 1){
		strcpy(sentido,"Horizontal");
		strcat(sentido,"\0");
		sorteia_x = rand()%25;
		sorteia_y = rand()%13;
		strcpy(v1, pala[rand()%113]);
		//matriz_palavras[x][y]
		tamanho = strlen(v1);
		y = tamanho;
		i = sorteia_y;
		//posiciona a palavra na tabela
		for(x=sorteia_y;x<(sorteia_y + tamanho );x++){
			matriz_palavras[i][x] = v1[tamanho - y];
			
			y--;
		}			
	}
}

void procurador(){
	scanf("%s",&pala_info);
	strupr(pala_info);
			
	int z;
	z=0;
	for(x=0;x<25;x++){
		for(y=0;y<25;y++){
			copia_todos_caracteres_tabela_horizontal[z] = matriz_palavras[x][y];
			z++;
			
		}
	}
	z = 0;
	for(x=0;x<25;x++){
		for(y=0;y<25;y++){
			copia_todos_caracteres_tabela_vertical[z] = matriz_palavras[y][x];
			z++;
			
		}
	}	
	avaliador2 = strstr(copia_todos_caracteres_tabela_vertical,pala_info);
	avaliador = strstr(copia_todos_caracteres_tabela_horizontal,pala_info);
	if((avaliador != NULL) || (avaliador2 != NULL) ){
		printf("\nEssa palavra existe na tabela\n");
	}
	else{
		printf("\nEssa palavra não existe na tabela\n");
	}
}


