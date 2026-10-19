/*
 * CONTROLE DE TREINOS E CALORIAS
 * ------------------------------------------------------------
 * Menu interativo que registra treinos (convertendo minutos em
 * queima calorica estimada), registra calorias consumidas e
 * mostra um relatorio condensado.
 *
 * Formula usada (metodo MET):
 *   kcal = MET * peso(kg) * tempo(horas)
 *
 * Os valores de MET sao aproximados (baseados no Compendium of
 * Physical Activities). O resultado e uma ESTIMATIVA.
 *
 * Compilar: gcc controle_treinos.c -o controle_treinos
 */

#include <stdio.h>
#include <stdlib.h>   /* exit() */

#define MAX_TREINOS    100
#define NUM_ATIVIDADES 8

/* ---------- Tabela de atividades (arrays paralelos) ---------- */
const char *NOMES[NUM_ATIVIDADES] = {
    "Caminhada",
    "Corrida moderada",
    "Ciclismo moderado",
    "Natacao",
    "Musculacao",
    "HIIT / Funcional",
    "Danca",
    "Yoga"
};

const float MET[NUM_ATIVIDADES] = {
    3.5f, 9.8f, 8.0f, 6.0f, 5.0f, 8.0f, 5.0f, 2.5f
};

/* ---------- Dados do programa (estado global simples) -------- */
float pesoKg = 70.0f;            /* peso padrao ate o usuario informar */

int   treinoAtividade[MAX_TREINOS];  /* indice da atividade */
int   treinoMinutos[MAX_TREINOS];    /* duracao em minutos  */
float treinoKcal[MAX_TREINOS];       /* kcal queimadas      */
int   totalTreinos = 0;

float kcalConsumidas = 0.0f;
int   totalRefeicoes = 0;

/* ---------- Funcoes auxiliares de entrada -------------------- */

/* Descarta o que sobrou no buffer do teclado ate o ENTER. */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Le um inteiro entre min e max, repetindo ate ser valido. */
int lerInteiro(const char *mensagem, int min, int max) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1 && valor >= min && valor <= max) {
            limparBuffer();
            return valor;
        }
        if (feof(stdin)) {           /* entrada encerrada: sai do programa */
            printf("\nEntrada encerrada.\n");
            exit(0);
        }
        printf("Valor invalido! Digite um numero entre %d e %d.\n", min, max);
        limparBuffer();
    }
}

/* Le um numero real entre min e max, repetindo ate ser valido. */
float lerReal(const char *mensagem, float min, float max) {
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1 && valor >= min && valor <= max) {
            limparBuffer();
            return valor;
        }
        if (feof(stdin)) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }
        printf("Valor invalido! Digite um valor entre %.0f e %.0f.\n", min, max);
        limparBuffer();
    }
}

/* ---------- Calculo ------------------------------------------ */

/* Converte minutos de treino em kcal estimadas. */
float calcularKcal(int atividade, int minutos) {
    float horas = minutos / 60.0f;
    return MET[atividade] * pesoKg * horas;
}

/* ---------- Funcoes do menu ---------------------------------- */

void exibirMenu(void) {
    printf("\n==========================================\n");
    printf("   CONTROLE DE TREINOS E CALORIAS\n");
    printf("==========================================\n");
    printf(" 1 - Registrar treino\n");
    printf(" 2 - Registrar calorias consumidas\n");
    printf(" 3 - Ver relatorio condensado\n");
    printf(" 4 - Informar/alterar peso corporal (atual: %.1f kg)\n", pesoKg);
    printf(" 5 - Limpar todos os dados\n");
    printf(" 0 - Sair\n");
    printf("------------------------------------------\n");
}

void registrarTreino(void) {
    int i, atividade, minutos;

    if (totalTreinos >= MAX_TREINOS) {
        printf("\nLimite de %d treinos atingido!\n", MAX_TREINOS);
        return;
    }

    printf("\n--- REGISTRAR TREINO ---\n");
    for (i = 0; i < NUM_ATIVIDADES; i++) {
        printf(" %d - %s\n", i + 1, NOMES[i]);
    }

    atividade = lerInteiro("Escolha a atividade: ", 1, NUM_ATIVIDADES) - 1;
    minutos   = lerInteiro("Duracao em minutos (1 a 600): ", 1, 600);

    treinoAtividade[totalTreinos] = atividade;
    treinoMinutos[totalTreinos]   = minutos;
    treinoKcal[totalTreinos]      = calcularKcal(atividade, minutos);

    printf("\nTreino registrado: %s por %d min\n", NOMES[atividade], minutos);
    printf("Queima estimada: %.0f kcal\n", treinoKcal[totalTreinos]);

    totalTreinos++;
}

void registrarCalorias(void) {
    float kcal;

    printf("\n--- REGISTRAR CALORIAS CONSUMIDAS ---\n");
    kcal = lerReal("Calorias da refeicao (kcal): ", 1.0f, 5000.0f);

    kcalConsumidas += kcal;
    totalRefeicoes++;

    printf("\nRefeicao registrada: %.0f kcal\n", kcal);
    printf("Total consumido ate agora: %.0f kcal\n", kcalConsumidas);
}

void alterarPeso(void) {
    printf("\n--- PESO CORPORAL ---\n");
    pesoKg = lerReal("Informe seu peso em kg (30 a 300): ", 30.0f, 300.0f);
    printf("Peso atualizado para %.1f kg.\n", pesoKg);
    printf("(Treinos ja registrados mantem o calculo original.)\n");
}

void exibirRelatorio(void) {
    int i, j;
    int   totalMinutos = 0;
    float totalQueimado = 0.0f;
    float saldo;

    /* Acumuladores por atividade */
    int   minPorAtividade[NUM_ATIVIDADES]  = {0};
    float kcalPorAtividade[NUM_ATIVIDADES] = {0};

    for (i = 0; i < totalTreinos; i++) {
        j = treinoAtividade[i];
        minPorAtividade[j]  += treinoMinutos[i];
        kcalPorAtividade[j] += treinoKcal[i];
        totalMinutos        += treinoMinutos[i];
        totalQueimado       += treinoKcal[i];
    }

    saldo = kcalConsumidas - totalQueimado;

    printf("\n==========================================\n");
    printf("          RELATORIO CONDENSADO\n");
    printf("==========================================\n");
    printf("Peso corporal : %.1f kg\n\n", pesoKg);

    printf("--- TREINOS ---\n");
    if (totalTreinos == 0) {
        printf("Nenhum treino registrado.\n");
    } else {
        for (i = 0; i < NUM_ATIVIDADES; i++) {
            if (minPorAtividade[i] > 0) {
                printf("%-18s %4d min   %6.0f kcal\n",
                       NOMES[i], minPorAtividade[i], kcalPorAtividade[i]);
            }
        }
        printf("------------------------------------------\n");
        printf("Sessoes        : %d\n", totalTreinos);
        printf("Tempo total    : %d min (%.1f h)\n",
               totalMinutos, totalMinutos / 60.0f);
        printf("Media por treino: %.0f kcal\n", totalQueimado / totalTreinos);
    }

    printf("\n--- ALIMENTACAO ---\n");
    printf("Refeicoes registradas: %d\n", totalRefeicoes);
    printf("Calorias consumidas  : %.0f kcal\n", kcalConsumidas);

    printf("\n--- BALANCO ---\n");
    printf("Consumidas : %8.0f kcal\n", kcalConsumidas);
    printf("Queimadas  : %8.0f kcal (apenas treinos)\n", totalQueimado);
    printf("Saldo      : %+8.0f kcal\n", saldo);

    if (totalTreinos == 0 && totalRefeicoes == 0) {
        printf("\nSem dados suficientes para avaliar.\n");
    } else if (saldo > 0) {
        printf("\nSaldo positivo: voce consumiu mais do que gastou em treinos.\n");
    } else if (saldo < 0) {
        printf("\nSaldo negativo: voce gastou mais em treinos do que consumiu.\n");
    } else {
        printf("\nSaldo equilibrado.\n");
    }

    printf("\nObs.: valores estimados. O saldo nao inclui o gasto basal\n");
    printf("(calorias que o corpo gasta em repouso).\n");
}

void limparDados(void) {
    int confirmacao;

    printf("\n--- LIMPAR DADOS ---\n");
    confirmacao = lerInteiro("Apagar treinos e refeicoes? (1 = sim, 0 = nao): ", 0, 1);

    if (confirmacao == 1) {
        totalTreinos   = 0;
        kcalConsumidas = 0.0f;
        totalRefeicoes = 0;
        printf("Dados apagados.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
}

/* ---------- Programa principal ------------------------------- */

int main(void) {
    int opcao;

    printf("Bem-vindo ao Controle de Treinos e Calorias!\n");
    pesoKg = lerReal("Para comecar, informe seu peso em kg (30 a 300): ", 30.0f, 300.0f);

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 5);

        switch (opcao) {
            case 1: registrarTreino();   break;
            case 2: registrarCalorias(); break;
            case 3: exibirRelatorio();   break;
            case 4: alterarPeso();       break;
            case 5: limparDados();       break;
            case 0: printf("\nAte a proxima! Bons treinos!\n"); break;
        }
    } while (opcao != 0);

    return 0;
}
