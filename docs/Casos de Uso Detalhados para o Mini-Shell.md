# Casos de Uso Detalhados para o Mini-Shell

Este documento apresenta casos de uso detalhados para as funcionalidades do mini-shell, cobrindo tanto os requisitos explícitos do `Projeto.pdf` quanto as funcionalidades implementadas. Cada caso de uso descreve um cenário, as pré-condições, as etapas de execução e os resultados esperados.

## 1. Casos de Uso para Requisitos Básicos

### Caso de Uso 1.1: Inicialização e Prompt Interativo

*   **Cenário**: O usuário inicia o mini-shell e espera interagir com ele.
*   **Pré-condições**: O executável `mini_shell` está compilado e acessível.
*   **Passos**: 
    1.  O usuário executa `./mini_shell` no terminal.
*   **Resultado Esperado**: 
    *   Um banner de boas-vindas é exibido.
    *   Um prompt interativo é exibido, indicando o diretório de trabalho atual (ex: `🐚/home/ubuntu🐚$>`).
    *   O shell aguarda a entrada do usuário.

### Caso de Uso 1.2: Leitura de Comando Simples

*   **Cenário**: O usuário digita um comando simples sem argumentos.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `ls` e pressiona Enter.
*   **Resultado Esperado**: 
    *   O comando `ls` é executado.
    *   O conteúdo do diretório atual é listado na saída padrão.
    *   O prompt é exibido novamente.

### Caso de Uso 1.3: Leitura de Comando com Argumentos

*   **Cenário**: O usuário digita um comando com múltiplos argumentos.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `echo Hello World` e pressiona Enter.
*   **Resultado Esperado**: 
    *   O comando `echo` é executado.
    *   `Hello World` é impresso na saída padrão.
    *   O prompt é exibido novamente.

### Caso de Uso 1.4: Execução de Comando Built-in (`exit`)

*   **Cenário**: O usuário deseja encerrar o mini-shell.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `exit` e pressiona Enter.
*   **Resultado Esperado**: 
    *   Uma animação de desligamento (`spinnerLoading`) é exibida.
    *   O mini-shell é encerrado com sucesso.

### Caso de Uso 1.5: Execução de Comando Built-in (`env`)

*   **Cenário**: O usuário deseja visualizar as variáveis de ambiente.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `env` e pressiona Enter.
*   **Resultado Esperado**: 
    *   As variáveis de ambiente do processo atual são listadas na saída padrão.
    *   O prompt é exibido novamente.

### Caso de Uso 1.6: Execução de Comando Built-in (`echo` com opção `-n`)

*   **Cenário**: O usuário deseja imprimir texto sem uma nova linha final.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `echo -n Teste` e pressiona Enter.
*   **Resultado Esperado**: 
    *   `Teste` é impresso na saída padrão, sem uma nova linha. O próximo prompt aparece imediatamente após `Teste`.

### Caso de Uso 1.7: Execução de Comando Externo (`cat`)

*   **Cenário**: O usuário deseja visualizar o conteúdo de um arquivo.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt. Existe um arquivo de texto (ex: `test.txt`) no diretório atual.
*   **Passos**: 
    1.  O usuário digita `cat test.txt` e pressiona Enter.
*   **Resultado Esperado**: 
    *   O conteúdo de `test.txt` é exibido na saída padrão.
    *   O prompt é exibido novamente.

### Caso de Uso 1.8: Comando Não Encontrado

*   **Cenário**: O usuário digita um comando que não existe.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `comando_inexistente` e pressiona Enter.
*   **Resultado Esperado**: 
    *   Uma mensagem de erro indicando "Command not found" é exibida no erro padrão.
    *   O prompt é exibido novamente.

## 2. Casos de Uso para Redirecionamento de I/O

### Caso de Uso 2.1: Redirecionamento de Saída (`>`)

*   **Cenário**: O usuário deseja salvar a saída de um comando em um novo arquivo, sobrescrevendo-o se existir.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `echo "Hello Redirection" > output.txt` e pressiona Enter.
    2.  O usuário digita `cat output.txt` e pressiona Enter.
*   **Resultado Esperado**: 
    *   Após o passo 1, o prompt é exibido novamente sem saída visível.
    *   Após o passo 2, `Hello Redirection` é exibido na saída padrão.

### Caso de Uso 2.2: Redirecionamento de Saída (Append `>>`)

*   **Cenário**: O usuário deseja adicionar a saída de um comando ao final de um arquivo existente.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt. O arquivo `output.txt` existe e contém `Hello Redirection`.
*   **Passos**: 
    1.  O usuário digita `echo "Appended Line" >> output.txt` e pressiona Enter.
    2.  O usuário digita `cat output.txt` e pressiona Enter.
*   **Resultado Esperado**: 
    *   Após o passo 1, o prompt é exibido novamente sem saída visível.
    *   Após o passo 2, a saída padrão exibe:
        ```
        Hello Redirection
        Appended Line
        ```

### Caso de Uso 2.3: Redirecionamento de Entrada (`<`)

*   **Cenário**: O usuário deseja usar o conteúdo de um arquivo como entrada para um comando.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt. O arquivo `input.txt` existe e contém `Linha 1
Linha 2`.
*   **Passos**: 
    1.  O usuário digita `cat < input.txt` e pressiona Enter.
*   **Resultado Esperado**: 
    *   A saída padrão exibe:
        ```
        Linha 1
        Linha 2
        ```
    *   O prompt é exibido novamente.

## 3. Casos de Uso para Pipes

### Caso de Uso 3.1: Pipe Simples

*   **Cenário**: O usuário deseja encadear dois comandos, onde a saída do primeiro se torna a entrada do segundo.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `ls -l | grep mini_shell` e pressiona Enter.
*   **Resultado Esperado**: 
    *   A saída padrão exibe a linha correspondente ao executável `mini_shell` do comando `ls -l`.
    *   O prompt é exibido novamente.

### Caso de Uso 3.2: Pipe com Múltiplos Comandos

*   **Cenário**: O usuário deseja encadear três ou mais comandos.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `ls -l | grep .c | wc -l` e pressiona Enter.
*   **Resultado Esperado**: 
    *   A saída padrão exibe o número de arquivos `.c` no diretório atual.
    *   O prompt é exibido novamente.

## 4. Casos de Uso para Tratamento de Erros

### Caso de Uso 4.1: Erro de Redirecionamento (Arquivo de Saída Ausente)

*   **Cenário**: O usuário tenta redirecionar a saída sem especificar um arquivo.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `echo "Test" >` e pressiona Enter.
*   **Resultado Esperado**: 
    *   Uma mensagem de erro como `Redirection error: No output file specified` é exibida no erro padrão.
    *   O prompt é exibido novamente.

### Caso de Uso 4.2: Erro de Redirecionamento (Arquivo de Entrada Ausente)

*   **Cenário**: O usuário tenta redirecionar a entrada de um arquivo inexistente.
*   **Pré-condições**: O mini-shell está em execução e exibindo o prompt.
*   **Passos**: 
    1.  O usuário digita `cat < non_existent_file.txt` e pressiona Enter.
*   **Resultado Esperado**: 
    *   Uma mensagem de erro como `Redirection error: Could not open input file: No such file or directory` é exibida no erro padrão.
    *   O prompt é exibido novamente.

## 5. Casos de Uso para Requisitos de Entrega

### Caso de Uso 5.1: Geração do Arquivo README

*   **Cenário**: O projeto deve ser entregue com um arquivo README completo.
*   **Pré-condições**: O mini-shell está implementado e compilado.
*   **Passos**: 
    1.  O arquivo `README.md` é gerado (manualmente ou por script).
*   **Resultado Esperado**: 
    *   O arquivo `README.md` existe no diretório raiz do projeto.
    *   O `README.md` contém seções sobre:
        *   Como compilar e rodar o mini-shell.
        *   Quais chamadas ao sistema foram utilizadas.
        *   Exemplos de comandos testados e suas saídas.
        *   Limitações conhecidas da implementação.
        *   Um placeholder para o link do vídeo de demonstração.

### Caso de Uso 5.2: Geração do Vídeo de Demonstração

*   **Cenário**: O projeto deve ser acompanhado por um vídeo curto de demonstração.
*   **Pré-condições**: O mini-shell está funcional e os casos de uso básicos podem ser demonstrados.
*   **Passos**: 
    1.  Um vídeo de no máximo 5 minutos é gravado demonstrando o uso do shell.
*   **Resultado Esperado**: 
    *   Um arquivo de vídeo (ex: `.mp4`) é criado.
    *   O vídeo demonstra a inicialização do shell, a execução de comandos built-in e externos, e exemplos de redirecionamento e pipes.
    *   O vídeo é conciso e claro.




## Casos de Uso Detalhados para o Mini-Shell

Este documento descreve casos de uso detalhados para as funcionalidades implementadas no mini-shell, cobrindo os requisitos levantados no `Projeto.pdf` e as melhorias adicionais.

### 1. Execução de Comandos Básicos

**Requisito:** Executar no mínimo três comandos diferentes corretamente e com argumentos (ls, cat, echo).

**Caso de Uso 1.1: Executar `echo` com argumento simples**
- **Descrição:** O usuário deseja exibir uma string simples na saída padrão.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo Hello` e pressiona Enter.
- **Pós-condições:** A string "Hello" é exibida na tela, seguida por uma nova linha.

**Caso de Uso 1.2: Executar `echo` com múltiplos argumentos**
- **Descrição:** O usuário deseja exibir múltiplas strings separadas por espaços.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo Hello World` e pressiona Enter.
- **Pós-condições:** A string "Hello World" é exibida na tela, seguida por uma nova linha.

**Caso de Uso 1.3: Executar `ls` sem argumentos**
- **Descrição:** O usuário deseja listar o conteúdo do diretório atual.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `ls` e pressiona Enter.
- **Pós-condições:** Uma lista dos arquivos e diretórios no diretório atual é exibida na tela.

**Caso de Uso 1.4: Executar `ls` com argumento `-l`**
- **Descrição:** O usuário deseja listar o conteúdo do diretório atual em formato longo.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `ls -l` e pressiona Enter.
- **Pós-condições:** Uma lista detalhada dos arquivos e diretórios no diretório atual é exibida na tela, incluindo permissões, proprietário, tamanho e data de modificação.

**Caso de Uso 1.5: Executar `cat` em um arquivo existente**
- **Descrição:** O usuário deseja exibir o conteúdo de um arquivo de texto.
- **Pré-condições:** O mini-shell está em execução e um arquivo de texto (ex: `test.txt`) existe no diretório atual.
- **Passos:**
    1. O usuário digita `cat test.txt` e pressiona Enter.
- **Pós-condições:** O conteúdo de `test.txt` é exibido na tela.

**Caso de Uso 1.6: Executar `cat` em um arquivo inexistente**
- **Descrição:** O usuário tenta exibir o conteúdo de um arquivo que não existe.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `cat non_existent_file.txt` e pressiona Enter.
- **Pós-condições:** Uma mensagem de erro (ex: "cat: non_existent_file.txt: No such file or directory") é exibida na tela.

### 2. Parsing Robusto (Tratamento de Aspas)

**Requisito:** Suporte a argumentos com espaços usando aspas.

**Caso de Uso 2.1: `echo` com aspas duplas**
- **Descrição:** O usuário deseja exibir uma frase com espaços como um único argumento.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo "Hello World from Mini-Shell"` e pressiona Enter.
- **Pós-condições:** A frase "Hello World from Mini-Shell" é exibida na tela como uma única string.

**Caso de Uso 2.2: `echo` com aspas simples**
- **Descrição:** O usuário deseja exibir uma frase com espaços usando aspas simples.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo 'Another test with quotes'` e pressiona Enter.
- **Pós-condições:** A frase "Another test with quotes" é exibida na tela como uma única string.

**Caso de Uso 2.3: Comando com aspas e outros argumentos**
- **Descrição:** O usuário executa um comando que combina argumentos com e sem aspas.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo Part1 "Part 2 with spaces" Part3` e pressiona Enter.
- **Pós-condições:** A saída "Part1 Part 2 with spaces Part3" é exibida na tela.

### 3. Tratamento de Erro "Comando Não Encontrado"

**Requisito:** Exibir mensagem de erro clara para comandos inválidos.

**Caso de Uso 3.1: Executar comando inexistente**
- **Descrição:** O usuário digita um comando que não existe no sistema.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `non_existent_command` e pressiona Enter.
- **Pós-condições:** A mensagem de erro "Command not found" é exibida na tela.

### 4. Redirecionamento de Entrada/Saída

**Requisito:** Suporte a `>`, `>>`, `<`.

**Caso de Uso 4.1: Redirecionamento de saída (sobrescrever)**
- **Descrição:** O usuário deseja salvar a saída de um comando em um novo arquivo ou sobrescrever um arquivo existente.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo "Hello World" > output.txt` e pressiona Enter.
    2. O usuário digita `cat output.txt` e pressiona Enter.
- **Pós-condições:** O arquivo `output.txt` é criado (ou sobrescrito) e contém "Hello World". O comando `cat` exibe "Hello World".

**Caso de Uso 4.2: Redirecionamento de saída (anexar)**
- **Descrição:** O usuário deseja adicionar a saída de um comando ao final de um arquivo existente.
- **Pré-condições:** O mini-shell está em execução e `output.txt` contém "Hello World".
- **Passos:**
    1. O usuário digita `echo "Appended Line" >> output.txt` e pressiona Enter.
    2. O usuário digita `cat output.txt` e pressiona Enter.
- **Pós-condições:** O arquivo `output.txt` agora contém "Hello World\nAppended Line". O comando `cat` exibe o conteúdo completo.

**Caso de Uso 4.3: Redirecionamento de entrada**
- **Descrição:** O usuário deseja usar o conteúdo de um arquivo como entrada para um comando.
- **Pré-condições:** O mini-shell está em execução e um arquivo `input.txt` existe com o conteúdo "This is input.".
- **Passos:**
    1. O usuário digita `cat < input.txt` e pressiona Enter.
- **Pós-condições:** O conteúdo de `input.txt` ("This is input.") é exibido na tela.

**Caso de Uso 4.4: Redirecionamento de entrada e saída combinados**
- **Descrição:** O usuário deseja processar um arquivo de entrada e salvar a saída em um arquivo diferente.
- **Pré-condições:** O mini-shell está em execução e `input.txt` existe com o conteúdo "Line 1\nLine 2".
- **Passos:**
    1. O usuário digita `cat < input.txt > output_copy.txt` e pressiona Enter.
    2. O usuário digita `cat output_copy.txt` e pressiona Enter.
- **Pós-condições:** O arquivo `output_copy.txt` é criado e contém o mesmo conteúdo de `input.txt`. O comando `cat` exibe o conteúdo de `output_copy.txt`.

### 5. Pipes (`|`)

**Requisito:** Suporte a pipes para encadeamento de comandos.

**Caso de Uso 5.1: Pipe simples (`ls | grep`)**
- **Descrição:** O usuário deseja listar arquivos e filtrar a saída usando `grep`.
- **Pré-condições:** O mini-shell está em execução e existem arquivos `.c` no diretório atual.
- **Passos:**
    1. O usuário digita `ls -l | grep .c` e pressiona Enter.
- **Pós-condições:** Apenas as linhas da saída de `ls -l` que contêm ".c" são exibidas na tela.

**Caso de Uso 5.2: Pipe com múltiplos comandos**
- **Descrição:** O usuário deseja encadear três comandos usando pipes.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `echo "one\ntwo\nthree" | grep "o" | wc -l` e pressiona Enter.
- **Pós-condições:** O número de linhas que contêm "o" (neste caso, 2) é exibido na tela.

### 6. Built-in `cd`

**Requisito:** Implementar o comando `cd`.

**Caso de Uso 6.1: `cd` para um diretório existente**
- **Descrição:** O usuário deseja mudar para um diretório específico.
- **Pré-condições:** O mini-shell está em execução e um diretório (ex: `my_dir`) existe.
- **Passos:**
    1. O usuário digita `cd my_dir` e pressiona Enter.
- **Pós-condições:** O diretório de trabalho atual do shell é alterado para `my_dir`. O prompt reflete o novo diretório.

**Caso de Uso 6.2: `cd` sem argumentos (para HOME)**
- **Descrição:** O usuário deseja retornar ao seu diretório `HOME`.
- **Pré-condições:** O mini-shell está em execução e o diretório atual não é o `HOME`.
- **Passos:**
    1. O usuário digita `cd` e pressiona Enter.
- **Pós-condições:** O diretório de trabalho atual do shell é alterado para o diretório `HOME` do usuário. O prompt reflete o novo diretório.

**Caso de Uso 6.3: `cd` para um diretório inexistente**
- **Descrição:** O usuário tenta mudar para um diretório que não existe.
- **Pré-condições:** O mini-shell está em execução.
- **Passos:**
    1. O usuário digita `cd non_existent_dir` e pressiona Enter.
- **Pós-condições:** Uma mensagem de erro (ex: "cd error: No such file or directory") é exibida na tela e o diretório de trabalho atual permanece inalterado.


