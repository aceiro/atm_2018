#!/bin/bash
#20181128145900
title 
clear
echo
echo "  --------------- Instlador Sumarizador ATM2s2018 ---------------"
echo
date +%H:%M:%S
echo "  --> Iniciando a Instalacao do Sumarizador, aguarde..."
echo
sleep 10
gcc main.c -o sumarizador 2> null
date +%H:%M:%S
echo "  --> Finalizando a Instalacao.Sera criado o arquivo sumarizador em:"
pwd
sleep 10
echo
date +%H:%M:%S
echo "  --> Para utilizar, inicialmente digite ./sumarizador --ajuda"
echo
#cleaning trash
rm null
read -p "Pressione qualquer tecla para sair do Instalador..."
echo
sleep 10

