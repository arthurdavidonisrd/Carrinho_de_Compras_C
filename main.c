#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define QTD_PRODUTOS 5

int main() {
    int codigos[] = {101, 102, 103, 104, 105};
    char nomes[][20] = {"Arroz", "Feijao", "Macarrao", "Farinha", "Acucar"};
    float precos[] = {5.5, 7.2, 4.0, 3.8, 2.5};

    int carrinho[MAX_ITENS][3]; // código, quantidade, índice
    float subtotais[MAX_ITENS]; // subtotal por item
    int itens_no_carrinho = 0;
    int continuar = 1;

    printf("==== Lista de Produtos ====\n");
    for (int i = 0; i < QTD_PRODUTOS; i++) {
        printf("Código: %d\tNome: %s\tPreço: R$ %.2f\n", codigos[i], nomes[i], precos[i]);
    }

    while (continuar && itens_no_carrinho < MAX_ITENS) {
        int codigo, quantidade;
        int indice_produto = -1;

        printf("\nDeseja adicionar um item ao carrinho? (1 = Sim, 0 = Nao): ");
        if (scanf("%d", &continuar) != 1 || (continuar != 0 && continuar != 1)) {
            printf("Entrada inválida. Encerrando o programa.\n");
            break;
        }
        if (!continuar) break;

        if (itens_no_carrinho >= MAX_ITENS) {
            printf("Carrinho cheio! Limite de 10 itens atingido.\n");
            break;
        }

        printf("Digite o código do produto: ");
        if (scanf("%d", &codigo) != 1) {
            printf("Entrada inválida para código.\n");
            while (getchar() != '\n');
            continue;
        }

        // Verifica se o código existe
        for (int i = 0; i < QTD_PRODUTOS; i++) {
            if (codigos[i] == codigo) {
                indice_produto = i;
                break;
            }
        }
        if (indice_produto == -1) {
            printf("Código de produto inválido.\n");
            continue;
        }

        printf("Digite a quantidade: ");
        if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
            printf("Quantidade inválida.\n");
            while (getchar() != '\n');
            continue;
        }

        // Verifica se o produto já está no carrinho
        int encontrado = 0;
        for (int i = 0; i < itens_no_carrinho; i++) {
            if (carrinho[i][0] == codigo) {
                printf("Produto já está no carrinho. Deseja atualizar a quantidade? (1 = Sim, 0 = Não): ");
                int atualizar;
                scanf("%d", &atualizar);
                if (atualizar == 1) {
                    carrinho[i][1] = quantidade;
                    subtotais[i] = precos[indice_produto] * quantidade;
                    printf("Quantidade atualizada!\n");
                } else {
                    printf("Nenhuma alteração feita.\n");
                }
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            carrinho[itens_no_carrinho][0] = codigo;
            carrinho[itens_no_carrinho][1] = quantidade;
            carrinho[itens_no_carrinho][2] = indice_produto;
            subtotais[itens_no_carrinho] = precos[indice_produto] * quantidade;
            itens_no_carrinho++;
            printf("Produto adicionado com sucesso!\n");
        }

        // Mostrar carrinho atual
        printf("\n=== CARRINHO ATUAL ===\n");
        printf("Produto\t\tQtd\tPreço\tSubtotal\n");
        for (int i = 0; i < itens_no_carrinho; i++) {
            int idx = carrinho[i][2];
            printf("%-10s\t%d\tR$%.2f\tR$%.2f\n", nomes[idx], carrinho[i][1], precos[idx], subtotais[i]);
        }
    }

    // Ordenar carrinho por nome (alfabética)
    for (int i = 0; i < itens_no_carrinho - 1; i++) {
        for (int j = i + 1; j < itens_no_carrinho; j++) {
            int idx_i = carrinho[i][2];
            int idx_j = carrinho[j][2];
            if (strcmp(nomes[idx_i], nomes[idx_j]) > 0) {
                
                int temp0 = carrinho[i][0], temp1 = carrinho[i][1], temp2 = carrinho[i][2];
                float temp_sub = subtotais[i];

                carrinho[i][0] = carrinho[j][0];
                carrinho[i][1] = carrinho[j][1];
                carrinho[i][2] = carrinho[j][2];
                subtotais[i] = subtotais[j];

                carrinho[j][0] = temp0;
                carrinho[j][1] = temp1;
                carrinho[j][2] = temp2;
                subtotais[j] = temp_sub;
            }
        }
    }

    // Exibir nota fiscal
    if (itens_no_carrinho == 0) {
        printf("\nNenhum item foi adicionado ao carrinho.\n");
    } else {
        printf("\n\n===== NOTA FISCAL =====\n");
        float total = 0.0;
        int total_itens = 0;

        printf("Produto\t\tQtd\tPreço\tSubtotal\n");
        printf("----------------------------------------\n");

        for (int i = 0; i < itens_no_carrinho; i++) {
            int idx = carrinho[i][2];
            int qtd = carrinho[i][1];
            float preco = precos[idx];
            float subtotal = subtotais[i];

            printf("%-10s\t%d\tR$%.2f\tR$%.2f\n", nomes[idx], qtd, preco, subtotal);
            total += subtotal;
            total_itens += qtd;
        }

        printf("----------------------------------------\n");
        printf("TOTAL: \t\t\t\tR$%.2f\n", total);
        printf("Total de itens comprados: %d\n", total_itens);
    }

    return 0;
}
