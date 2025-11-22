#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 50

// --- Definição da Estrutura (Struct) ---

struct Livro
{
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;
};

struct Emprestimo
{
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

// --- Protótipos das Funções ---
// Declarar as funções aqui permite que a "main" as utilize antes de suas definições.
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca, struct Emprestimo *emprestimos, int *totalEmprestimos, int totalLivros);
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);

// --- Função Principal (main) ---
int main()
{
    struct Livro *biblioteca = (struct Livro *)calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1; // Sai do programa com código de erro.
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do
    {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:
            cadastrarLivro(biblioteca, &totalLivros);
            break;

        case 2:
            listarLivros(biblioteca, totalLivros);
            break;

        case 3:
            realizarEmprestimo(biblioteca, emprestimos, &totalEmprestimos, totalLivros);
            break;

        case 4:
            listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
            break;

        case 0:
            printf("\nSaindo do programa...\n");
            break;

        default:
            printf("\nOpcao invalida! Pressione Enter para tentar novamente.\n");
            getchar();
            break;
        }
    } while (opcao != 0);

    // Chama a função para liberar a memória alocada
    liberarMemoria(biblioteca, emprestimos);
    return 0;
}

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void exibirMenu()
{
    printf("\n--- Menu de Biblioteca ---\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Realizar Emprestimo\n");
    printf("4. Listar Emprestimos\n");
    printf("0. Sair\n");
    printf("***************************\n");
    printf("Escolha uma opcao: ");
}

/**
 * @brief Cadastra um novo livro na biblioteca.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Ponteiro para o contador de livros cadastrados.
 */

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros)
{
    printf("\n--- Cadastrar Livro ---\n");

    if (*totalLivros < MAX_LIVROS)
    {
        int indice = *totalLivros; // Usa o valor atual de totalLivros como índice

        printf("Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);
        printf("Digite o autor do livro: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);
        printf("Digite a editora do livro: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);

        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = 0;
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = 0;
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = 0;

        printf("Digite a edicao do livro: ");
        scanf("%d", &biblioteca[indice].edicao);
        limparBufferEntrada();

        biblioteca[indice].disponivel = 1;
        (*totalLivros)++;
        printf("\nLivro cadastrado com sucesso!\n");
    }
    else
    {
        printf("\nCapacidade maxima de livros atingida!\n");
    }
    printf("Pressione Enter para continuar...\n");
    getchar();
}

/**
 * @brief Libera a memória alocada para os arrays de livros e empréstimos.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Número total de livros cadastrados.
 */

void listarLivros(const struct Livro *biblioteca, int totalLivros)
{
    printf("\nLista de Livros Cadastrados...\n\n");
    if (totalLivros == 0)
    {
        printf("Nenhum livro cadastrado na biblioteca.\n");
    }
    else
    {
        for (int i = 0; i < totalLivros; i++)
        {
            printf("Livro %d:\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Disponivel: %s\n\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
        }
        printf("***************************\n");
    }
    printf("Pressione Enter para continuar...\n");
    getchar();
}

/**
 * @brief Realiza o empréstimo de um livro.
 * @param biblioteca Ponteiro para o array de livros.
 * @param totalLivros Número total de livros cadastrados.
 * @param emprestimos Ponteiro para o array de empréstimos.
 * @param totalEmprestimos Ponteiro para o contador de empréstimos realizados.
 */
void realizarEmprestimo(struct Livro *biblioteca, struct Emprestimo *emprestimos, int *totalEmprestimos, int totalLivros)
{
    printf("\n--- Realizar Emprestimo ---\n");

    if (*totalEmprestimos >= MAX_EMPRESTIMOS)
    {
        printf("Capacidade maxima de emprestimos atingida!\n");
    }
    else
    {
        printf("Livros disponiveis:\n");
        int disponiveis = 0;
        for (int i = 0; i < totalLivros; i++)
        {
            if (biblioteca[i].disponivel)
            {
                printf("%d. %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;
            }
        }

        if (disponiveis == 0)
        {
            printf("Nenhum livro disponivel para emprestimo.\n");
        }
        else
        {
            printf("\nDigite o numero do livro que deseja emprestar: ");
            int numLivro;
            scanf("%d", &numLivro);
            limparBufferEntrada();

            int indice = numLivro - 1;
            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel)
            {
                printf("Digite seu nome: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = 0;

                emprestimos[*totalEmprestimos].indiceLivro = indice;
                biblioteca[indice].disponivel = 0;

                (*totalEmprestimos)++;
                printf("\nEmprestimo realizado com sucesso!\n");
            }
            else
            {
                printf("\nOpcao invalida ou livro indisponivel!\n");
            }
        }
    }
    printf("Pressione Enter para continuar...\n");
    getchar();
}

/**
 * @brief Lista todos os empréstimos realizados.
 * @param biblioteca Ponteiro para o array de livros.
 * @param emprestimos Ponteiro para o array de empréstimos.
 * @param totalEmprestimos Número total de empréstimos realizados.
 */

void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos)
{
    printf(" Lista de Emprestimos...\n");
    if (totalEmprestimos == 0)
    {
        printf("Nenhum emprestimo realizado.\n");
    }
    else
    {
        for (int i = 0; i < totalEmprestimos; i++)
        {
            int indiceLivro = emprestimos[i].indiceLivro;
            printf("Emprestimo %d:\n", i + 1);
            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
            printf("Usuario: %s\n\n", emprestimos[i].nomeUsuario);
        }
        printf("***************************\n");
    }
    printf("Pressione Enter para continuar...\n");
    getchar();
}

/**
 * @brief Libera a memória alocada para os arrays dinâmicos.
 */

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos)
{
    free(biblioteca);
    free(emprestimos);
    printf("\nMemoria liberada com sucesso!\n");
}
