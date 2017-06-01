#!/bin/bash


if [ "$1" = 'la' ]; then
    ./compile.sh la $*
     echo  ""
    echo "Isolamento -> Lagrange     "
    echo "------------------------------- "
    ./bin/lagrange.exe $*
    
elif [ "$1" = 'tr'  ]; then
    ./compile.sh tr
     echo  ""
    echo "Isolamento -> Troca de Sinal  "
    echo "------------------------------- "
    ./bin/troca_sinal.exe $*
    
elif [ "$1" = 'bi'  ]; then
      ./compile.sh bi
     echo  ""
    echo "Refinamento -> Bisseção     "
    echo "------------------------------- "
    ./bin/bissecao.exe $*
    
elif [ "$1" = 'br'  ]; then
    ./compile.sh br
     echo  ""
    echo "Refinamento -> Broyden      "
    echo "------------------------------- "

    ./bin/broyden.exe $*
elif [ "$1" = 'co'  ]; then
    ./compile.sh co
     echo  ""
    echo "Refinamento -> Corda        "
    echo "------------------------------- "

    ./bin/corda.exe $*
elif [ "$1" = 'ne'  ]; then
    ./compile.sh ne
     echo  ""
    echo "Refinamento -> Newton      "
    echo "------------------------------- "

    ./bin/newton.exe $*
elif [ "$1" = 'bn'  ]; then
    ./compile.sh bn
     echo  ""
    echo "Refinamento -> Bisseção Newton      "
    echo "------------------------------- "
    ./bin/bissecao_newton.exe $*
elif [ "$1" = 'po'  ]; then
      ./compile.sh po
     echo  ""
    echo "Refinamento -> Ponto Fixo  "
    echo "------------------------------- "

    ./bin/ponto_fixo.exe $*
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
    echo " bn = Bisseção-Newton"
    echo " br = Broyden"
    echo " ------------------- "
fi
