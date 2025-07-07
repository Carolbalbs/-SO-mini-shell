# Documentação do Projeto Mini Shell 

## Introdução

Este projeto consiste na implementação de um shell básico em linguagem C, como parte da disciplina de Sistemas Operacionais ministrada pela professora Larissa Barbosa Leôncio Pinheiro. O objetivo principal é compreender e aplicar conceitos importantes de como um interpretador de comandos funciona por trás dos panos — similar ao que acontece em terminais como o bash ou o zsh.

A proposta foi desenvolver, do zero, um programa capaz de interpretar comandos digitados pelo usuário, executar programas externos, e oferecer suporte a comandos internos como exit, echo e env. Tudo isso utilizando apenas recursos da biblioteca padrão e chamadas POSIX — sem usar bibliotecas prontas como readline ou sistemas de parsing automáticos.

Além de aplicar os conceitos teóricos, o projeto também visa desenvolver habilidades práticas, como:

Manipulação de processos com fork, execvp, wait;

Gerenciamento de memória dinâmica com malloc e realloc;

Leitura de entrada em baixo nível com read();

Tratamento de erros e uso de códigos de retorno;

E principalmente, a organização modular do código, separando funcionalidades em arquivos e funções específicas.

Por fim, a experiência do usuário também foi considerada, com elementos como prompt colorido, mensagens amigáveis e uma pequena animação de saída para tornar o uso do shell mais interativo e didático.



#
(Content truncated due to size limit. Use line ranges to read in chunks)
