/*
 * SISTEMA DE PEDAGIO - CONTAGEM DE CARROS POR DIA DA SEMANA
 * ------------------------------------------------------------
 * Guarda a quantidade de carros que passaram pelo pedagio em
 * cada dia da semana, ao longo de varias semanas, e destaca em
 * NEGRITO os dias de pico.
 *
 * Estruturas usadas:
 *   - MATRIZ : carros[SEMANAS][DIAS]  (linha = semana, coluna = dia)
 *   - MATRIZ : nomes[DIAS][10]        (nomes dos dias, texto)
 *   - VETOR  : totalDia[DIAS]         (total acumulado de cada dia)
 *   - for    : percorrer vetores e matrizes
 *   - while  : menu principal e validacao das entradas
 *
 * Negrito: usa sequencias ANSI ("\033[1m" liga, "\033[0m" desliga).
 * Funciona em Linux, macOS, Windows Terminal e no CMD/PowerShell
 * do Windows 10 ou superior.
 *
 * Compilar: gcc pedagio.c -o pedagio
 */

#include <stdio.h>
#include <stdlib.h>

#define SEMANAS 4      /* quantidade de semanas controladas */
#define DIAS    7      /* dias da semana                    */

#define NEGRITO "\033[1m"
#define NORMAL  "\033[0m"

int main(void) {

    /* ---------- Dados ---------- */
    char nomes[DIAS][10] = {
        "Domingo", "Segunda", "Terca", "Quarta",
        "Quinta", "Sexta", "Sabado"
    };
    int carros[SEMANAS][DIAS] = {{0}};   /* matriz de contagem */
    int totalDia[DIAS];                  /* vetor de totais    */

    /* ---------- Variaveis de apoio ---------- */
    int opcao = -1;
    int semana, dia, qtd, ok, c, valido, confirmacao;
    int i, j, k;
    int maxLinha, maxTotal, totalGeral, barras;

#ifdef _WIN32
    system("");    /* habilita as sequencias ANSI no console do Windows */
#endif

    printf("Bem-vindo ao Sistema de Pedagio!\n");

    /* ---------- Menu principal ---------- */
    while (opcao != 0) {

        /* Recalcula o vetor de totais por dia (soma de cada coluna) */
        totalGeral = 0;
        maxTotal = 0;
        for (j = 0; j < DIAS; j++) {
            totalDia[j] = 0;
            for (i = 0; i < SEMANAS; i++) {
                totalDia[j] += carros[i][j];
            }
            totalGeral += totalDia[j];
            if (totalDia[j] > maxTotal) {
                maxTotal = totalDia[j];
            }
        }

        printf("\n==========================================\n");
        printf("        SISTEMA DE PEDAGIO\n");
        printf("==========================================\n");
        printf(" 1 - Registrar carros\n");
        printf(" 2 - Ver tabela semanal\n");
        printf(" 3 - Ver relatorio e dias de pico\n");
        printf(" 4 - Zerar dados\n");
        printf(" 0 - Sair\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");

        ok = scanf("%d", &opcao);
        while ((c = getchar()) != '\n' && c != EOF) { }   /* limpa o teclado */
        if (ok != 1) {
            if (ok == EOF) {
                opcao = 0;       /* entrada encerrada: sai do programa */
            } else {
                opcao = -1;      /* texto digitado: opcao invalida     */
            }
        }

        switch (opcao) {

            /* ---------------- REGISTRAR ---------------- */
            case 1:
                printf("\n--- REGISTRAR CARROS ---\n");

                /* Semana */
                valido = 0;
                while (!valido) {
                    printf("Semana (1 a %d): ", SEMANAS);
                    ok = scanf("%d", &semana);
                    while ((c = getchar()) != '\n' && c != EOF) { }
                    if (ok == EOF) {
                        printf("\nEntrada encerrada.\n");
                        return 0;
                    }
                    if (ok == 1 && semana >= 1 && semana <= SEMANAS) {
                        valido = 1;
                    } else {
                        printf("Valor invalido! Digite de 1 a %d.\n", SEMANAS);
                    }
                }

                /* Dia da semana */
                for (j = 0; j < DIAS; j++) {
                    printf(" %d - %s\n", j + 1, nomes[j]);
                }
                valido = 0;
                while (!valido) {
                    printf("Dia da semana (1 a %d): ", DIAS);
                    ok = scanf("%d", &dia);
                    while ((c = getchar()) != '\n' && c != EOF) { }
                    if (ok == EOF) {
                        printf("\nEntrada encerrada.\n");
                        return 0;
                    }
                    if (ok == 1 && dia >= 1 && dia <= DIAS) {
                        valido = 1;
                    } else {
                        printf("Valor invalido! Digite de 1 a %d.\n", DIAS);
                    }
                }

                /* Quantidade de carros */
                valido = 0;
                while (!valido) {
                    printf("Quantidade de carros (1 a 100000): ");
                    ok = scanf("%d", &qtd);
                    while ((c = getchar()) != '\n' && c != EOF) { }
                    if (ok == EOF) {
                        printf("\nEntrada encerrada.\n");
                        return 0;
                    }
                    if (ok == 1 && qtd >= 1 && qtd <= 100000) {
                        valido = 1;
                    } else {
                        printf("Valor invalido! Digite de 1 a 100000.\n");
                    }
                }

                carros[semana - 1][dia - 1] += qtd;

                printf("\nRegistrado: %d carros (semana %d, %s)\n",
                       qtd, semana, nomes[dia - 1]);
                printf("Total desse dia nessa semana: %d\n",
                       carros[semana - 1][dia - 1]);
                break;

            /* ---------------- TABELA SEMANAL ---------------- */
            case 2:
                printf("\n--- MOVIMENTO SEMANAL ---\n");
                printf("(em negrito: dia de pico de cada semana)\n\n");

                /* Cabecalho: 3 primeiras letras de cada dia */
                printf("%-8s", "Semana");
                for (j = 0; j < DIAS; j++) {
                    printf("%8.3s", nomes[j]);
                }
                printf("%10s\n", "Total");
                printf("--------");
                for (j = 0; j < DIAS; j++) {
                    printf("--------");
                }
                printf("----------\n");

                /* Uma linha por semana */
                for (i = 0; i < SEMANAS; i++) {

                    /* Descobre o maior valor da semana */
                    maxLinha = 0;
                    for (j = 0; j < DIAS; j++) {
                        if (carros[i][j] > maxLinha) {
                            maxLinha = carros[i][j];
                        }
                    }

                    printf("Sem %-4d", i + 1);
                    qtd = 0;                       /* total da semana */
                    for (j = 0; j < DIAS; j++) {
                        if (maxLinha > 0 && carros[i][j] == maxLinha) {
                            printf("%s%8d%s", NEGRITO, carros[i][j], NORMAL);
                        } else {
                            printf("%8d", carros[i][j]);
                        }
                        qtd += carros[i][j];
                    }
                    printf("%10d\n", qtd);
                }

                /* Linha de totais por dia (em negrito os dias de pico geral) */
                printf("--------");
                for (j = 0; j < DIAS; j++) {
                    printf("--------");
                }
                printf("----------\n");
                printf("%-8s", "Total");
                for (j = 0; j < DIAS; j++) {
                    if (maxTotal > 0 && totalDia[j] == maxTotal) {
                        printf("%s%8d%s", NEGRITO, totalDia[j], NORMAL);
                    } else {
                        printf("%8d", totalDia[j]);
                    }
                }
                printf("%10d\n", totalGeral);
                break;

            /* ---------------- RELATORIO ---------------- */
            case 3:
                printf("\n==========================================\n");
                printf("     RELATORIO - DIAS DE PICO\n");
                printf("==========================================\n");

                if (totalGeral == 0) {
                    printf("Nenhum carro registrado ainda.\n");
                    break;
                }

                printf("%-9s %8s %9s  Movimento\n", "Dia", "Total", "Media");
                printf("------------------------------------------\n");

                for (j = 0; j < DIAS; j++) {
                    barras = totalDia[j] * 20 / maxTotal;   /* escala 0 a 20 */

                    if (totalDia[j] == maxTotal) {
                        printf("%s", NEGRITO);              /* liga negrito */
                    }

                    printf("%-9s %8d %9.1f  ",
                           nomes[j], totalDia[j], (float)totalDia[j] / SEMANAS);
                    for (k = 0; k < barras; k++) {
                        printf("#");
                    }
                    if (totalDia[j] == maxTotal) {
                        printf(" <- PICO%s", NORMAL);       /* desliga negrito */
                    }
                    printf("\n");
                }

                printf("------------------------------------------\n");
                printf("Total geral : %d carros\n", totalGeral);
                printf("Media diaria: %.1f carros\n",
                       (float)totalGeral / (SEMANAS * DIAS));

                printf("Dia(s) de pico: ");
                for (j = 0; j < DIAS; j++) {
                    if (totalDia[j] == maxTotal) {
                        printf("%s%s%s (%d)  ", NEGRITO, nomes[j], NORMAL, totalDia[j]);
                    }
                }
                printf("\n");
                break;

            /* ---------------- ZERAR ---------------- */
            case 4:
                printf("\n--- ZERAR DADOS ---\n");
                valido = 0;
                while (!valido) {
                    printf("Apagar todos os registros? (1 = sim, 0 = nao): ");
                    ok = scanf("%d", &confirmacao);
                    while ((c = getchar()) != '\n' && c != EOF) { }
                    if (ok == EOF) {
                        printf("\nEntrada encerrada.\n");
                        return 0;
                    }
                    if (ok == 1 && (confirmacao == 0 || confirmacao == 1)) {
                        valido = 1;
                    } else {
                        printf("Digite 1 para sim ou 0 para nao.\n");
                    }
                }

                if (confirmacao == 1) {
                    for (i = 0; i < SEMANAS; i++) {
                        for (j = 0; j < DIAS; j++) {
                            carros[i][j] = 0;
                        }
                    }
                    printf("Dados apagados.\n");
                } else {
                    printf("Operacao cancelada.\n");
                }
                break;

            case 0:
                printf("\nEncerrando o sistema. Boa viagem!\n");
                break;

            default:
                printf("\nOpcao invalida! Escolha de 0 a 4.\n");
        }
    }

    return 0;
}
