#!/bin/bash

if [ "$1" = 'la' ]; then
    echo "     Refinamento -> Lagrange     "
    echo " ------------------------------- "
  ./bin/lagrange.exe
elif [ "$1" = 'tr'  ]; then
    echo "  Refinamento -> Troca de Sinal  "
    echo " ------------------------------- "
  ./bin/troca_sinal.exe
elif [ "$1" = 'bi'  ]; then
    echo "     Refinamento -> Bisseção     "
    echo " ------------------------------- "
  ./bin/bissecao.exe
elif [ "$1" = 'br'  ]; then
    echo "       Refinamento -> Corda      "
    echo " ------------------------------- "
  ./bin/broyden.exe
elif [ "$1" = 'co'  ]; then
    echo "    Refinamento -> Ponto Fixo    "
    echo " ------------------------------- "
  ./bin/corda.exe
elif [ "$1" = 'ne'  ]; then
    echo "      Refinamento -> Newton      "
    echo " ------------------------------- "
  ./bin/newton.exe
elif [ "$1" = 'po'  ]; then
    echo "      Refinamento -> Broyden     "
    echo " ------------------------------- "
  ./bin/ponto_fixo.exe
else
   
    echo " --- Isolamento --- "
    echo " la = Lagrange"
    echo " tr = Troca de Sinal"
    echo " ------------------- "
    
    echo " --- Refinamento --- "
    echo " bi = Bisseção"
    echo " co = Corda"
    echo " po = Ponto Fixo"
    echo " ne = Newton"
    echo " br = Broyden"
    echo " ------------------- "
fi
