# 📚 Sistema de Gerenciamento de Biblioteca

Este projeto é um sistema de gerenciamento de biblioteca desenvolvido em linguagem C. Ele permite o cadastro de livros, listagem do acervo e controle de empréstimos para usuários, utilizando conceitos avançados de programação estruturada e gerenciamento de memória.

## 🚀 Funcionalidades


https://github.com/user-attachments/assets/3637aa04-eb78-4543-acfd-1f134ee0d448


O sistema oferece as seguintes opções através de um menu interativo:

1.  **Cadastrar Livro:** Registra novos livros com título, autor, editora e edição.
2.  **Listar Livros:** Exibe todo o acervo cadastrado e o status de disponibilidade (Disponível/Emprestado).
3.  **Realizar Empréstimo:** Permite vincular um livro disponível a um usuário específico.
4.  **Listar Empréstimos:** Mostra o histórico de todos os empréstimos ativos (Livro + Usuário).

## 🛠️ Tecnologias e Conceitos Utilizados

Este projeto foi construído para aplicar conceitos fundamentais e avançados da linguagem C:

* **Structs (Estruturas):** Modelagem de dados complexos (`Livro` e `Emprestimo`).
* **Ponteiros:** Manipulação direta de memória e passagem de dados por referência para funções.
* **Alocação Dinâmica (`malloc` / `calloc`):** O tamanho da biblioteca e dos registros de empréstimos é definido em tempo de execução, otimizando o uso da RAM.
* **Modularização:** Código organizado em funções específicas (`cadastrar`, `listar`, `emprestar`) para melhor legibilidade e manutenção.
* **Manipulação de Strings:** Uso seguro de `fgets` e `strcspn` para leitura de texto e tratamento de buffers.

## 📋 Estrutura de Dados

O projeto baseia-se em duas estruturas principais:

### Struct Livro
Armazena os dados bibliográficos e o status do item.
```c
struct Livro {
    char nome[50];
    char autor[50];
    char editora[50];
    int edicao;
    int disponivel; // 1 para Disponível, 0 para Emprestado
};
```

### Struct Emprestimo
Relaciona um usuário a um livro através do índice do vetor.
```c 
struct Emprestimo {
    int indiceLivro; // Aponta para a posição do livro no array
    char nomeUsuario[50];
};
```
----
### ⚙️ Como Compilar e Executar

#### Pré-requisitos
Você precisa de um compilador C instalado (como GCC ou MinGW).
#### Passos

1. Clone este repositório ou baixe os arquivos.
2. Abra o terminal na pasta do projeto.
3. Compile o código com o comando:
```Bash 
gcc main.c -o biblioteca
```
4. Execute o programa:
   * **Windows:** `biblioteca.exe`
   * **Linux/Mac:** `./biblioteca`

----

### 🛡️ Tratamento de Erros e Segurança

  • **Verificação de Memória:** O sistema verifica se a alocação dinâmica (``calloc``/``malloc``) foi bem-sucedida antes de iniciar.

  • **Limpeza de Buffer:** Implementação de função para limpar o buffer do teclado, evitando erros de leitura em menus.

  • **Validação de Índices:** Verifica se o livro escolhido para empréstimo existe e se está disponível antes de concluir a operação.


### author

Desenvolvido por João Paulo Melo Amorim como parte da disciplina de Estruturas de Dados.

---
*Projeto desenvolvido para fins educacionais.*
