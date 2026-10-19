/*
 * CONTROLE DE TREINOS E CALORIAS (versao simples)
 * ------------------------------------------------------------
 * Usa apenas: while, for, do-while, if/else e switch.
 * Sem funcoes extras e sem arrays: tudo dentro da main.
 *
 * Formula (metodo MET):  kcal = MET * peso(kg) * tempo(horas)
 * O resultado e uma ESTIMATIVA.
 *
 * Compilar: gcc treinos_simples.c -o treinos_simples
 */

#include <stdio.h>

int main(void) {

    /* ---------- Variaveis ---------- */
    int   opcao, atividade, minutos, c;
    int   totalTreinos = 0, totalMinutos = 0, totalRefeicoes = 0;
    float peso, met, kcal, refeicao;
    float totalQueimado = 0, kcalConsumidas = 0, saldo;

    printf("Bem-vindo ao Controle de Treinos e Calorias!\n");

    /* ---------- Le o peso (repete ate ser valido) ---------- */
    do {
        printf("Informe seu peso em kg (30 a 300): ");
        if (scanf("%f", &peso) != 1) {
            peso = 0;                                 /* forca repetir */
            while ((c = getchar()) != '\n' && c != EOF) { }  /* limpa teclado */
        }
        if (peso < 30 || peso > 300) {
            printf("Valor invalido!\n");
        }
    } while (peso < 30 || peso > 300);

    /* ---------- Menu principal ---------- */
    do {
        printf("\n==========================================\n");
        printf("   CONTROLE DE TREINOS E CALORIAS\n");
        printf("==========================================\n");
        printf(" 1 - Registrar treino\n");
        printf(" 2 - Registrar calorias consumidas\n");
        printf(" 3 - Ver relatorio\n");
        printf(" 0 - Sair\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;                               /* opcao invalida */
            while ((c = getchar()) != '\n' && c != EOF) { }
        }

        switch (opcao) {

            case 1:
                printf("\n--- REGISTRAR TREINO ---\n");
                printf(" 1 - Caminhada\n");
                printf(" 2 - Corrida\n");
                printf(" 3 - Ciclismo\n");
                printf(" 4 - Natacao\n");
                printf(" 5 - Musculacao\n");

                /* Le a atividade (1 a 5) */
                do {
                    printf("Escolha a atividade: ");
                    if (scanf("%d", &atividade) != 1) {
                        atividade = 0;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                    }
                    if (atividade < 1 || atividade > 5) {
                        printf("Opcao invalida!\n");
                    }
                } while (atividade < 1 || atividade > 5);

                /* Le os minutos (1 a 600) */
                do {
                    printf("Duracao em minutos: ");
                    if (scanf("%d", &minutos) != 1) {
                        minutos = 0;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                    }
                    if (minutos < 1 || minutos > 600) {
                        printf("Digite um valor entre 1 e 600!\n");
                    }
                } while (minutos < 1 || minutos > 600);

                /* Define o MET de acordo com a atividade */
                switch (atividade) {
                    case 1: met = 3.5; break;   /* Caminhada  */
                    case 2: met = 9.8; break;   /* Corrida    */
                    case 3: met = 8.0; break;   /* Ciclismo   */
                    case 4: met = 6.0; break;   /* Natacao    */
                    case 5: met = 5.0; break;   /* Musculacao */
                }

                /* Converte minutos em calorias */
                kcal = met * peso * (minutos / 60.0);

                totalTreinos++;
                totalMinutos  += minutos;
                totalQueimado += kcal;

                printf("\nTreino registrado: %d min\n", minutos);
                printf("Queima estimada: %.0f kcal\n", kcal);
                break;

            case 2:
                printf("\n--- REGISTRAR CALORIAS CONSUMIDAS ---\n");

                do {
                    printf("Calorias da refeicao (1 a 5000): ");
                    if (scanf("%f", &refeicao) != 1) {
                        refeicao = 0;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                    }
                    if (refeicao < 1 || refeicao > 5000) {
                        printf("Valor invalido!\n");
                    }
                } while (refeicao < 1 || refeicao > 5000);

                kcalConsumidas += refeicao;
                totalRefeicoes++;

                printf("\nRefeicao registrada: %.0f kcal\n", refeicao);
                printf("Total consumido: %.0f kcal\n", kcalConsumidas);
                break;

            case 3:
                saldo = kcalConsumidas - totalQueimado;

                printf("\n==========================================\n");
                printf("               RELATORIO\n");
                printf("==========================================\n");
                printf("Peso: %.1f kg\n\n", peso);

                printf("--- TREINOS ---\n");
                if (totalTreinos == 0) {
                    printf("Nenhum treino registrado.\n");
                } else {
                    printf("Sessoes       : %d\n", totalTreinos);
                    printf("Tempo total   : %d min\n", totalMinutos);
                    printf("Queima total  : %.0f kcal\n", totalQueimado);
                    printf("Media/treino  : %.0f kcal\n", totalQueimado / totalTreinos);
                }

                printf("\n--- ALIMENTACAO ---\n");
                printf("Refeicoes     : %d\n", totalRefeicoes);
                printf("Consumidas    : %.0f kcal\n", kcalConsumidas);

                printf("\n--- BALANCO ---\n");
                printf("Saldo (consumidas - queimadas): %.0f kcal\n", saldo);

                if (saldo > 0) {
                    printf("Saldo positivo: consumiu mais do que gastou nos treinos.\n");
                } else if (saldo < 0) {
                    printf("Saldo negativo: gastou mais nos treinos do que consumiu.\n");
                } else {
                    printf("Saldo equilibrado.\n");
                }

                printf("\nObs.: valores estimados, sem o gasto basal.\n");
                break;

            case 0:
                printf("\nAte a proxima! Bons treinos!\n");
                break;

            default:
                printf("\nOpcao invalida! Escolha de 0 a 3.\n");
        }

    } while (opcao != 0);

    return 0;
}
