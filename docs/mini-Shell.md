# Como Compilar e Rodar

Para compilar o mini-shell, certifique-se de ter o `gcc` (GNU Compiler Collection) instalado em seu sistema. Em sistemas baseados em Debian/Ubuntu, você pode instalá-lo com:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

Após a instalação do `gcc`, navegue até o diretório onde os arquivos-fonte (`index.c`, `utils.c`, `builtin.c`, `index.h`) estão localizados e execute o seguinte comando para compilar:

```bash
gcc -o mini_shell index.c utils.c builtin.c -I.
```

Este comando criará um executável chamado `mini_shell` no diretório atual.

Para rodar o mini-shell, basta executar o binário:

```bash
./mini_shell
```

O shell exibirá um prompt interativo (`🐚/caminho/atual🐚$>`) onde você poderá digitar comandos.


## Vídeo Curto Demonstrando o Uso do Shell

Mini-shell em ação!

