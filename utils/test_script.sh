#!/bin/bash

# Script para testar o sistema Reliable Multicast com Relógio de Lamport

echo "=== Sistema de criacao de processos ==="
echo ""

# Função para limpar processos
cleanup() {
    echo "Finalizando processos..."
    pkill -f "python.*hello-world.py"
    exit 0
}

# Captura Ctrl+C
trap cleanup SIGINT

# Verifica se o Python está disponível
if ! command -v python3 &> /dev/null; then
    echo "Python3 não encontrado. Instale o Python 3.6 ou superior."
    exit 1
fi

# Cria diretório para logs
mkdir -p logs

# Função para iniciar processo em background
start_process() {
    local process_id=$1
    local port=$2
    shift 2
    local peers="$@"
    
    echo "Iniciando processo $process_id na porta $port..."
    python3 ../script/hello-world.py $process_id $port $peers > logs/${process_id}.log 2>&1 &
    echo "Processo $process_id iniciado (PID: $!)"
}

# Configuração padrão: 3 processos
if [ "$1" = "demo" ]; then
    echo "Iniciando demonstração com 3 processos..."
    echo ""
    
    # Inicia processos
    start_process P1 8001 8002 8003
    sleep 3
    start_process P2 8002 8001 8003
    sleep 3
    start_process P3 8003 8001 8002
    
    echo ""
    echo "Todos os processos iniciados!"
    echo "Logs disponíveis em: logs/P1.log, logs/P2.log, logs/P3.log"
    echo ""
    echo "Pressione Ctrl+C para finalizar todos os processos"
    
    # Aguarda indefinidamente
    while true; do
        sleep 1
    done
    

    
else
    echo "Uso:"
    echo "  $0 demo        - Criação de processos"
    echo "Exemplo de uso manual:"
    echo "  Digite  utils/test_script.sh demo          - Inicia demonstração de criação de processos"
    echo "  ps -a         - Lista processos que estão rodando"
fi