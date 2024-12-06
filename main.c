#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_CLIENTES 20000000

// Estrutura que representa um cliente
typedef struct {
    int id;
    char nome[50];
    int idade;
} Cliente;

// Array de clientes
Cliente clientes[MAX_CLIENTES];

// Vari�vel para rastrear o n�mero de clientes
int num_clientes = 0;

// Fun��o para verificar se o ID j� existe
int verificar_cliente_existente(int id) {
     double  start_time1,start_time2,end_time1,end_time2;
     int encontrado=0;
     printf("versao sequencial\n");
     start_time1 = omp_get_wtime();
     for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id == id) {
             encontrado = 1; // Cliente encontrado // ID j� existe
        }
    }
 end_time1 = omp_get_wtime();
   encontrado=0;




    printf("versao Paralela:\n");
    start_time2 = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id == id) {
             encontrado = 1; // Cliente encontrado // ID j� existe
        }
    }

    end_time2 = omp_get_wtime();


    printf("tempo Paralela: %f \n",end_time2-start_time2);
    printf("tempo Sequencial: %f \n",end_time1-start_time1);

    return encontrado; // ID n�o existe
}

// Fun��o para criar um cliente
void criar_cliente() {
    if (num_clientes < MAX_CLIENTES) {
        Cliente novo_cliente;
        printf("Digite o ID do cliente: ");
        scanf("%d", &novo_cliente.id);

        // Verifica se o ID j� existe
        if (verificar_cliente_existente(novo_cliente.id)) {
            printf("Erro: Cliente com ID %d j� existe.\n", novo_cliente.id);
            return;
        }

        printf("Digite o nome do cliente: ");
        getchar();  // Para consumir o caractere de nova linha (\n) ap�s a leitura do ID
        fgets(novo_cliente.nome, sizeof(novo_cliente.nome), stdin);
        novo_cliente.nome[strcspn(novo_cliente.nome, "\n")] = 0;  // Remover a nova linha extra
        printf("Digite a idade do cliente: ");
        scanf("%d", &novo_cliente.idade);

        for(int i=0;i<20000000;i++){
        clientes[num_clientes] = novo_cliente;
        num_clientes++;
        }

        printf("Cliente criado com sucesso!\n");
    } else {
        printf("Erro: n�o � poss�vel adicionar mais clientes.\n");
    }
}

// Fun��o para ler todos os clientes com programa��o paralela
void ler_clientes() {
    double  start_time1,start_time2,end_time1,end_time2;
    if (num_clientes == 0) {
        printf("Nenhum cliente encontrado.\n");
        return;
    }

    printf("Lista de Clientes:\n");


     printf("versao sequencial\n");
    start_time1 = omp_get_wtime();
     for (int i = 0; i < num_clientes; i++) {
        printf("ID: %d, Nome: %s, Idade: %d\n", clientes[i].id, clientes[i].nome, clientes[i].idade);
        clientes[i].id = i+1;
    }
    end_time1 = omp_get_wtime();


printf("---------------------------------------:\n");
    printf("versao Paralela:\n");
    start_time2 = omp_get_wtime();
    // Paralelizando a exibi��o dos dados dos clientes
    #pragma omp parallel for
    for (int i = 0; i < num_clientes; i++) {
        printf("num-thead: %d, ID: %d, Nome: %s, Idade: %d\n",omp_get_thread_num(), clientes[i].id, clientes[i].nome, clientes[i].idade);
        clientes[i].id = i+1;
    }
    end_time2 = omp_get_wtime();





    printf("tempo Paralela: %f \n",end_time2-start_time2);
    printf("tempo Sequencial: %f \n",end_time1-start_time1);

}

// Fun��o para visualizar as informa��es de um cliente espec�fico
void visualizar_cliente() {
     double  start_time1,start_time2,end_time1,end_time2;
    int id;
    printf("Digite o ID do cliente a ser visualizado: ");
    scanf("%d", &id);
 int encontrado = 0;

     printf("versao sequencial\n");
    start_time1 = omp_get_wtime();
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id == id) {
            encontrado = 1; // Cliente encontrado
            printf("Informa��es do Cliente:\n");
            printf("ID: %d\n", clientes[i].id);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Idade: %d\n", clientes[i].idade);

        }
    }
     end_time1 = omp_get_wtime();

   encontrado = 0;
printf("---------------------------------------:\n");
    printf("versao Paralela:\n");
    start_time2 = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id == id) {
            encontrado = 1; // Cliente encontrado
            printf("Informa��es do Cliente:\n");
            printf("ID: %d\n", clientes[i].id);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Idade: %d\n", clientes[i].idade);

        }
    }
    end_time2 = omp_get_wtime();
    printf("tempo Paralela: %f \n",end_time2-start_time2);
    printf("tempo Sequencial: %f \n",end_time1-start_time1);

    if (!encontrado) {
        printf("Erro: Cliente com ID %d n�o encontrado.\n", id);
    }
}

// Fun��o para atualizar um cliente pelo ID
void atualizar_cliente() {
     double  start_time1,start_time2,end_time1,end_time2;
    int id;
    printf("Digite o ID do cliente a ser atualizado: ");
    scanf("%d", &id);
     int encontrado = 0;
    printf("versao sequencial\n");
    start_time1 = omp_get_wtime();
    for (int i = 0; i < num_clientes; i++) {
        printf("num_thead %d",omp_get_thread_num());
        if (clientes[i].id == id) {
            encontrado = 1; // Cliente encontrado
            printf("Digite o novo nome do cliente: ");
            getchar();  // Para consumir o caractere de nova linha (\n)
            fgets(clientes[i].nome, sizeof(clientes[i].nome), stdin);
            clientes[i].nome[strcspn(clientes[i].nome, "\n")] = 0;  // Remover a nova linha extra
            printf("Digite a nova idade do cliente: ");
            scanf("%d", &clientes[i].idade);
            printf("Cliente atualizado com sucesso!\n");

        }


    }

 end_time1 = omp_get_wtime();


printf("---------------------------------------:\n");
    printf("versao Paralela:\n");
    start_time2 = omp_get_wtime();
    // Verifica se o cliente com o ID existe
     encontrado = 0;
    #pragma omp parallel for
    for (int i = 0; i < num_clientes; i++) {
        printf("num_thead %d",omp_get_thread_num());
        if (clientes[i].id == id) {
            encontrado = 1; // Cliente encontrado
            printf("Digite o novo nome do cliente: ");
            getchar();  // Para consumir o caractere de nova linha (\n)
            fgets(clientes[i].nome, sizeof(clientes[i].nome), stdin);
            clientes[i].nome[strcspn(clientes[i].nome, "\n")] = 0;  // Remover a nova linha extra
            printf("Digite a nova idade do cliente: ");
            scanf("%d", &clientes[i].idade);
            printf("Cliente atualizado com sucesso!\n");

        }


    }
    end_time2 = omp_get_wtime();

    printf("tempo Paralela: %f \n",end_time2-start_time2);
    printf("tempo Sequencial: %f \n",end_time1-start_time1);


    if (!encontrado) {
        printf("Erro: Cliente com ID %d n�o encontrado.\n", id);
    }
}

// Fun��o para deletar um cliente pelo ID
void deletar_cliente() {
     double  start_time1,start_time2,end_time1,end_time2;
    int id;
    printf("Digite o ID do cliente a ser deletado: ");
    scanf("%d", &id);
    int encontrado = 0;
    printf("versao sequencial\n");

    start_time1 = omp_get_wtime();
    for (int i = 0; i < num_clientes; i++) {
            printf("num_thead %d ",omp_get_thread_num() );
        if (clientes[i].id == id) {
            encontrado = 1; // Cliente encontrado
            // Move todos os elementos seguintes uma posi��o � frente
            for (int j = i; j < num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            num_clientes--;
            printf("Cliente com ID %d deletado com sucesso!\n", id);

        }
    }
    end_time1 = omp_get_wtime();


printf("---------------------------------------:\n");
    printf("versao Paralela:\n");
    start_time2 = omp_get_wtime();
    // Verifica se o cliente com o ID existe
     encontrado = 0;
    #pragma omp parallel for
    for (int i = 0; i < num_clientes; i++) {
            printf("num_thead %d ",omp_get_thread_num() );
        if (clientes[i].id == id) {
            encontrado = 1; // Cliente encontrado
            // Move todos os elementos seguintes uma posi��o � frente
            for (int j = i; j < num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            num_clientes--;
            printf("Cliente com ID %d deletado com sucesso!\n", id);

        }
    }
    end_time2 = omp_get_wtime();

    printf("tempo Paralela: %f \n",end_time2-start_time2);
    printf("tempo Sequencial: %f \n",end_time1-start_time1);
    if (!encontrado) {
        printf("Erro: Cliente com ID %d n�o encontrado.\n", id);
    }
}

// Fun��o para exibir o menu e obter a op��o escolhida pelo usu�rio
void exibir_menu() {
    printf("\nMenu de Op��es :\n");
    printf("1. Criar Cliente\n");
    printf("2. Recuperar (Listar) Clientes\n");
    printf("3. Atualizar Cliente\n");
    printf("4. Deletar Cliente\n");
    printf("5. Visualizar Cliente\n");
    printf("6. Sair\n");
    printf("Escolha uma op��o: ");
}

int main() {
    int opcao;

    // Loop principal para intera��o com o usu�rio
    while (1) {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_cliente();
                break;
            case 2:
                ler_clientes();
                break;
            case 3:
                atualizar_cliente();
                break;
            case 4:
                deletar_cliente();
                break;
            case 5:
                visualizar_cliente();
                break;
            case 6:
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    }

    return 0;
}
