# README

Este documento apresenta uma descrição do código em C++ que implementa um simulador para análise de traces de acesso a páginas em um sistema de memória. O programa lê arquivos de trace, converte endereços hexadecimais para números de página, e calcula o número de frames necessários para armazenar essas páginas em um determinado intervalo de tempo. Abaixo estão os detalhes sobre a estrutura do código e suas funcionalidades.

## Descrição do Código

### Dependências
O código utiliza a biblioteca padrão do C++ (`<bits/stdc++.h>`) para manipulação de estruturas de dados e funções de entrada/saída.

### Estrutura de Dados

#### Classe `Page`
A classe `Page` é responsável por armazenar informações sobre uma página, incluindo:
- **Atributos**:
  - `pageNumber`: o número da página.
  - `tam`: o tamanho da página.
  - `hex`: uma string que representa a página em formato hexadecimal.
- **Métodos**:
  - `Page(char *hexa, int tamanho)`: Construtor que inicializa a página a partir de um valor hexadecimal.
  - `bin2dec(int8_t *bin, int qtdbits)`: Converte um número binário para decimal.
  - `hex2bin(char* hex, int qtdbits)`: Converte um número hexadecimal para binário.
  - `setPageNumber(int8_t *end, int qtdbits, int pgsize)`: Define o número da página com base no endereço binário e no tamanho da página.
  - `print()`: Exibe informações sobre a página, incluindo o valor hexadecimal, o tamanho e o número da página.
  - `getPageNumber()`: Retorna o número da página.

### Variáveis Globais
- `medttl`, `menttl`, `maittl`: Variáveis globais para armazenar a média, o menor e o maior número de frames necessários entre todos os traces.

### Função `runTrace`
A função `runTrace` processa um arquivo de trace para identificar as páginas acessadas. Os principais passos incluem:
- Leitura do arquivo de trace e armazenamento do conteúdo em um vetor.
- Análise do vetor, onde cada conjunto de caracteres representa uma página.
- Cálculo do número de frames necessários para armazenar as páginas acessadas em um intervalo de tempo definido pelo parâmetro `delta`.
- Armazenamento do total de frames necessários, bem como da média, menor e maior número de frames entre todos os traces analisados.

### Função Principal (`main`)
Na função `main`, o programa solicita ao usuário o tamanho da página e a janela de tempo (delta). Em seguida, chama a função `runTrace` para processar diferentes arquivos de trace (como `bzip.trace`, `gcc.trace`, `sixpack.trace` e `swim.trace`). Por fim, o programa imprime as estatísticas calculadas, incluindo a média, o menor e o maior número de frames necessários.

## Compilação e Execução
Para compilar e executar o código, utilize os seguintes comandos:

```bash
g++ -o simulador_paginas simulador_paginas.cpp
./simulador_paginas
```

## Observações
- O arquivo de trace deve estar no mesmo diretório que o executável, ou o caminho deve ser especificado corretamente.
- O código pode ser adaptado para incluir mais arquivos de trace, bastando adicionar chamadas para a função `runTrace` com os arquivos desejados.

Este código serve como uma ferramenta para simulação e análise de acesso à memória, sendo útil para estudos em sistemas operacionais e gerenciamento de memória.
