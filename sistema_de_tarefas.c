#include <stdio.h>
#include <string.h>
#define MAX_TAREFAS 100

typedef struct {
int id;
char descricao[100];
int prioridade;
int tempoEstimado;
} Tarefa;

typedef struct {
Tarefa itens[MAX_TAREFAS];
int inicio;
int fim;
int tamanho;
} Fila;


typedef struct {
Tarefa itens[MAX_TAREFAS];
int topo;
} Pilha;

Tarefa tarefas[MAX_TAREFAS];
int totalTarefas = 0;


void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
return f->tamanho == 0;
}

int filaCheia(Fila *f) {
return f->tamanho == MAX_TAREFAS;
}

void inserirFila(Fila *f, Tarefa t) {
 if (filaCheia(f)) {
  printf("\nFila cheia !!!!");
    return;
    }

f->fim = (f->fim + 1) % MAX_TAREFAS;
f->itens[f->fim] = t;
f->tamanho++;

printf("\nTarefa adicionada a fila !!!!");
}

Tarefa removerFila(Fila *f, int *sucesso) {
 Tarefa vazia = {0, "", 0, 0};

if (filaVazia(f)) {
 printf("\nA fila esta vazia !!!");
 *sucesso = 0;
     return vazia;
    }

Tarefa t = f->itens[f->inicio];

f->inicio = (f->inicio + 1) % MAX_TAREFAS;
f->tamanho--;

*sucesso = 1;

return t;
}




void inicializarPilha(Pilha *p) {
p->topo = -1;
}

int pilhaVazia(Pilha *p) {
return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
return p->topo == MAX_TAREFAS - 1;
}

void pushPilha(Pilha *p, Tarefa t) {
if (pilhaCheia(p)) {
 printf("\nPilha cheia!");
    return;
    }
p->topo++;
p->itens[p->topo] = t;
}

Tarefa popPilha(Pilha *p, int *sucesso) {
 Tarefa vazia = {0, " ", 0, 0};

if (pilhaVazia(p)) {
 *sucesso = 0;
  return vazia;
    }
*sucesso = 1;
Tarefa t = p->itens[p->topo];
p->topo--;

return t;
}



//CADASTRO 



void cadastrarTarefa() {
 if (totalTarefas >= MAX_TAREFAS) {
  printf("\nLimite de tarefa !!!");
   return;
    }
Tarefa t;
t.id = totalTarefas + 1;
printf("\n------------- CADASTRO DE TAREFA -------------------");

printf("Descricao: ");
getchar();
fgets(t.descricao, sizeof(t.descricao), stdin);

t.descricao[strcspn(t.descricao, "\n")] = '\0';

 do{
 printf("Prioridade de (1 a 10): ");
 scanf("%d", &t.prioridade);

 if (t.prioridade < 1 || t.prioridade > 10) {
   printf("Digite uma prioridade entre 1 a 10  \n");
}

}while (t.prioridade < 1 || t.prioridade > 10);
do{
 printf("Tempo estimado em minutos: ");
 scanf("%d", &t.tempoEstimado);
if (t.tempoEstimado <= 0) {
 printf("O tempo deve ser maior que zero.\n");
    }
}while (t.tempoEstimado <= 0);
    tarefas[totalTarefas] = t;
    totalTarefas++;

    printf("\nTarefa cadastrada !!");
}


void listarTarefas() {
 if (totalTarefas == 0) {
  printf("\nNenhuma tarefa cadastrada !!!");
 return;
    }

printf("\n*************** TAREFAS *************");

for (int i = 0; i < totalTarefas; i++) {
 printf("\nID : %d\n", tarefas[i].id);
 printf("Descricao : %s\n", tarefas[i].descricao);
 printf("Prioridade :  %d\n", tarefas[i].prioridade);
 printf("Tempo estimado : %d minutos\n", tarefas[i].tempoEstimado);
    }
}



// busca



int buscarTarefaPorId(int id, Tarefa *resultado) {
 for (int i = 0; i < totalTarefas; i++) {
if (tarefas[i].id == id) {
 *resultado = tarefas[i];
    return 1;
 }
}
return 0;
 }

void ordenarBubbleSort(int criterio) {  
 Tarefa temp;

 for (int i = 0; i < totalTarefas - 1; i++) {

  for (int j = 0; j < totalTarefas - i - 1; j++) {

 int trocar = 0;

if (criterio == 1) {
 if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
    trocar = 1;
}

}else if (criterio == 2) {
    if (tarefas[j].tempoEstimado >
  tarefas[j + 1].tempoEstimado) {
   trocar = 1;
 }
}

if (trocar) {
 temp = tarefas[j];
tarefas[j] = tarefas[j + 1];
tarefas[j + 1] = temp;
    }
  }
 }
}





// menu

int main() {
Fila fila;
Pilha pilha;
inicializarFila(&fila);
inicializarPilha(&pilha);
int opcao;

do{
printf("\n***************************************\n");
printf("   SISTEMA DE GERENCIAMENTO DE TAREFAS   \n");
printf("*****************************************\n\n");
printf("1-Cadastrar tarefa\n");
printf("2-Listar tarefas\n");
printf("3-Ordenar tarefas\n");
printf("4-Adicionar tarefa fila\n");
printf("5-Executar tarefa da fila\n");
printf("6-Mostrar historico\n");
printf("0-Sair\n");
printf("Escolha uma opcao: ");
 scanf("%d", &opcao);
  
  switch (opcao) {
case 1:
 cadastrarTarefa();
    break;

case 2:
 listarTarefas();
  break;

 case 3: {
if (totalTarefas == 0) {
printf("\nNenhuma tarefa cadastrada !!!");
break;
}

int criterio;
printf("\n1 - Ordenar por prioridade");
printf("2 - Ordenar por tempo \n");
printf("Escolha : ");
 scanf("%d", &criterio);
 if (criterio == 1 || criterio == 2) {
ordenarBubbleSort(criterio);
printf("\nTarefa ordenada !!!!");

}else {
printf("\nOpcao invalida !!");
}
break;
  }
case 4: {
 if (totalTarefas == 0) {
printf("\nNenhuma tarefa cadastrada.");
break;
 }

listarTarefas();
int id;
Tarefa tarefa;

printf("\nDigite o ID da tarefa: ");
  scanf("%d", &id);

if (buscarTarefaPorId(id, &tarefa)) {
 inserirFila(&fila, tarefa);
 } else{
printf("\nTarefa nao encontrada!!!!\n");
   }
break;
    }

case 5:{
 int sucesso;
 Tarefa tarefa = removerFila(&fila, &sucesso);

if (sucesso){

 pushPilha(&pilha, tarefa);

  printf("\nTarefa executada com sucesso !!!!\n");
  printf("ID: %d\n", tarefa.id);
  printf("Descricao: %s\n", tarefa.descricao);
}
break;
  }
case 6: {
 if (pilhaVazia(&pilha)) {
  printf("\nNenhuma tarefa foi concluida ainda.\n");
 break;
}

printf("******** HISTORICO *******");

 for (int i = pilha.topo; i >= 0; i--) {
printf("\nID: %d\n", pilha.itens[i].id);
printf("Descricao: %s\n", pilha.itens[i].descricao);
printf("Prioridade: %d\n", pilha.itens[i].prioridade);
printf("Tempo: %d  minutos",
 
 pilha.itens[i].tempoEstimado);
   }
break;
 }

case 0:
 printf("\n Programa foi  encerrado !!.");
break;

default:
 printf("\n ERrror! ");
 }
 
}while (opcao != 0);
return 0;
}

