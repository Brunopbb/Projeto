#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <ctype.h>
#include <time.h>

typedef struct{

	char nome[30], curso[30], cpf[10];
	int matricula;

}ALUNO;

typedef struct {

	int codigo_paciente;
	char nome[30], nascimento[15], cpf[15], end[30];
	
}PACIENTE;

typedef struct {

	int codigo_professor;
	char nome[30], curso[30];
	
}SUPERVISOR;

typedef struct{

	int codigo_agendamento;
	PACIENTE p;
	char area_atendimento[30], data[15];

}AGENDAMENTOS;

typedef struct{

	int codigo_atendimento;
	AGENDAMENTOS agenda;
	ALUNO aluno;
	PACIENTE p;
	SUPERVISOR sup;

}ATENDIMENTOS;

//SISTEMA
int verificar_conteudo(char nome_arquivo[]);
void menu_Sistema();
void iniciar_arq();

//ALUNO
void cadastrar_aluno();
void listar_alunos();
void remover_alunos();
void editar_Alunos();
void menu_Aluno();
void gerenciador_de_Alunos();


//PACIENTE
void cadastrar_Paciente();
void listar_Pacientes();
void remover_Pacientes();
void editar_Pacientes();
int verificar_codigo_Paciente();
void menu_Paciente();
void gerenciador_de_Paciente();

//SUPERVISORES
void cadastrar_Supervisor();
void listar_Supervisores();
void remover_Supervisores();
void editar_supervisores();
int verificar_codigo_Supervisor();
void gerenciador_de_Supervisores();
void menu_supervisor();


//AGENDAMENTO
void cadastrar_Agendamentos();
void listar_Agendamentos();
void remover_Agendamento();
void menu_Agendamentos();
int verificar_codigo_Agendamento(int codigo);
void gerenciador_Agendamentos();

//ATENDIMENTO
void gerenciador_Atendimentos();
void cadastrar_Atendimentos();
void listar_Atendimentos();
void listar_por_Area();
void listar_por_Aluno();
void listar_por_Paciente();
void remover_P(int codigo);
void remover_Atendimentos();
void menu_Atendimentos();
int verificar_codigo_Atendimento(int codigo);


//////////////////////////
//MENU PRICIPAL
//////////////////////////

int main(){



	
	
	iniciar_arq();
	menu_Sistema();


	



}

//////////////////////////
//FUNÇÕES DO SISTEMA
//////////////////////////

void iniciar_arq(){

	FILE *alunos, *paciente, *supervisor, *age, *atende;
	alunos = fopen("alunos.txt", "a + b");
	paciente = fopen("paciente.txt", "a + b");
	supervisor = fopen("supervisores.txt", "a + b");
	age = fopen("agendamentos.txt", "a + b");
	atende = fopen("atendimentos.txt", "a + b");


}



void menu_Sistema(){
	int op;
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.....................\n");
	printf("================================================================================\n\n");
	printf("\t1 - MENU DE ALUNOS               3 - MENU DE SUPERVISORES\n\n");
	printf("\t2 - MENU DE PACIENTES            4 - MENU DE AGENDAMENTOS\n\n");
	printf("\t5 - MENU DE ATENDIMENTOS         6 - SAIR\n\n");
	printf("\n\tDIGITE A OPÇÃO: ");
	scanf("%d", &op);

	if(op > 6 || op < 1){
		printf("\n\t\t\t\tOPÇÃO INVALIDA!\n");
		sleep(2);
		system("clear");
		menu_Sistema();
		
	}

	switch(op){
		case 1:
			system("clear");
			gerenciador_de_Alunos();
			menu_Sistema();
			break;
		case 2:
			system("clear");
			gerenciador_de_Paciente();
			menu_Sistema();
			break;
		case 3:
			system("clear");
			gerenciador_de_Supervisores();
			menu_Sistema();
			break;
		case 4:
			system("clear");
			gerenciador_Agendamentos();
			menu_Sistema();
			break;
		case 5:
			system("clear");
			gerenciador_Atendimentos();
			menu_Sistema();
			break;
		case 6:
			printf("\n\n\t\t\tSISTEMA SENDO DESLIGADO. AGUARDE...\n");
			sleep(3);
			break;
		
	
		
	}
	

}

int verificar_conteudo(char nome_arquivo[]){
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if(arquivo == NULL)
        return 0;

    fseek(arquivo, 0, SEEK_END);
    int tam = ftell(arquivo);
    fclose(arquivo);

    return tam;
}



//////////////////////////
//FUNÇÕES DO ALUNO
//////////////////////////

void gerenciador_de_Alunos(){
	int op;

	do{	

		system("clear");
		menu_Aluno();
		printf("\t\t\t\tDIGITE A OPÇÃO: ");
		scanf("%d", &op);

		if(op > 5 || op < 1){
			printf("\n\t\t\t\tOPÇÃO INVALIDA!\n");
			sleep(2);
			menu_Aluno();
		}

		switch(op){
			case 1:
				system("clear");
				cadastrar_aluno();
				sleep(2);
				menu_Aluno();
				break;
			case 2:
				system("clear");
				remover_alunos();
				sleep(2);
				menu_Aluno();
				break;
			case 3:
				system("clear");
				editar_Alunos();
				sleep(2);
				menu_Aluno();
				break;
			case 4:
				system("clear");
				listar_alunos();
				menu_Aluno();
				break;

		}

	}while(op != 5);


}




void menu_Aluno(){
	
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t\t++++++  MENU DO ALUNO  ++++++\n\n");
	printf("\t1 - CADASTRAR ALUNOS               3 - EDITAR ALUNOS\n\n");
	printf("\t2 - REMOVER ALUNOS                 4 - LISTAR TODOS OS ALUNOS\n\n");
	printf("\t5 - SAIR\n\n");
	




}




int verificar_matricula_Aluno(int matricula){

	FILE *arquivo;
	ALUNO aluno;
	arquivo = fopen("alunos.txt", "rb");

	while(fread(&aluno, sizeof(ALUNO), 1, arquivo) == 1){
		if(matricula == aluno.matricula){
			return 0;
		}
	}

	return 1;

}


void pegar_nome_Aluno(int matricula, char nome[]){

	FILE *arquivo;
	arquivo = fopen("alunos.txt", "rb");
	ALUNO aluno;

	while(fread(&aluno, sizeof(ALUNO), 1, arquivo) == 1){
		if(matricula == aluno.matricula){
			strcpy(nome, aluno.nome);
		}
	}
}


void cadastrar_aluno(){

	ALUNO aluno;
	int mat;
	FILE *arquivo;
	char op;

	arquivo = fopen("alunos.txt", "a+b");
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t   ++++++  MENU DO ALUNO (CADASTRO) ++++++\n\n");
	printf("--------------------------------------------------------------------------------\n\n");

	srand((unsigned)time(NULL));

	mat = 1 + rand();

	if(verificar_matricula_Aluno(mat)){

		aluno.matricula = mat;

		printf("\n\t\t\tSUA MATRICULA É: %d\n", aluno.matricula);

		printf("\n\t\t\tDIGITE O NOME DO ALUNO: ");
		scanf(" %[^\n]", aluno.nome);

		printf("\n\t\t\tDIGITE O CURSO DO ALUNO: ");
		scanf(" %[^\n]", aluno.curso);

		printf("\n\t\t\tDIGITE O CPF DO ALUNO: ");
		scanf(" %[^\n]", aluno.cpf);

		printf("\n\t\tTEM CERTEZA QUE DESEJA CADASTRAR? (S - SIM, N - NÃO): ");
		scanf(" %c", &op);
		if(op == 'S'){
			fwrite(&aluno, sizeof(ALUNO), 1, arquivo);
			printf("\n\t\t\t\tALUNO CADASTRADO!\n");
		}else{
			printf("\n\t\t\t\tALUNO NÃO CADASTRADO!\n");
		}
		fclose(arquivo);

	}else{

		printf("\n\n\t\t\tESSA MATRICULA JÁ EXISTE!\n");
		sleep(3);
		cadastrar_aluno();
	}

}

	

void listar_alunos(){

	ALUNO aluno;
	FILE *arquivo;

	arquivo = fopen("alunos.txt", "rb");
	char *nome = "alunos.txt", op;
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO ALUNO (ALUNOS CADASTRADOS) ++++++\n\n");
	printf("--------------------------------------------------------------------------------\n\n");

	if(arquivo != NULL){

		if(verificar_conteudo(nome) == 0)

			printf("\t\t\t NÃO HÁ ALUNOS CADASTRADOS!\n");

		else{

			rewind(arquivo);
			while(fread(&aluno, sizeof(ALUNO), 1, arquivo) == 1){
				
				printf("\t\t\t   ====================\n");
				printf("\t\t\t   NOME %s\n", aluno.nome);
				printf("\t\t\t   MATRICULA: %d\n", aluno.matricula);
				printf("\t\t\t   CURSO: %s\n", aluno.curso);
				printf("\t\t\t   CPF: %s\n", aluno.cpf);
				printf("\t\t\t   ====================\n");
				sleep(1);
			}

		}fclose(arquivo);

	}else{
		printf("\n\t\t\t  NÃO HÁ ALUNOS CADASTRADOS!\n");
	}

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}
}



void remover_alunos(){

	ALUNO aluno;
	int matricula;

	FILE *arquivo, *novo_arquivo;

	char *nome_antigo = "alunos.txt", *nome_novo = "al.txt", op;

	arquivo = fopen("alunos.txt", "r + b");
	novo_arquivo = fopen("al.txt", "a + b");
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO ALUNO (REMORÇÃO) ++++++\n\n");

	

	if(verificar_conteudo("alunos.txt") == 0){

		printf("\n\t\t\tNÃO EXISTEM ALUNOS CADASTRADOS\n");

	}else{

		printf("\t\tDIGITE A MATRICULA DO ALUNO A SER REMOVIDO: ");
		scanf("%d", &matricula);

		if(verificar_matricula_Aluno(matricula) == 0){

			printf("\n\t  TEM CERTEZA QUE DESEJA REMOVER O ALUNO (S - SIM, N - NÃO): ");
			scanf(" %c", &op);
			if(op == 'S'){

				while(fread(&aluno, sizeof(ALUNO), 1, arquivo) == 1){
					if(matricula != aluno.matricula){
						fwrite(&aluno, sizeof(ALUNO), 1, novo_arquivo);
					}
				}
				printf("\n\t\t\t\tALUNO REMOVIDO!\n");
				remove("alunos.txt");
				rename(nome_novo, nome_antigo);
				fclose(arquivo);
				fclose(novo_arquivo);
			}else{
				printf("\n\t\t\t\tALUNO NÃO REMOVIDO\n");
			}
			
		}else{
			printf("\n\t\t\tESSE ALUNO NÃO ESTÁ CADASTRADO!\n");
		}
	}

}

void editar_Alunos(){

	ALUNO aluno;
	int matricula;

	FILE *arquivo, *novo_arquivo;

	char *nome_antigo = "alunos.txt", *nome_novo = "al.txt", op, nome[30];

	arquivo = fopen("alunos.txt", "r + b");
	novo_arquivo = fopen("al.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t  ++++++  MENU DO ALUNO (EDIÇÃO) ++++++\n\n");

	

	if(verificar_conteudo(nome_antigo) != 0){

		printf("\t\tDIGITE A MATRICULA DO ALUNO A SER EDITADO: ");
		scanf("%d", &matricula);

		if(verificar_matricula_Aluno(matricula) == 0){

			while(fread(&aluno, sizeof(ALUNO), 1, arquivo) == 1){
				if(matricula != aluno.matricula){

					fwrite(&aluno, sizeof(ALUNO), 1, novo_arquivo);

				}else if(matricula == aluno.matricula){

					printf("\n\t\tVOCE ESTÁ EDITANDO O ALUNO: %s\n", aluno.nome);
					printf("--------------------------------------------------------------------------------\n");
					printf("\n\t\t\tNOVA MATRICULA: ");
					scanf(" %d", &matricula);

					pegar_nome_Aluno(matricula, nome);

					if((verificar_matricula_Aluno(matricula) == 0) && strcmp(nome, aluno.nome) != 0){
						printf("\n\t\t\t  ESSA MATRICULA JÁ EXISTE!\n");
						sleep(2);
						menu_Aluno();
					}else{

						aluno.matricula = matricula;
						printf("\n\t\t\tNOVO NOME: ");
						scanf(" %[^\n]", aluno.nome);


						printf("\n\t\t\tNOVO CURSO: ");
						scanf(" %[^\n]", aluno.curso);

						printf("\n\t\t\tNOVO CPF: ");
						scanf(" %[^\n]", aluno.cpf);

						printf("\n\t\tTEM CERTEZA QUE QUER EDITAR O ALUNO? (S - SIM, N - NÃO): ");
						scanf(" %c", &op);
						if(op == 'S'){
							fwrite(&aluno, sizeof(ALUNO), 1, novo_arquivo);
							printf("\n\t\t\t\tALUNO EDITADO!\n");
							remove("alunos.txt");
							rename(nome_novo, nome_antigo);
						}
						else{
							printf("\n\t\t\t\tALUNO NÃO EDITADO\n");
							fwrite(&aluno, sizeof(ALUNO), 1, novo_arquivo);
						}
					}


				}
			}
		}else{

			printf("\n\t\t\tESSE ALUNO NÃO EXISTE! AGUARDE...\n");

		}
	}else{

			printf("\n\t\tNÃO EXISTEM ALUNOS CADASTRADOS! AGUARDE...\n");
			return;
	}

	

	fclose(novo_arquivo);

}

///////////////////////////////
//FUNÇÕES DO PACIENTE
///////////////////////////////


void menu_Paciente(){
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t\t++++++  MENU DO PACIENTE  ++++++\n\n");
	printf("\t1 - CADASTRAR PACIENTES               3 - EDITAR PACIENTES\n\n");
	printf("\t2 - REMOVER PACIENTES                 4 - LISTAR TODOS OS PACIENTES\n\n");
	printf("\t5 - SAIR\n\n");
}

void gerenciador_de_Paciente(){

	int op;

	do{
		system("clear");
		menu_Paciente();
		printf("\n\t\t\t\tDIGITE A OPÇÃO: ");
		scanf("%d", &op);

			switch(op){
			case 1:
				system("clear");
				cadastrar_Paciente();
				sleep(2);
				menu_Paciente();
				break;
			case 2:
				system("clear");
				remover_Pacientes();
				sleep(2);
				menu_Paciente();
				break;
			case 3:
				system("clear");
				editar_Pacientes();
				sleep(2);
				menu_Paciente();
				break;
			case 4:
				system("clear");
				listar_Pacientes();
				menu_Paciente();


			}
		}while(op != 5);

}


int verificar_codigo_Paciente(int codigo){

	FILE *arquivo;
	PACIENTE p;
	
	arquivo = fopen("paciente.txt", "rb");

	while(fread(&p, sizeof(PACIENTE), 1, arquivo) == 1){
		if(codigo == p.codigo_paciente){
			return 0;
		}
		
	}

	return 1;

}

void pegar_informacoes_Paciente(int codigo, char nome[]){

	FILE *arquivo;
	PACIENTE p;

	arquivo = fopen("paciente.txt", "rb");


	while(fread(&p, sizeof(PACIENTE), 1, arquivo) == 1){
		if(codigo == p.codigo_paciente){
			strcpy(nome, p.nome);
		}
	}fclose(arquivo);

}


void cadastrar_Paciente(){

	PACIENTE p;
	int codigo;
	char op;
	FILE *arquivo;
	arquivo = fopen("paciente.txt", "a+b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO PACIENTE (CADASTRADO) ++++++\n\n");

	srand((unsigned)time(NULL));

	codigo = 1 + rand();

	if(verificar_codigo_Paciente(codigo)){

		p.codigo_paciente = codigo;

		printf("\n\t\t\tO SEU CODIGO É: %d\n", p.codigo_paciente);

		printf("\n\t\t\tDIGITE O NOME DO PACIENTE: ");
		scanf(" %[^\n]", p.nome);

		printf("\n\t\t\tDATA DE NASCIMENTO DO PACIENTE: ");
		scanf(" %[^\n]", p.nascimento);

		printf("\n\t\t\tDIGITE O CPF DO PACIENTE: ");
		scanf(" %[^\n]", p.cpf);

		printf("\n\t\t\tDIGITE O ENDEREÇO DO PACIENTE: ");
		scanf(" %[^\n]", p.end);

		printf("\n\t\tTEM CERTEZA QUE DESEJA CADASTRAR? (S - SIM, N - NÃO): ");
		scanf(" %c", &op);
		if(op == 'S'){
			printf("\n\n\t\t\t\tPACIENTE CADASTRADO!\n");
			fwrite(&p, sizeof(PACIENTE), 1, arquivo);
		}else{
			printf("\n\t\t\t\tPACIENTE NÃO CADASTRADO!\n");
		}

		fclose(arquivo);

	}else{

		printf("\n\t\t\t\tESSE CODIGO JÀ EXISTE!\n");
		sleep(3);
		cadastrar_Paciente();
	}

}

void listar_Pacientes(){

	PACIENTE p;

	FILE *arquivo;

	arquivo = fopen("paciente.txt", "rb");
	char *nome = "paciente.txt", op;
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t   ++++++  MENU DO PACIENTE (PACIENTES CADASTRADOS) ++++++\n\n");

	if(arquivo != NULL){

		if(verificar_conteudo(nome) == 0){
			printf("\n\t\t\tNÃO HÁ PACIENTES CADASTRADOS\n");
		}else{

			while(fread(&p, sizeof(PACIENTE), 1, arquivo) == 1){
				printf("\t\t\t   ====================\n");
				printf("\t\t\t   NOME: %s\n", p.nome);
				printf("\t\t\t   CODIGO: %d\n", p.codigo_paciente);
				printf("\t\t\t   NASCIMENTO: %s\n", p.nascimento);
				printf("\t\t\t   CPF: %s\n", p.cpf);
				printf("\t\t\t   ENDEREÇO: %s\n", p.end);
				printf("\t\t\t   ====================\n");
				sleep(1);

			}fclose(arquivo);
		}
	}else{

		printf("\n\t\t\t   NÃO HÁ PACIENTES CADASTRADOS\n");
	}

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}

}

void remover_Pacientes(){

	FILE *arquivo, *arquivo2;
	int cod;
	PACIENTE p;

	char *nome_antigo = "paciente.txt", *nome_novo = "paciente2.txt", op;

	arquivo = fopen("paciente.txt", "rb");
	arquivo2 = fopen("paciente2.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO PACIENTE (REMORÇÃO) ++++++\n\n");

	

	if(verificar_conteudo(nome_antigo) != 0){

		printf("\n\t\tDIGITE O CODIGO DO PACIENTE A SER REMOVIDO: ");
		scanf("%d", &cod);

		if(verificar_codigo_Paciente(cod) == 0){
			printf("\n\t  TEM CERTEZA QUE DESEJA REMOVER O PACIENTE? (S - SIM, N - NÃO): ");
			scanf(" %c", &op);
			if(op == 'S'){
				while(fread(&p, sizeof(PACIENTE), 1, arquivo) == 1){
					if(cod != p.codigo_paciente){
						fwrite(&p, sizeof(PACIENTE), 1, arquivo2);
					}
				}
				printf("\n\t\t\t\tPACIENTE REMOVIDO!\n");
				remove("paciente.txt");
				rename(nome_novo, nome_antigo);
				fclose(arquivo);
				fclose(arquivo2);
			}else{
				printf("\n\t\t\t\tPACIENTE NÃO REMOVIDO!\n");
			}
		

		}else{
			printf("\n\t\t\t   ESSE PACIENTE NÃO EXISTE\n");

		}
	}else{

		printf("\n\t\t\tNÃO EXISTEM PACIENTES CADASTRADOS\n");

	}


}

void editar_Pacientes(){

	FILE *arquivo, *arquivo2;
	int cod;
	PACIENTE p;

	char *nome_antigo = "paciente.txt", *nome_novo = "paciente2.txt", op, nome[30];

	arquivo = fopen("paciente.txt", "rb");
	arquivo2 = fopen("paciente2.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO PACIENTE (EDIÇÃO) ++++++\n\n");

	

	if(verificar_conteudo(nome_antigo) != 0){

		printf("\t\t\tDIGITE O CODIGO DO PACIENTE: ");
		scanf("%d", &cod);

		if(verificar_codigo_Paciente(cod) == 0){

			while(fread(&p, sizeof(PACIENTE), 1, arquivo) == 1){
				if(cod != p.codigo_paciente){

					fwrite(&p, sizeof(PACIENTE), 1, arquivo2);

				}else if(cod == p.codigo_paciente){

					printf("\n\t\t\tVOCE ESTÁ EDITANDO O PACIENTE: %s\n", p.nome);
					printf("--------------------------------------------------------------------------------\n");

					printf("\n\t\t\tNOVO CODIGO: ");
					scanf(" %d", &cod);

					pegar_informacoes_Paciente(cod, nome);

					if(verificar_codigo_Paciente(cod) == 0 && strcmp(nome, p.nome) != 0){
						printf("\n\t\t\t   ESSE CODIGO JÁ EXISTE!\n");
						sleep(2);
						menu_Paciente();
					}else{
						p.codigo_paciente = cod;
						printf("\n\t\t\tNOVO NOME: ");
						scanf(" %[^\n]", p.nome);

						printf("\n\t\t\tNASCIMENTO: ");
						scanf(" %[^\n]", p.nascimento);

						printf("\n\t\t\tNOVO CPF: ");
						scanf(" %[^\n]", p.cpf);

						printf("\n\t\t\tNOVO ENDEREÇO: ");
						scanf(" %[^\n]", p.end);

						printf("\n\t TEM CERTEZA QUE QUER EDITAR O PACIENTE? (S - SIM, N - NÃO): ");
						scanf(" %c", &op);
						if(op == 'S'){
							printf("\n\t\t\tPACIENTE EDITADO");
							fwrite(&p, sizeof(PACIENTE), 1, arquivo2);
							remove("paciente.txt");
							rename(nome_novo, nome_antigo);
	
						}else{
							printf("\n\t\t\t  PACIENTE NÃO EDITADO!\n");
							fwrite(&p, sizeof(PACIENTE), 1, arquivo2);
						}
					}


				}
			}
		}else{
			printf("\n\t\t\t\tESSE PACIENTE NÃO EXISTE!");
		}

		
	}else{
		printf("\n\t\t\tNÃO EXISTEM PACIENTES CADASTRADOS!\n");
		return;
	}

	
fclose(arquivo2);

}





////////////////////////
//FUNÇÕES DO SUPERVISOR
////////////////////////

void menu_supervisor(){

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t\t++++++  MENU DO SUPERVISOR  ++++++\n\n");
	printf("\t1 - CADASTRAR SUPERVISORES               3 - EDITAR SUPERVISORES\n\n");
	printf("\t2 - REMOVER SUPERVISORES                 4 - LISTAR SUPERVISORES\n\n");
	printf("\t5 - SAIR\n\n");

}

void gerenciador_de_Supervisores(){

	int op;

	do{

		system("clear");
		menu_supervisor();
		printf("\n\t\t\t\tDIGITE A OPÇÃO: ");
		scanf("%d", &op);

		switch(op){
			case 1:
				system("clear");
				cadastrar_Supervisor();
				sleep(2);
				menu_supervisor();
				break;
			case 2:
				system("clear");
				remover_Supervisores();
				sleep(2);
				menu_supervisor();
				break;
			case 3:
				system("clear");
				editar_supervisores();
				sleep(2);
				menu_supervisor();
				break;
			case 4:
				system("clear");
				listar_Supervisores();
				menu_supervisor();
				break;
		}
	}while(op != 5);

}

int verificar_codigo_Supervisor(int codigo){

	FILE *arquivo;
	SUPERVISOR sup;
	arquivo = fopen("supervisores.txt", "rb");


	while(fread(&sup, sizeof(SUPERVISOR), 1, arquivo) == 1){
		if(codigo == sup.codigo_professor){
			fclose(arquivo);
			return 0;
		}

	}

	fclose(arquivo);
	return 1;

}

void pegar_informacoes_Supervisor(int codigo, char nome[]){

	FILE *arquivo;
	SUPERVISOR sup;
	arquivo = fopen("supervisores.txt", "rb");

	while(fread(&sup, sizeof(SUPERVISOR), 1, arquivo) == 1){
		if(codigo == sup.codigo_professor){
			strcpy(nome, sup.nome);
		}
	}

}

void cadastrar_Supervisor(){

	FILE *arquivo;
	SUPERVISOR sup;
	int codigo;
	char op;

	arquivo = fopen("supervisores.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO SUPERVISOR (CADASTRO) ++++++\n\n");

	srand((unsigned)time(NULL));

	codigo = 1 + rand();
	

	if(verificar_codigo_Supervisor(codigo)){

		sup.codigo_professor = codigo;

		printf("\n\t\t\tSEU CODIGO É: %d\n", sup.codigo_professor);

		printf("\n\t\t\tDIGITE O NOME DO SUPERVISOR: ");
		scanf(" %[^\n]", sup.nome);

		printf("\n\t\t\tDIGITE O CURSO DO SUPERVISOR: ");
		scanf(" %[^\n]", sup.curso);

		printf("\n\t  TEM CERTEZA QUE DESEJA CADASTRAR O SUPERVISOR? (S - SIM, N - NÃO): ");
		scanf(" %c", &op);
		if(op == 'S'){
			printf("\n\t\t\t\tSUPERVISOR CADASTRADO!\n");
			fwrite(&sup, sizeof(SUPERVISOR), 1, arquivo);
			fclose(arquivo);
		}else{
			printf("\n\t\t\t\tSUPERVISOR NÃO CADASTRADO!\n");
		}

	}else{

		printf("\n\t\t\t\tESSE CODIGO JÁ EXISTE!\n");
		sleep(2);
		cadastrar_Supervisor();

	}


}


void listar_Supervisores(){

	FILE *arquivo;
	SUPERVISOR sup;
	char op;
	arquivo = fopen("supervisores.txt", "rb");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("          ++++++  MENU DO SUPERVISOR (SUPERVISORES CADASTRADOS) ++++++\n\n");

	if(arquivo != NULL){

		if(verificar_conteudo("supervisores.txt") != 0){

			while(fread(&sup, sizeof(SUPERVISOR), 1, arquivo) == 1){
				printf("\t\t\t   ====================\n");
				printf("\t\t\t   NOME: %s\n", sup.nome);
				printf("\t\t\t   CURSO: %s\n", sup.curso);
				printf("\t\t\t   CODIGO: %d\n", sup.codigo_professor);
				printf("\t\t\t   ====================\n");
				sleep(1);
			
			}
			fclose(arquivo);
		}else{

			printf("\n\t\t\tNÃO EXISTEM SUPERVISORES CADASTRADOS!\n");

		}
	}else{
		printf("\n\t\t\tNÃO EXISTEM SUPERVISORES CADASTRADOS!\n");
	}

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}

}

void remover_Supervisores(){

	FILE *arquivo, *arquivo2;
	SUPERVISOR sup;
	int cod;
	char *nome_antigo = "supervisores.txt", *nome_novo = "supervisores2.txt", op;

	arquivo = fopen("supervisores.txt", "rb");
	arquivo2 = fopen("supervisores2.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t   ++++++  MENU DO SUPERVISOR (REMORÇÃO) ++++++\n\n");


	if(verificar_conteudo(nome_antigo) != 0){

		printf("\n\t\tDIGITE O CODIGO DO SUPERVISOR A SER REMOVIDO: ");
		scanf("%d", &cod);

		if(verificar_codigo_Supervisor(cod) == 0){

			printf("TEM CERTEZA QUE DESEJA EXCLUIR: %s (S - SIM, N - NÃO): ", sup.nome);
			scanf(" %c", &op);
			
			if(op == 'S'){
			
				while(fread(&sup, sizeof(SUPERVISOR), 1, arquivo) == 1){
					if(cod != sup.codigo_professor){
						fwrite(&sup, sizeof(SUPERVISOR), 1, arquivo2);
					}
				}
				printf("\n\t\t\t\tSUPERVISOR REMOVIDO!\n");
				remove("supervisores.txt");
				rename(nome_novo, nome_antigo);
				fclose(arquivo2);
				fclose(arquivo);
			}else{
				printf("\n\t\t\t\tSUPERVISOR NÃO REMOVIDO\n");
			}
		}else{
			printf("\n\t\t\t\tESSE SUPERVISOR NÃO EXISTE!\n");
		}
	}else{
		printf("\n\t\t\tNÃO EXISTEM SUPERVISORES CADASTRADOS!\n");

	}



}

void editar_supervisores(){

	FILE *arquivo, *arquivo2;
	SUPERVISOR sup;
	int cod;
	char *nome_antigo = "supervisores.txt", *nome_novo = "supervisores2.txt", op, nome[30];

	arquivo = fopen("supervisores.txt", "rb");
	arquivo2 = fopen("supervisores2.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO SUPERVISOR (EDIÇÃO) ++++++\n\n");
	printf("--------------------------------------------------------------------------------\n");
	

	if(verificar_conteudo(nome_antigo) != 0){

		printf("\t\tDIGITE O CODIGO DO SUPERVISOR A SER EDITADO: ");
		scanf("%d", &cod);

		if(verificar_codigo_Supervisor(cod) == 0){

			while(fread(&sup, sizeof(SUPERVISOR), 1, arquivo) == 1){
				if(cod != sup.codigo_professor){

					fwrite(&sup, sizeof(SUPERVISOR), 1, arquivo2);

				}else if(cod == sup.codigo_professor){

					printf("\n\t\tVOCE ESTÁ EDITANDO O SUPERVISOR: %s\n", sup.nome);
					printf("--------------------------------------------------------------------------------\n");

					printf("\n\t\tNOVO CODIGO: ");
					scanf("%d", &cod);
					pegar_informacoes_Supervisor(cod, nome);
					if((verificar_codigo_Supervisor(cod) == 0) && strcmp(nome, sup.nome) != 0){
						printf("\n\t\t\t   ESSE CODIGO JÁ EXISTE!\n");
						sleep(2);
						menu_supervisor();
					}else{
						sup.codigo_professor = cod;
						printf("\n\t\tNOVO NOME: ");
						scanf(" %[^\n]", sup.nome);

						printf("\n\t\tNOVO CURSO: ");
						scanf(" %[^\n]", sup.curso);

						printf("\n\t\tTEM CERTEZA QUE DESEJA EDITAR? (S - SIM, N - NÃO): ");
						scanf(" %c", &op);
						if(op == 'S'){

							fwrite(&sup, sizeof(SUPERVISOR), 1, arquivo2);
							printf("\n\n\t\t\tSUPERVISOR EDITADO!\n");
							remove("supervisores.txt");
							rename(nome_novo, nome_antigo);
						}else{
							printf("\n\t\t\tPACIENTE NÃO EDITADO!\n");
							fwrite(&sup, sizeof(SUPERVISOR), 1, arquivo2);
						}
					}

				}
			}
		}else{
			printf("\n\n\t\t\tESSE SUPERVISOR NÃO EXISTE!\n");

		}

	}else{

		printf("\n\t\t\tNÃO EXISTEM SUPERVISORES CADASTRADOS!\n");
	}

	fclose(arquivo2);

}

/////////////////////////////////
//FUNÇÕES AGENDAMENTO
/////////////////////////////////

void menu_Agendamentos(){

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("                     ++++++  MENU DE AGENDAMENTOS  ++++++\n\n");
	printf("\t1 - CADASTRAR AGENDAMENTOS               3 - LISTAR AGENDAMENTOS\n\n");
	printf("\t2 - REMOVER AGENDAMENTOS                 4 - SAIR\n\n");
	                          


}

void gerenciador_Agendamentos(){
	int op;

	do{
		system("clear");
		menu_Agendamentos();
		printf("\n\t\t\t\tDIGITE A OPÇÃO: ");
		scanf("%d", &op);
		switch(op){

			case 1:
				system("clear");
				cadastrar_Agendamentos();
				sleep(2);
				menu_Agendamentos();
				break;
			case 2:
				system("clear");
				remover_Agendamento();
				sleep(2);
				menu_Agendamentos();
				break;
			case 3:
				system("clear");
				listar_Agendamentos();
				menu_Agendamentos();
				break;

		}

	}while(op != 4);
}

int pegar_informacoes_Agendamentos(int *codigo, char data[], char servico[]){

	FILE *arquivo;
	AGENDAMENTOS agenda;
	arquivo = fopen("agendamentos.txt", "rb");


	while(fread(&agenda, sizeof(AGENDAMENTOS), 1, arquivo) == 1){
		if(*codigo == agenda.p.codigo_paciente){
			*codigo = agenda.codigo_agendamento;
			strcpy(data, agenda.data);
			strcpy(servico, agenda.area_atendimento);
			return 1;
		}
	}
	return 0;

}

int verificar_Servicos(int codigo, char servico[]){

	FILE *arquivo;
	AGENDAMENTOS agenda;
	arquivo = fopen("agendamentos.txt", "rb");

	while(fread(&agenda, sizeof(AGENDAMENTOS), 1, arquivo) == 1){
		if(codigo == agenda.p.codigo_paciente){
			if(strcmp(servico, agenda.area_atendimento) == 0){
				return 0;
			}else{
				return 1;
			}
		}
	}

}


void cadastrar_Agendamentos(){

	FILE *arquivo;
	AGENDAMENTOS agenda;

	char nome[30], area[30], op;
	int codigo;

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLÍNICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("                 ++++++  MENU DE AGENDAMENTOS (CADASTRO) ++++++\n\n");
	

	arquivo = fopen("agendamentos.txt", "a + b");

	printf("\n\t\t\tDIGITE O CODIGO DO PACIENTE: ");
	scanf("%d", &codigo);

	if(verificar_codigo_Paciente(codigo) == 0){

		pegar_informacoes_Paciente(codigo, nome);

		strcpy(agenda.p.nome, nome);
		agenda.p.codigo_paciente = codigo;

		srand((unsigned)time(NULL));

		agenda.codigo_agendamento = 100 + rand();
		printf("\n\t\t\tO CODIGO DO SEU AGENDAMENTO É: %d\n", agenda.codigo_agendamento);

		printf("\n\t\t\tDIGITE A DATA DA CONSULTA: ");
		scanf(" %[^\n]", agenda.data);

		printf("\n\t\t\tÁREA: ");
		scanf(" %[^\n]", area);

		if(verificar_conteudo("agendamentos.txt") == 0){
			strcpy(agenda.area_atendimento, area);

		}else if(verificar_Servicos(codigo, area)){
			strcpy(agenda.area_atendimento, area);

		}else{
			printf("\n\t  VOCE NÃO PODE CADASTRAR O MESMO ALUNO EM UM SERVIÇO MAIS DE UMA VEZ!\n");
			sleep(3);
			menu_Agendamentos();
		}
		printf("\n\t\t  TEM CERTEZA QUE DESEJA AGENDAR? (S - SIM, N - NÃO): ");
		scanf(" %c", &op);
		if(op == 'S'){
			fwrite(&agenda, sizeof(AGENDAMENTOS), 1, arquivo);
			printf("\n\t\t\tAGENDADO COM SUCESSO!");
			sleep(2);
		}else{
			printf("\n\t\t\t\tNÃO AGENDADO!\n");
			
		}

		

	}else{

		printf("\n\t\t\t   ESSE PACIENTE NÃO EXISTE!\n");
		sleep(2);
		gerenciador_Agendamentos();

	}

	fclose(arquivo);

}

void listar_Agendamentos(){

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t   ++++++  MENU DO AGENDAMENTOS (AGENDAMENTOS) ++++++\n\n");


	FILE *arquivo;
	AGENDAMENTOS agenda;
	arquivo = fopen("agendamentos.txt", "rb");
	char op;
	if(verificar_conteudo("agendamentos.txt") != 0){

		while(fread(&agenda, sizeof(AGENDAMENTOS), 1, arquivo) == 1){
			printf("\t\t\t   ==========================\n");
			printf("\n\t\t\t   NOME DO PACIENTE: %s\n", agenda.p.nome);
			printf("\n\t\t\t   CODIGO DO PACIENTE: %d\n", agenda.p.codigo_paciente);
			printf("\n\t\t\t   CODIGO AGENDAMENTO: %d\n", agenda.codigo_agendamento);
			printf("\n\t\t\t   AREA DO ATENDIMENTO: %s\n", agenda.area_atendimento);
			printf("\n\t\t\t   DATA DA CONSULTA: %s\n", agenda.data);
			printf("\t\t\t   ==========================\n");
			sleep(1);

		}fclose(arquivo);
		
	}else{
		printf("\n\t\t\t   NÃO EXISTEM AGENDAMENTOS!\n");
	}

	printf("\n\t\t\t   PRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}

}

int verificar_codigo_Agendamento(int codigo){

	FILE *arquivo;
	AGENDAMENTOS agenda;
	arquivo = fopen("agendamentos.txt", "rb");

	while(fread(&agenda, sizeof(AGENDAMENTOS), 1, arquivo) == 1){
		if(agenda.codigo_agendamento == codigo){
			return 0;
		}
	}

	return 1;

}

void remover_Agendamento(){

	FILE *arquivo, *arquivo2;

	arquivo = fopen("agendamentos.txt", "rb");
	arquivo2 = fopen("agen.txt", "a + b");

	char *nome_antigo = "agendamentos.txt", *nome_novo = "agen.txt", op;
	int codigo;
	AGENDAMENTOS agenda;
	PACIENTE p;

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t   ++++++  MENU DO AGENDAMENTOS (REMORÇÃO) ++++++\n\n");

	if(verificar_conteudo("agendamentos.txt") != 0){

		printf("\n\t\t\tDIGITE O CODIGO DO AGENDAMENTO: ");
		scanf("%d", &codigo);

		if(verificar_codigo_Agendamento(codigo) == 0){

			printf("\n\t\t\tAGENDAMENTO DO PACIENTE: %s\n", p.nome);
			printf("\n\tTEM CERTEZA QUE DESEJA EXCLUIR ESSE AGENDAMENTO: (S SIM, N - NÃO): ");
			scanf(" %c", &op);

			if(op == 'S'){

				while(fread(&agenda, sizeof(agenda), 1, arquivo) == 1){

					if(codigo != agenda.codigo_agendamento){
						fwrite(&agenda, sizeof(AGENDAMENTOS), 1, arquivo2);

					}

				}
				printf("\n\t\t\t   AGENDAMENTO EXCLUINDO\n");
				remove("agendamentos.txt");
				rename(nome_novo, nome_antigo);
				fclose(arquivo2);

			}else{
				printf("\n\t\t\t   AGENDAMENTO NÃO EXCLUIDO\n");
			}
		}else{
			printf("\n\t\t\t   ESSE AGENDAMENTO NÃO EXISTE\n");
		}
	}else{
		printf("\n\t\t\tNÃO EXISTEM AGENDAMENTOS\n");
	}

}

///////////////////////////
//FUNÇÕES DO ATENDIMENTO
///////////////////////////

void gerenciador_Atendimentos(){

	int op;
	

	do{

		system("clear");
		menu_Atendimentos();
		printf("\n\tDIGITE A OPÇÃO: ");
		scanf("%d", &op);

		switch(op){

			case 1:

				system("clear");
				cadastrar_Atendimentos();
				sleep(2);
				menu_Atendimentos();
				break;

			case 2:

				system("clear");
				remover_Atendimentos();
				sleep(2);
				menu_Atendimentos();
				break;

			case 3:
				system("clear");
				listar_Atendimentos();
				menu_Atendimentos();
				break;

			case 4:
				system("clear");
				listar_por_Aluno();
				menu_Atendimentos();
				break;

			case 5:
				system("clear");
				listar_por_Area();
				menu_Atendimentos();
				break;

			case 6:
				system("clear");
				listar_por_Paciente();
				menu_Atendimentos();
				break;


		}


	}while(op != 7);

}

void menu_Atendimentos(){

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t   ++++++  MENU DE ATENDIMENTOS  ++++++\n\n");
	printf("\t1 - CADASTRAR ATENDIMENTOS\t4 - LISTAR POR ALUNO\n\n");
	printf("\t2 - REMOVER ATENDIMENTOS\t5 - LISTAR ÁREA\n\n");
	printf("\t3 - LISTAR OS ATENDIMENTOS\t6 - LISTAR POR PACIENTE\n\n");
	printf("\t7 - SAIR\n\n");


}



void cadastrar_Atendimentos(){

	int matricula_aluno, codigo_paciente, codigo_supervisor, bool = 0;
	char nome_aluno[30], nome_paciente[30], data[15], servico[30], nome_supervisor[30];
	ATENDIMENTOS atende;

	FILE *arquivo;

	arquivo = fopen("atendimentos.txt", "a + b");

	srand((unsigned)time(NULL));

	atende.codigo_atendimento = 100 + rand();

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLÍNICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DE ATENDIMENTOS (CADASTRO) ++++++\n\n");
	printf("--------------------------------------------------------------------------------\n\n");

	do{

		printf("\n\t\t\tO CODIGO DO SEU ATENDIMENTO É: %d\n", atende.codigo_atendimento);

		printf("\n\t\t\tDIGITE O CODIGO DO ALUNO: ");
		scanf("%d", &matricula_aluno);

		if(verificar_matricula_Aluno(matricula_aluno) == 0){

			pegar_nome_Aluno(matricula_aluno, nome_aluno);

			atende.aluno.matricula = matricula_aluno;
			strcpy(atende.aluno.nome, nome_aluno);

		}else{

			printf("\n\t\t\tESSE ALUNO NÃO EXISTE!\n");
			break;

		}

		printf("\n\t\t\tDIGITE O CODIGO DO PACIENTE: ");
		scanf("%d", &codigo_paciente);

		if(verificar_codigo_Paciente(codigo_paciente) == 0){

			pegar_informacoes_Paciente(codigo_paciente, nome_paciente);

			strcpy(atende.p.nome, nome_paciente);

			atende.p.codigo_paciente = codigo_paciente;

		}else{

			printf("\n\t\t\tESSE PACIENTE NÃO EXISTE!\n");
			break;

		}

		if(pegar_informacoes_Agendamentos(&codigo_paciente, data, servico)){

			atende.agenda.codigo_agendamento = codigo_paciente;

			strcpy(atende.agenda.data, data);

			strcpy(atende.agenda.area_atendimento, servico);

		}else{

			printf("\n\t\t\tESSE PACIENTE NÃO ESTÁ AGENDADO!\n");
			break;
		}

		printf("\n\t\t\tDIGITE O CODIGO DO SUPERVISOR: ");
		scanf("%d", &codigo_supervisor);

		if(verificar_codigo_Supervisor(codigo_supervisor) == 0){

			pegar_informacoes_Supervisor(codigo_supervisor, nome_supervisor);

			atende.sup.codigo_professor = codigo_supervisor;

			strcpy(atende.sup.nome, nome_supervisor);

		}else{

			printf("\n\t\t\tESSE SUPERVISOR NÃO EXISTE!\n");
			break;

		}

	
		bool = 1;

	}while(bool != 1);

	if(bool == 1){
		fwrite(&atende, sizeof(ATENDIMENTOS), 1, arquivo);
		remover_P(codigo_paciente);
		printf("\n\t\t\tATENDIMENTO CADASTRADO!");
	}else{
		printf("\n\t\t\tATENDIMENTO NÃO CADASTRADO!");
	}

	fclose(arquivo);

}


int verificar_codigo_Atendimento(int codigo){

	FILE *arquivo;
	ATENDIMENTOS atende;
	arquivo = fopen("atendimentos.txt", "rb");

	while(fread(&atende, sizeof(ATENDIMENTOS), 1, arquivo) == 1){
		if(codigo == atende.codigo_atendimento){
			return 1;
		}
	}

	return 0;

}

void remover_Atendimentos(){

	FILE *arquivo, *arquivo2;
	int codigo;
	ATENDIMENTOS atende;
	char *nome_novo = "atendimento.txt", *nome_antigo = "atendimentos.txt", op;
	arquivo = fopen("atendimentos.txt", "rb");
	arquivo2 = fopen("atendimento.txt", "a + b");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t   ++++++  MENU DO ATENDIMENTOS (REMORÇÃO) ++++++\n\n");

	if(verificar_conteudo("atendimentos.txt") != 0){

		printf("\n\t\t\tDIGITE O CODIGO DO ATENDIMENTO: ");
		scanf("%d", &codigo);

		if(verificar_codigo_Atendimento(codigo)){

			printf("\n\t TEM CERTEZA QUE DESEJA EXCLUIR ESSE ATENDIMENTO? (S - SIM, N - NÃO): ");
			scanf(" %c", &op);
			if(op == 'S'){
				while(fread(&atende, sizeof(ATENDIMENTOS), 1, arquivo) == 1){
					if(codigo != atende.codigo_atendimento){
						fwrite(&atende, sizeof(ATENDIMENTOS), 1, arquivo2);
					}
				}
				printf("\n\t\t\t   ATENDIMENTO EXCLUIDO!\n");
				remove("atendimentos.txt");
				rename(nome_novo, nome_antigo);
				fclose(arquivo2);
			
			}else{
				printf("\n\t\t\tATENDIMENTO NÃO EXCLUIDO!\n");
			}
		}else{
			printf("\n\t\t\tESSE ATENDIMENTO NÃO EXISTE\n");
		}

	}else{
		printf("\n\t\t\tNÃO EXISTEM ATENDIMENTOS CADASTRADOS\n");
	}

}

void remover_P(int codigo){

	FILE *arquivo, *arquivo2;

	arquivo = fopen("agendamentos.txt", "rb");
	arquivo2 = fopen("agen.txt", "a + b");

	char *nome_antigo = "agendamentos.txt", *nome_novo = "agen.txt";
	AGENDAMENTOS agenda;

	while(fread(&agenda, sizeof(agenda), 1, arquivo) == 1){

		if(codigo != agenda.codigo_agendamento){
			fwrite(&agenda, sizeof(AGENDAMENTOS), 1, arquivo2);

		}

	}
	remove("agendamentos.txt");
	rename(nome_novo, nome_antigo);
	fclose(arquivo);
	fclose(arquivo2);

}
	


void listar_Atendimentos(){

	FILE *arquivo;	
	ATENDIMENTOS atende;
	char prox;
	arquivo = fopen("atendimentos.txt", "rb");

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t\t++++++  MENU DO ATENDIMENTOS (ATENDIMENTOS) ++++++\n\n");

	if(verificar_conteudo("atendimentos.txt") != 0){
		while(fread(&atende, sizeof(ATENDIMENTOS), 1, arquivo) == 1){
			printf("\t\t==========================================\n");
			printf("\t\tCODIGO DO ATENDIMENTO: %d\n", atende.codigo_atendimento);
			printf("\t\tSERVIÇO PRESTADO: %s\n", atende.agenda.area_atendimento);
			printf("\t\tCODIGO DO AGENDAMENTO: %d\n", atende.agenda.codigo_agendamento);
			printf("\t\tDATA DO AGENDAMENTO: %s\n", atende.agenda.data);
			printf("\t\tNOME DO PACIENTE: %s\n", atende.p.nome);
			printf("\t\tCODIGO DO PACIENTE: %d\n", atende.p.codigo_paciente);
			printf("\t\tNOME DO ALUNO: %s\n", atende.aluno.nome);
			printf("\t\tMATRICULA DO ALUNO: %d\n", atende.aluno.matricula);
			printf("\t\tNOME DO SUPERVISOR: %s\n", atende.sup.nome);
			printf("\t\tCODIGO DO SUPERVISOR: %d\n", atende.sup.codigo_professor);
			printf("\n\t\t==========================================\n");
						
		}
		
	}else{
		printf("\n\t\t\tNÃO EXISTEM ATENDIMENTOS AGENDADOS!\n");

	}	

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &prox);
	if(prox == 'c'){
		return;
	}

}
void listar_por_Area(){

	FILE *arquivo;
	ATENDIMENTOS atende;
	char area[30], op;
	arquivo = fopen("atendimentos.txt", "rb");
	int cont = 0;
	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t++++++  MENU DO ATENDIMENTOS (ATENDIMENTOS POR ÁREA) ++++++\n\n");

	if(verificar_conteudo("atendimentos.txt") != 0){

		printf("\n\t\tDIGITE A ÁREA DO ATENDIMENTO: ");
		scanf(" %[^\n]", area);

		while(fread(&atende, sizeof(ATENDIMENTOS), 1, arquivo) == 1){
			if(strstr(atende.agenda.area_atendimento, area)){
				printf("\n\t\t\tTIPO DE SERVIÇO: %s\n", area);
				printf("\t\t\tDADOS DO ATENDIMENTO:\n");
				printf("\t\t\t=====================================\n");
				printf("\t\t\tCODIGO DO ATENDIMENTO: %d\n", atende.codigo_atendimento);
				printf("\t\t\tCODIGO DO AGENDAMENTO: %d\n", atende.agenda.codigo_agendamento);
				printf("\t\t\tDATA DO AGENDAMENTO: %s\n", atende.agenda.data);
				printf("\t\t\tNOME DO PACIENTE: %s\n", atende.p.nome);
				printf("\t\t\tCODIGO DO PACIENTE: %d\n", atende.p.codigo_paciente);
				printf("\t\t\tNOME DO ALUNO: %s\n", atende.aluno.nome);
				printf("\t\t\tMATRICULA DO ALUNO: %d\n", atende.aluno.matricula);
				printf("\t\t\tNOME DO SUPERVISOR: %s\n", atende.sup.nome);
				printf("\t\t\tCODIGO DO SUPERVISOR: %d\n", atende.sup.codigo_professor);
				cont++;
			
			}
			
		}if(cont == 0){
			printf("\n\t\t  NÃO EXISTEM ATENDIMENTOS PARA ESSA ÁREA!\n");
		}
	}else{
		printf("\n\t\tNÃO EXISTEM ATENDIMENTOS AGENDADOS!\n");
		return;
	}
	

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}


}

void listar_por_Aluno(){

	ATENDIMENTOS atende;
	FILE *arquivo;
	arquivo = fopen("atendimentos.txt", "rb");
	char nome[30], op;
	int matricula;

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t++++++  MENU DO ATENDIMENTOS (ATENDIMENTOS POR ALUNO) ++++++\n\n");
	
	if(verificar_conteudo("atendimentos.txt") != 0){


		printf("\t\t\tDIGITE O NOME DO ALUNO: "); 
		scanf(" %[^\n]", nome);

		while(fread(&atende, sizeof(ATENDIMENTOS), 1, arquivo) == 1){
			if(strstr(atende.aluno.nome, nome)){
				printf("\t\t\t================================\n");
				printf("\t\t\tATENDIMENTOS DO ALUNO: %s\n", atende.aluno.nome);
				printf("\t\t\tMATRICULA DO ALUNO: %d\n", atende.aluno.matricula);
				printf("\t\t\tDADOS DO ATENDIMENTO:\n");
				printf("\t\t\t=====================================\n");
				printf("\t\t\tAREA DO ATENDIMENTO: %s\n", atende.agenda.area_atendimento);
				printf("\t\t\tCODIGO DO ATENDIMENTO: %d\n", atende.codigo_atendimento);
				printf("\t\t\tCODIGO DO AGENDAMENTO: %d\n", atende.agenda.codigo_agendamento);
				printf("\t\t\tNOME DO SUPERVISOR: %s\n", atende.sup.nome);
				printf("\t\t\tCODIGO DO SUPERVISOR: %d\n", atende.sup.codigo_professor);
				printf("\t\t\tNOME DO PACIENTE: %s\n", atende.p.nome);
				printf("\t\t\tCODIGO DO PACIENTE: %d\n", atende.p.codigo_paciente);
				printf("\n");
					

			}else{
				printf("\n\t\t\tNÃO EXISTEM ATENDIMENTOS PARA ESSE ALUNO\n");
			}
		}
	}else{

		printf("\n\t\t\tNÃO EXISTEM ATENDIMENTOS\n\n");
	}

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}
}
	

void listar_por_Paciente(){

	int codigo;

	ATENDIMENTOS atende;
	FILE *arquivo;
	arquivo = fopen("atendimentos.txt", "rb");

	char nome[30], op;

	system("clear");
	printf("\n\n================================================================================\n");
	printf(".....................:::::::::::CLINICA UEPB:::::::::::::.......................\n");
	printf("================================================================================\n\n");
	printf("\t++++++  MENU DO ATENDIMENTOS (ATENDIMENTOS POR PACIENTE) ++++++\n\n");


	if(verificar_conteudo("atendimentos.txt") != 0){
	
		printf("\n\t\t\tDIGITE O NOME DO PACIENTE: "); 
		scanf(" %[^\n]", nome);

		while(fread(&atende, sizeof(ATENDIMENTOS), 1, arquivo) == 1){
			if(strstr(atende.p.nome, nome)){
				printf("\t\t\t=====================================\n");
				printf("\t\t\tCONSULTAS DO PACIENTE %s\n", atende.p.nome);
				printf("\t\t\tDADOS DA CONSULTA: \n");
				printf("\t\t\t=====================================\n");
				printf("\t\t\tAREA DO ATENDIMENTO: %s\n", atende.agenda.area_atendimento);
				printf("\t\t\tCODIGO DO ATENDIMENTO: %d\n", atende.codigo_atendimento);
				printf("\t\t\tCODIGO DO AGENDAMENTO: %d\n", atende.agenda.codigo_agendamento);
				printf("\t\t\tNOME DO SUPERVISOR: %s\n", atende.sup.nome);
				printf("\t\t\tCODIGO DO SUPERVISOR: %d\n", atende.sup.codigo_professor);
				printf("\t\t\tNOME DO ALUNO: %s\n", atende.aluno.nome);
				printf("\t\t\tMATRICULA DO ALUNO: %d\n", atende.aluno.matricula);
				printf("\n");
				
			}else{
				printf("\n\t\t\tNÃO EXISTEM ATENDIMENTOS MARCADOS PARA ESSE PACIENTE\n");
			}
		}
	}else{
		printf("\n\t\t\tNÃO EXISTEM ATENDIMENTOS\n");
	}

	printf("\n\t\t\tPRESSIONE c PARA CONTINUAR... ");
	scanf(" %c", &op);
	if(op == 'c'){
		return;
	}
}

	





