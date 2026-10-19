# Algoritmos em C

Repositório com os programas desenvolvidos na disciplina **Algoritmo e Pensamento Computacional**, em linguagem C.

## Projetos

| Pasta | Descrição | Conceitos |
|---|---|---|
| [`01-controle-treinos-simples`](./01-controle-treinos-simples) | Menu de treinos e calorias, tudo dentro da `main` | `while`, `do-while`, `if/else`, `switch` |
| [`02-controle-treinos-completo`](./02-controle-treinos-completo) | Versão ampliada, com relatório por atividade | arrays, funções, `#define`, validação reutilizável |

## Controle de Treinos e Calorias

Programa de terminal com menu interativo que:

- registra treinos e **converte minutos em queima calórica estimada**;
- registra as calorias consumidas;
- exibe um **relatório condensado** com totais, média por treino e saldo calórico.

### Fórmula utilizada (método MET)

```
kcal = MET × peso (kg) × tempo (horas)
```

Os valores de MET são aproximados (baseados no *Compendium of Physical Activities*). **O resultado é uma estimativa** e não inclui o gasto basal.

| Atividade | MET |
|---|---|
| Caminhada | 3,5 |
| Corrida | 9,8 |
| Ciclismo | 8,0 |
| Natação | 6,0 |
| Musculação | 5,0 |

### Como compilar e executar

Requer um compilador C (por exemplo, o GCC).

```bash
# Versão simples
cd 01-controle-treinos-simples
gcc treinos_simples.c -o treinos_simples
./treinos_simples        # no Windows: treinos_simples.exe

# Versão completa
cd ../02-controle-treinos-completo
gcc controle_treinos.c -o controle_treinos
./controle_treinos
```

### Exemplo de uso

```
==========================================
   CONTROLE DE TREINOS E CALORIAS
==========================================
 1 - Registrar treino
 2 - Registrar calorias consumidas
 3 - Ver relatorio
 0 - Sair
------------------------------------------
Escolha uma opcao: 1

--- REGISTRAR TREINO ---
Escolha a atividade: 2
Duracao em minutos: 30

Treino registrado: 30 min
Queima estimada: 343 kcal
```

*(Exemplo com peso de 70 kg.)*

## Decisões técnicas

**Tratamento de entradas inválidas.** Cada leitura segue o mesmo padrão:

1. O retorno do `scanf` é verificado (`!= 1` indica falha de tipo, como letras no lugar de número).
2. Em caso de falha, a variável recebe um **valor sentinela** fora da faixa válida, já que o `scanf` não altera a variável quando falha.
3. O buffer do teclado é limpo com `while ((c = getchar()) != '\n' && c != EOF)`, evitando loop infinito.
4. Um `do-while` repete a pergunta até o valor estar dentro da faixa permitida.

Opções de menu inexistentes são tratadas pelo `default` do `switch`, e a divisão por zero no relatório é evitada verificando se há treinos registrados.

**Limitações conhecidas**

- Entradas como `12abc` são aceitas como `12`, e o restante pode afetar a leitura seguinte.
- Os dados ficam apenas em memória e são perdidos ao fechar o programa.
- O limite é de 100 treinos na versão completa.

## Próximos passos

- [ ] Salvar e carregar os dados em arquivo
- [ ] Trocar os arrays paralelos por `struct`
- [ ] Reescrever partes usando ponteiros

## Sobre o desenvolvimento

Projeto desenvolvido como atividade acadêmica, com apoio de IA (Claude) para explicações, revisão e geração de partes do código.
