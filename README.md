# PGM - Protein Geometry Manager

**PGM** (Protein Geometry Manager) é um programa desenvolvido em C++ para o processamento e preparação de arquivos PDB para simulações no GROMACS. Ele automatiza etapas essenciais, como limpeza de resíduos de água, geração de topologias, configuração da caixa de simulação, e solvatação do sistema.

## Funcionalidades
- Processa arquivos `.pdb` para preparar entradas para o GROMACS.
- Realiza as seguintes etapas automaticamente:
  1. Remove resíduos de água indesejados (`HOH`).
  2. Gera a topologia do sistema.
  3. Configura uma caixa de simulação com dimensões definidas.
  4. Solvata a caixa com moléculas de água.
- Cria uma pasta separada para armazenar os arquivos gerados para cada arquivo `.pdb` processado.

## Pré-requisitos
- **Sistema operacional**: Linux (testado no Ubuntu).
- **GROMACS**: Certifique-se de que o GROMACS está instalado e configurado no seu sistema.
- **Compilador C++**: Ex.: g++

## Como usar
1. Clone este repositório:
   ```bash
   git clone <url-do-repositório>
   cd <nome-do-repositório>
   ```
2. Compile o programa:
   ```bash
   g++ -o pgm pgm.cpp
   ```
3. Execute o programa na pasta contendo os arquivos `.pdb`:
   ```bash
   ./pgm
   ```
4. Siga as instruções na interface para selecionar um arquivo `.pdb` ou processar todos os arquivos disponíveis.

## Teste o programa
Incluímos neste repositório um arquivo de exemplo chamado `1aki.pdb`. Você pode usá-lo para testar o funcionamento do programa. Basta seguir as instruções de uso descritas acima.

## Observações
- O programa gera arquivos intermediários e finais na mesma pasta do executável, organizando-os em subpastas com o nome base do arquivo `.pdb` processado.
- Certifique-se de que a pasta de trabalho está limpa para evitar conflitos com arquivos existentes.

## Contribuições
Contribuições são bem-vindas! Caso encontre algum problema ou tenha sugestões de melhoria, sinta-se à vontade para abrir uma issue ou enviar um pull request.

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).

## Autor
Lucca - Desenvolvedor Full Stack e Químico Teórico

---

### Exemplos de Arquivos Gerados
Ao processar o arquivo `1aki.pdb`, o programa gerará os seguintes arquivos:
- `1aki_clean.pdb`
- `1aki_processed.gro`
- `1aki_newbox.gro`
- `1aki_solv.gro`
- `topol.top`
- `posre.itp`

Todos os arquivos serão organizados na subpasta `1aki/`.

