#!/bin/bash

if [ "$1" = 'la' ]; then
    echo  "Compilando Lagrange..."
    g++ -std=c++11  isolamento/lagrange.cpp -o bin/lagrange.exe
elif [ "$1" = 'tr'  ]; then
    echo  "Compilando TrocaSinal..."
    g++ -std=c++11  isolamento/troca_sinal.cpp -o bin/troca_sinal.exe
elif [ "$1" = 'bi'  ]; then
    echo  "Compilando Bisseção..."
    g++ -std=c++11  refinamento/bissecao.cpp -o bin/bissecao.exe
elif [ "$1" = 'br'  ]; then
    echo  "Compilando Corda      "
    g++ -std=c++11  refinamento/corda.cpp -o bin/corda.exe
elif [ "$1" = 'co'  ]; then
    echo  "Compilando Ponto Fixo    "
    g++ -std=c++11  refinamento/ponto_fixo.cpp -o bin/ponto_fixo.exe
elif [ "$1" = 'ne'  ]; then
    echo  "Compilando Newton      "
    g++ -std=c++11  refinamento/newton.cpp -o bin/newton.exe
elif [ "$1" = 'po'  ]; then
    echo  "Compilando Broyden     "
    g++ -std=c++11  refinamento/broyden.cpp -o bin/broyden.exe
else

    echo  "Compilando Lagrange..."
    g++ -std=c++11  isolamento/lagrange.cpp -o bin/lagrange.exe

    echo  "Compilando TrocaSinal..."
    g++ -std=c++11  isolamento/troca_sinal.cpp -o bin/troca_sinal.exe

    echo  "Compilando Bisseção..."
    g++ -std=c++11  refinamento/bissecao.cpp -o bin/bissecao.exe

    echo  "Compilando Corda      "
    g++ -std=c++11  refinamento/corda.cpp -o bin/corda.exe

    echo  "Compilando Ponto Fixo    "
    g++ -std=c++11  refinamento/ponto_fixo.cpp -o bin/ponto_fixo.exe

    echo  "Compilando Newton      "
    g++ -std=c++11  refinamento/newton.cpp -o bin/newton.exe

    echo  "Compilando Broyden     "
    g++ -std=c++11  refinamento/broyden.cpp -o bin/broyden.exe
    
fi