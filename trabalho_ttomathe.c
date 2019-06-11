#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#define arquivoAluno "aluno.dat"
#define arquivoCurso "curso.dat"
#define arqLista
typedef struct
{
	int dia;
	int mes;
	int ano;

}dt;

typedef struct
{
    int codigo;
	char nome[30];
    char endereco[50];
	char cpf[15];
	int telefone;
	char nascimento[10];
	dt data_nasc;
}aluno;

typedef struct
{
    int codigo;
	char curso[30];
	char duracao[10];
    dt data_PrimeiroSemetre;
}curso;

void cadastraAluno(void);
void cadastraCurso(void);
void consultaAluno(void);
void consultaAlunoNome(void);
void consultaAlunoCPF(void);
void consultaCurso(void);
void consultaCursoCodigo(void);

int main(){
    int op;
	do {
		printf("\n\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); // /t é tab
		printf("\t~   Escolha uma das opcoes   ~\n");
		printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\n\t1- Cadastrar Aluno\n");
		printf("\n\t2- Cadastrar Curso\n");
		printf("\n\t3- Mostrar todos os Alunos Cadastrados\n");
        printf("\n\t4- Consultar Aluno por Nome\n");
		printf("\n\t5- Consultar Aluno por CPF\n");
		printf("\n\t6- Mostrar todos os Cursos Cadastrados\n");
		printf("\n\t7- Consultar Curso por Codigos\n");
		printf("\n\t0- Sair do programa\n\n");
		printf("\tEscola uma Opcao: ");
		scanf("%d", &op);
		switch(op){
		    case 1:
			        system ("cls");//limpar o campo
					cadastraAluno();
		         break;
		    case 2:
					system ("cls");
					cadastraCurso();
		         break;
		    case 3:
					system ("cls");
					consultaAluno();
		         break;
		    case 4:
			        system ("cls");
					consultaAlunoNome();
		         break;
		    case 5:
			        system ("cls");
					consultaAlunoCPF();
		         break;
		    case 6:
			        system ("cls");
					consultaCurso();
		         break;
		    case 7:
			        system ("cls");
					consultaCursoCodigo();
		         break;
		    case 0:
					system ("cls");
			     break;
			default:
			        printf("\n\tOpcao invalida!\n\n");
			        system("pause");
                    break;
        }
	}while(op != 0);
	return 0;
}

void cadastraAluno(){

	FILE * arq;
	aluno registro;
    char aux[15];
    char aux2[15];
    char cpf[15];
    int i=0,j=0;
    int a = 0, num=0;
    do{
		do{
		   printf("\n\n\t     Cadastro de Novo Aluno\n\n");
		        if ((arq = fopen(arquivoAluno, "a+b")) == NULL) { /* o fopen serve para dois propositos
		   primeiro abre um fluxo para usar e ligar um arquivo com ele
		   segundo retorna um ponteiro de arquivo associado aquele arquivo
		   a+b acrescenta ou cria um arquivo binario para leitura ou escrita*/
				fprintf(stderr, "\n\tImpossivel abrir o arquivo %s!\n", arquivoAluno); /* - serve para gravar
				mensagem de erro*/
		          }
		   fseek(arq, 0, SEEK_SET); /*fseek procura por um byte especificado no fluxo. Vai posicionar o 0 seek_set
		   ponteiro no inicio do arquivo */
		   a=0;
		   printf("\nCPF: ");
		   fflush(stdin);
		   gets(cpf);
		   while(fread(&registro, sizeof(aluno), 1, arq) > 0) { // o & é operador de endereço
			if(strncmp(cpf,registro.cpf, strlen(cpf)) == 0){ /* O strncmp compara caracteres de um string e pode ser
			 enumerada a qntd de caracteres a serem comparadas. Usado para validar o cpf que esta sendo cadastrado */
			  a=a+1;
		    }
	       }
		   if(a > 0){
			  printf("\n\n\tJa existe um aluno cadastrado com esse cpf: %s\n\n",cpf);
			  printf("\n\tCPF Invalido !!!\n\n");
		   }
		}while(a > 0);
	    fseek(arq, 0, SEEK_END);
		registro.codigo= ftell(arq) / sizeof(aluno) + 1;
		printf("\tCodigo do Aluno: %d\n\n", registro.codigo);
		printf("\n\nCPF: %s \n",cpf);
	    strcpy(registro.cpf,cpf);

		printf("\nNome: ");
		fflush(stdin);
		gets(registro.nome);
		
		printf("\nData de Nascimento (ddmmaaaa): ");
		scanf("%02d %02d %4d", &registro.data_nasc.dia, &registro.data_nasc.mes, &registro.data_nasc.ano);

		printf("\nEndereco: ");
		fflush(stdin);
		gets(registro.endereco);

		printf("\nTelefone: ");
		fflush(stdin);
		gets(aux);
	    	registro.telefone=atoi(aux);

	    
		fwrite(&registro, sizeof(aluno), 1, arq);
	    system("cls");
	    printf("\n\n\tCliente Cadastrado Com Sucesso!\n\n");
	    fclose(arq);

        printf("\n\tDeseja Cadastrar outro Aluno ?\n\n\t1 - Sim\n\n\t2 - Nao\n\n ");
 	    scanf("%d", &num);
		  while(num < 0 || num > 2){
			  	system ("cls");//usudo para limpar registro
			  	printf("\n\tOpcao Invalida!!\n\n");
                printf("\n\tDeseja Cadastrar outro Aluno ?\n\n");
                printf("\n\tDigite novamente:\n\n\n\t\t1 - Sim\n\n\t\t2 - Nao\n");
  		        scanf("%d", &num);
				system("cls");
	      }
	}while(num==1);
}

void cadastraCurso(){
	FILE * arq;
	curso registro;
	int num=0;
	do{

		printf("\n\n\t     Cadastro de novo Curso \n\n");
		if ((arq = fopen(arquivoCurso, "ab")) == NULL) {
			fprintf(stderr, "\n\tImpossivel abrir o arquivo %s!\n", arquivoCurso);
		}
		fseek(arq, 0, SEEK_END);

		registro.codigo = ftell(arq) / sizeof(curso) + 1;

	       system("cls");
	       printf("Cadastro de Cursos\n\n");

	       printf("Codigo: %d\n\n", registro.codigo);
	       printf("\nNome do Curso: ");
	       fflush(stdin);
		   gets(registro.curso);
	       printf("\nDuracao: ");
	       gets(registro.duracao);
	 	   printf("\nData de Entrada (ddmmaaaa): ");
		   scanf("%02d %02d %4d", &registro.data_PrimeiroSemetre.dia, &registro.data_PrimeiroSemetre.mes, &registro.data_PrimeiroSemetre.ano);

		   fwrite(&registro, sizeof(curso), 1, arq);
    	   system("cls");
		   printf("\n\n\tCurso Cadastrado Com Sucesso!\n\n");

		   fclose(arq);

			printf("\n\tDeseja Cadastrar outro Curso ?\n\n\t1- Sim\n\n\t2- Nao\n\n ");
			scanf("%d", &num);
			while(num < 0 || num > 2){
  		  	     system ("cls");
				 printf("\n\tOpcao Invalida!!\n\n\tDigite novamente:\n\n\t\t1-Sim\n\n\t\t2- Nao\n");
		         scanf("%d", &num);
           }
	}while(num==1);
}

void consultaAluno(){
system("cls");

FILE * arq;
FILE * arq2;
int num=0;

aluno consulta;

	if ((arq = fopen(arquivoAluno, "rb")) == NULL) {
		fprintf(stderr, "\n\tNao existe nenhum aluno cadastrado!\n\n\n");
		printf("\n\ns");
        system("pause");
		return;
	}

	if((arq2 = fopen(arqLista"TodosAlunos.txt", "w")) == NULL) {
		fprintf(stderr, "\n\tErro de abertura do arquivo %s!\n", arqLista"TodosAlunos.txt");
        printf("\n\n");
		system("pause");
		return;
	}

	printf("\n\nAlunos Cadastrados\n\n");
	printf("==========================================================================================================\n");
	printf("Cod.:        Nome:\t      Data de Nascimento:\t\t Endereco:\t Cpf:\t         tel.:\t  \t    \n");
	printf("==========================================================================================================\n\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	while (fread(&consulta, sizeof(aluno), 1, arq) > 0) {

     printf("%-10d %-23s %02d/%02d/%04d\t\t\t %-12s %-16s %-10d \n",consulta.codigo,consulta.nome,consulta.data_nasc.dia,consulta.data_nasc.mes,consulta.data_nasc.ano,consulta.endereco,consulta.cpf,consulta.telefone);

	printf("------------------------------------------------------------------------------------------------------------\n");
	}
	fseek(arq,0,SEEK_SET);

    printf("\n\n\tDeseja gerar um relatorio ?\n\n\tDigite:\n\n\t1- Sim\n\n\t2- Nao\n\n\t");
    scanf("%d", &num);
    while(num<1||num>2){
	  	system ("cls");
	    printf("\n\tOpcao Invalida!!!");
        printf("\n\n\tDeseja gerar um relatorio ?\n\n\tDigite novamente:\n\n\t\t 1- Sim \n\t\t 2- Nao\n ");
        scanf("%d", &num);
    }
    if(num==1){
    	system ("cls");
    	printf("==========================================================================\n");
        printf("\n\n\tRelatorio gerado e enviado por e-mail com sucesso!!\n\n");
		printf("==========================================================================\n");
   }
   else if(num==2){
		   system ("cls");
		  	return;
   }
    system("pause");
    system("cls");
    fclose(arq);
    fclose(arq2);
}
void consultaAlunoNome(){
system("cls");

FILE * arq;
FILE * arq2;

aluno consulta;
int num=0,num2=0;
char nome[50];
int achei = 0;

int i=0,j=0;

	do{
		if ((arq = fopen(arquivoAluno, "rb")) == NULL) {
			fprintf(stderr, "\n\tNao existe nenhum aluno cadastrado!\n");
			printf("\n\n");
			system("pause");
            return;
		}
		if((arq2 = fopen(arqLista"PesquisaAlunoNome.txt", "w")) == NULL) {
			fprintf(stderr, "\n\tErro de abertura do arquivo %s!\n", arqLista"PesquisaAlunoNome.txt");
			printf("\n\n");
            system("pause");
            return;
		}
		printf("\n\n\t     Pesquisa de alunos por nome\n\n");
	    do{
			printf("\tNome do Aluno: ");
			scanf(" %50[^\n]", nome);
		    printf("\n\n");
			rewind(arq);
	        printf("\n\nAlunos cadastrados com esse nome:%s\n\n",nome);
	        printf("==========================================================================================================\n");
			printf("Cod.:        Nome:\t      Data de Nascimento:\t\t Endereco:\t Cpf:\t         tel.:\t  \t    \n");
			printf("==========================================================================================================\n\n");
			printf("------------------------------------------------------------------------------------------------------------\n");
	
			while(fread(&consulta, sizeof(aluno), 1, arq) > 0)
            {
			  for(i=0;i< (strlen(nome));i++)
              {
			  	nome[i]=toupper(nome[i]);
				for(j=0;j<(strlen(consulta.nome));j++)
                {
			  		consulta.nome[j]=toupper(consulta.nome[j]);
			  	}
			  }
			  if(strncmp(nome,consulta.nome, strlen(nome)) == 0)
              {
                   printf("%-10d %-23s %02d/%02d/%04d\t\t\t %-12s %-16s %-10d \n",consulta.codigo,consulta.nome,consulta.data_nasc.dia,consulta.data_nasc.mes,consulta.data_nasc.ano,consulta.endereco,consulta.cpf,consulta.telefone);
	               printf("------------------------------------------------------------------------------------------------------------\n");
				   achei = 1;
			  }
			}
	        printf("==========================================================================================================\n\n");
		    if (!achei){
			  printf("\n\n\tNao existe aluno cadastrado com esse nome: %s\n\n",nome);
			  printf("\n\tDigite Novamente !\n\n");
			}

		}while(!achei);

		fseek(arq,0,SEEK_SET);

		printf("\n\n\tDeseja Gerar Um Relatorio ?\n\n\tDigite:\n\n\t1- Sim\n\n\t2- Nao\n\n\t");
		scanf("%d", &num);
		while(num<1||num>2)
		{
           system ("cls");
		   printf("\n\tOpcao Invalida!!!\n\n");
           printf("\tDeseja Gerar Um Relatorio ?\n\n");
           printf("\tDigite novamente:\n\n\t\t 1- Sim \n\t\t 2- Nao\n");
		   scanf("%d", &num);
        }

		if(num==1){
			system ("cls");
    		printf("==========================================================================\n");
        	printf("\n\n\tRelatorio gerado e enviado por e-mail com sucesso!!\n\n");
			printf("==========================================================================\n");
   			system("pause");
			}

	    system("cls");
	    fclose(arq);
	    fclose(arq2);

		printf("\n\tDeseja Realizar Outra Pesquisa ?\n\n\t1- Sim\n\n\t2- Nao\n\n ");
		scanf("%d", &num2);
		while(num2 < 0 || num2 > 2)
		{
			system ("cls");
		    printf("\n\tOpcao Invalida!!!\n\n");
            printf("\tDeseja Realizar Outra Pesquisa ?\n\n");
            printf("\tDigite novamente:\n\n\t\t 1-Sim \n\t\t 2- Nao).\n");
      		scanf("%d", &num2);
		}
	system("cls");
	}while(num2==1);
}

void consultaAlunoCPF(){
system("cls");

FILE * arq;
FILE * arq2;

aluno consulta;
int num=0,num2=0;
char cpf[15];
int achei = 0;
int i=0,j=0;

	do{
		if ((arq = fopen(arquivoAluno, "rb")) == NULL)
        {
			fprintf(stderr, "\n\tErro: Nao existe nenhum aluno cadastrado!\n");
		    printf("\n\n");
        	system("pause");
            return;
		}
		if((arq2 = fopen(arqLista"PesquisaAlunoCPF.txt", "w")) == NULL)
        {
			fprintf(stderr, "\n\tErro de abertura do arquivo %s!\n", arqLista"PesquisaAlunoCPF.txt");
			printf("\n\n");
            system("pause");
    		return;
		}
		printf("\n\n\t   Consultar Aluno por cpf    \n\n");
	 do{
			printf("\tCPF do Aluno: ");
			fflush(stdin);
			gets(cpf);
		    printf("\n\n");

			rewind(arq);

			printf("\n\n\t\tAluno com esse cpf: %s\n\n",cpf);
	        printf("==========================================================================================================\n");
			printf("Cod.:        Nome:\t      Data de Nascimento:\t\t Endereco:\t Cpf:\t         tel.:\t  \t    \n");
			printf("==========================================================================================================\n\n");
			printf("------------------------------------------------------------------------------------------------------------\n");

			while(fread(&consulta, sizeof(aluno), 1, arq) > 0)
            {
			  for(i=0;i< (strlen(cpf));i++)
              {
			  	cpf[i]=toupper(cpf[i]);
				  for(j=0;j<(strlen(consulta.cpf));j++)
                  {
			  		consulta.cpf[j]=toupper(consulta.cpf[j]);
			  	  }
			  }
			  if(strncmp(cpf,consulta.cpf, strlen(cpf)) == 0)
              {
                printf("%-10d %-23s %02d/%02d/%04d\t\t\t %-12s %-16s %-10d \n",consulta.codigo,consulta.nome,consulta.data_nasc.dia,consulta.data_nasc.mes,consulta.data_nasc.ano,consulta.endereco,consulta.cpf,consulta.telefone);
                printf("------------------------------------------------------------------------------------------------------------\n");
				achei = 1;
 			  }
			}
	        
		    if (!achei){
			  printf("\n\n\tNao existe aluno cadastrado com  esse CPF: %s\n\n",cpf);
			  printf("\n\tDigite Novamente !\n\n");
			}

		}while(!achei);

		fseek(arq,0,SEEK_SET);

	    printf("\n\n\tDeseja Gerar Um Relatorio ?\n\n\tDigite:\n\n\t1- Sim\n\n\t2- Nao\n\n\t ");
		scanf("%d", &num);
		while(num<1||num>2)
        {
           	system ("cls");
			printf("\n\tOpcao Invalida!!!\n\n");
            printf("\tDeseja Gerar Um Relatorio ?\n\n");
            printf("\tDigite novamente:\n\n\t\t 1- Sim\n\n\t\t 2- Nao\n");
		    scanf("%d", &num);
        }
		if(num==1)
        {
			system ("cls");
    		printf("==========================================================================\n");
        	printf("\n\n\tRelatorio gerado e enviado por e-mail com sucesso!!\n\n");
			printf("==========================================================================\n");
			system("pause");
		}
	    system("cls");
	    fclose(arq);
	    fclose(arq2);

		printf("\n\tDeseja Realizar Outra Pesquisa ?\n\n\t1- Sim\n\n\t2- Nao\n\n ");
		scanf("%d", &num2);
		while(num2 < 0 || num2 > 2)
        {
			system ("cls");
			printf("\n\tOpcao Invalida!!!\n\n\tDigite novamente:\n\n\t\t 1-Sim \n\t\t 2- Nao).\n");
		    scanf("%d", &num2);
		}
  		system("cls");
	}while(num2==1);
}

void consultaCurso (){

system("cls");

FILE * arq;
FILE * arq2;
int num=0;

curso consulta;

	if ((arq = fopen(arquivoCurso, "rb")) == NULL) { //rb- abrir arquivo para leitura e deve estar presente no disco
		fprintf(stderr, "\n\tErro: Nao existe nenhum Aluno cadastrado!\n\n\n");
		printf("\n\n");
        system("pause");
		return;
	}
	if((arq2 = fopen(arqLista"TodosCurso.txt", "w")) == NULL) {
		fprintf(stderr, "\n\tErro de abertura do arquivo %s!\n", arqLista"TodosCurso.txt");
		printf("\n\n");
        system("pause");
		return;
	}
	printf("\n\n\t\t\t\tAluno(s) cadastrado(s)\n\n");
	printf("=========================================================================\n");
	printf(" Cod.:                Nome:             Duracao:    Data Criacao:  \n");
	printf("=========================================================================\n\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&consulta, sizeof(curso), 1, arq) > 0) {
	 printf(" %04d %20s %-12s %02d/%02d/%04d\n",consulta.codigo, consulta.curso, consulta.duracao, consulta.data_PrimeiroSemetre.dia,consulta.data_PrimeiroSemetre.mes,consulta.data_PrimeiroSemetre.ano);
	 printf("-------------------------------------------------------------------------\n");
	}
	

	fseek(arq,0,SEEK_SET);

    printf("\n\n\tDeseja Gerar Um Relatorio ?\n\n\tDigite:\n\n\t1- Sim\n\n\t2- Nao\n\n\t");
	scanf("%d", &num);
	while(num<1||num>2)
    {
	  	system ("cls");
	  	printf("\n\tNumero Invalido!!!\n\n\tDigite novamente");
	  	scanf("%d", &num);
	}
	if(num==1){
		    system ("cls");
    		printf("==========================================================================\n");
        	printf("\n\n\tRelatorio gerado e enviado por e-mail com sucesso!!\n\n");
			printf("==========================================================================\n");

		}else{
		   system ("cls");
		  	return;
		}


    system("pause");
	system ("cls");
    fclose(arq);
    fclose(arq2);
}

void consultaCursoCodigo(){

	FILE * arq;
	FILE * arq2;
	curso consulta;
	int codigo,num=0,num2=0;

	int achei = 0;
	int i=0,j=0;


	do{

		if ((arq = fopen(arquivoCurso, "rb")) == NULL) {
			fprintf(stderr, "\n\tErro: Nao existe nenhum Curso cadastrado!\n");
      		printf("\n\n");
            system("pause");
			return;
		}

		if((arq2 = fopen(arqLista"PesquisaCursoCodigo.txt", "w")) == NULL) {
			fprintf(stderr, "\n\tErro de abertura do arquivo %s!\n",arqLista"PesquisaCursoCodigo.txt");
            printf("\n\n");
			system("pause");
    		return;
		}

	 do{
			printf("\tCodigo do Curso: ");
			fflush(stdin);
			scanf("%d", &codigo);
		    printf("\n\n");

			rewind(arq);

			printf("\n\n\t\t\t\tCurso cadastrado com o codigo: %d\n\n",codigo);
			printf("=========================================================================\n");
			printf(" Cod.: Titulo:                       Duracao:    Data Primeiro Semestre:  \n");
			printf("=========================================================================\n\n");
			printf("-------------------------------------------------------------------------\n");
			while(fread(&consulta, sizeof(curso), 1, arq) > 0) {

				if( codigo == consulta.codigo){
		 			printf(" %04d %-30s %-10s  %02d/%02d/%04d   \n",consulta.codigo, consulta.curso, consulta.duracao,
					  consulta.data_PrimeiroSemetre.dia,consulta.data_PrimeiroSemetre.mes,consulta.data_PrimeiroSemetre.ano);
					printf("-------------------------------------------------------------------------\n");

						 achei = 1;
				}
			}
			printf("\n=========================================================================\n\n");

		    if (!achei){

			  system ("cls");
			  printf("\n\n\tNao existe Cursos cadastrados com esse titulo: %d\n\n",codigo);
			  printf("\n\tDigite Novamente !\n\n");

			}

		}while(!achei);

		fseek(arq,0,SEEK_SET);

		printf("\n\n\tDeseja Gerar Um Relatorio ?\n\n\tDigite:\n\n\t1- Sim\n\n\t2- Nao\n\n\t ");
		scanf("%d", &num);
		while(num<1||num>2)
        {
			system ("cls");
			printf("\n\tOpcao Invalida!!!\n\n\tDigite novamente:\n\n\t\t 1- Sim \n\t\t 2- Nao\n");
       		scanf("%d", &num);
		}
		if(num==1)
        {
			system ("cls");
    		printf("==========================================================================\n");
        	printf("\n\n\tRelatorio gerado e enviado por e-mail com sucesso!!\n\n");
			printf("==========================================================================\n");
			system("pause");
      	}
	    system("cls");
	    fclose(arq);
	    fclose(arq2);

		printf("\n\tDeseja Realizar Outra Pesquisa ?\n\n\t1- Sim\n\n\t2- Nao\n\n ");
		scanf("%d", &num2);
		while(num2 < 0 || num2 > 2)
        {
			system ("cls");
			printf("\n\tOpcao Invalida!!!\n\n\tDeseja Realizar Outra Pesquisa ?\n\n\tDigite novamente:\n\n\t\t 1-Sim \n\t\t 2- Nao).\n");
		    scanf("%d", &num2);
        }
    system("cls");
	}while(num2==1);
}

