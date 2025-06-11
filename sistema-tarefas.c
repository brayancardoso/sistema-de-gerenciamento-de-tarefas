#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 100
#define MAX_CARACTERES 50

void cadastrarTarefa(char tarefas[][4][MAX_CARACTERES], int *quantidade) {
    if (*quantidade >= MAX_TAREFAS) {
        printf("\nLimite máximo de tarefas atingido.\n");
        return;
    }
    printf("\nCadastro de Tarefa:\n");
    printf("Título: ");
    fgets(tarefas[*quantidade][0], MAX_CARACTERES, stdin);
    tarefas[*quantidade][0][strcspn(tarefas[*quantidade][0], "\n")] = '\0';

    printf("Descrição: ");
    fgets(tarefas[*quantidade][1], MAX_CARACTERES, stdin);
    tarefas[*quantidade][1][strcspn(tarefas[*quantidade][1], "\n")] = '\0';

    printf("Prioridade (Alta, Média, Baixa): ");
    fgets(tarefas[*quantidade][2], MAX_CARACTERES, stdin);
    tarefas[*quantidade][2][strcspn(tarefas[*quantidade][2], "\n")] = '\0';

    printf("Status (Pendente, Em andamento, Concluído): ");
    fgets(tarefas[*quantidade][3], MAX_CARACTERES, stdin);
    tarefas[*quantidade][3][strcspn(tarefas[*quantidade][3], "\n")] = '\0';

    (*quantidade)++;
    printf("Tarefa cadastrada com sucesso!\n");
}

void listarTarefas(char tarefas[][4][MAX_CARACTERES], int quantidade) {
    printf("\n=== Lista de Tarefas ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s - %s - Prioridade: %s - Status: %s\n", i + 1,
            tarefas[i][0], tarefas[i][1], tarefas[i][2], tarefas[i][3]);
    }
}

void editarTarefa(char tarefas[][4][MAX_CARACTERES], int indice) {
    printf("\nEditando Tarefa %d\n", indice + 1);
    printf("Novo Título: ");
    fgets(tarefas[indice][0], MAX_CARACTERES, stdin);
    tarefas[indice][0][strcspn(tarefas[indice][0], "\n")] = '\0';

    printf("Nova Descrição: ");
    fgets(tarefas[indice][1], MAX_CARACTERES, stdin);
    tarefas[indice][1][strcspn(tarefas[indice][1], "\n")] = '\0';

    printf("Nova Prioridade: ");
    fgets(tarefas[indice][2], MAX_CARACTERES, stdin);
    tarefas[indice][2][strcspn(tarefas[indice][2], "\n")] = '\0';

    printf("Novo Status: ");
    fgets(tarefas[indice][3], MAX_CARACTERES, stdin);
    tarefas[indice][3][strcspn(tarefas[indice][3], "\n")] = '\0';

    printf("Tarefa editada com sucesso!\n");
}

void excluirTarefa(char tarefas[][4][MAX_CARACTERES], int *quantidade, int indice) {
    for (int i = indice; i < *quantidade - 1; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(tarefas[i][j], tarefas[i + 1][j]);
        }
    }
    (*quantidade)--;
    printf("Tarefa excluída com sucesso!\n");
}

void salvarTarefasEmArquivo(char tarefas[][4][MAX_CARACTERES], int quantidade) {
    FILE *arquivo = fopen("tarefas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "Tarefa %d: %s - %s - Prioridade: %s - Status: %s\n",
                i + 1, tarefas[i][0], tarefas[i][1], tarefas[i][2], tarefas[i][3]);
    }
    fclose(arquivo);
    printf("Tarefas salvas com sucesso no arquivo tarefas.txt!\n");
}

int main() {
    char tarefas[MAX_TAREFAS][4][MAX_CARACTERES];
    int quantidade = 0;
    int opcao;

    do {
        printf("\n=== Sistema de Gerenciamento de Tarefas ===\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Editar Tarefa\n");
        printf("4. Excluir Tarefa\n");
        printf("5. Salvar Tarefas em Arquivo\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do teclado

        switch (opcao) {
            case 1:
                cadastrarTarefa(tarefas, &quantidade);
                break;
            case 2:
                listarTarefas(tarefas, quantidade);
                break;
            case 3:
                printf("Digite o número da tarefa para editar: ");
                int ed;
                scanf("%d", &ed);
                getchar();
                if (ed >= 1 && ed <= quantidade)
                    editarTarefa(tarefas, ed - 1);
                else
                    printf("Índice inválido.\n");
                break;
            case 4:
                printf("Digite o número da tarefa para excluir: ");
                int ex;
                scanf("%d", &ex);
                getchar();
                if (ex >= 1 && ex <= quantidade)
                    excluirTarefa(tarefas, &quantidade, ex - 1);
                else
                    printf("Índice inválido.\n");
                break;
            case 5:
                salvarTarefasEmArquivo(tarefas, quantidade);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 6);

    return 0;
}
