#!/bin/bash

NUM_TESTS=1 #nombre de test

for ((test_num=1; test_num<=NUM_TESTS; test_num++)); do
    echo "===== Test $test_num ====="

    N=$((RANDOM % 120 + 1))   #N = nb elements/arguments
    echo "Nombre d'éléments : $N"

    numbers=""
    for ((i=0; i<N; i++)); do
        numbers+="$((RANDOM % 10)) "  #nombre genere entre 0 et xxxx
    done

    echo "$numbers"

    ./PmergeMe $numbers | tr ' ' '\n' > output_programme.txt

    tr ' ' '\n' < output_programme.txt | sed '/^$/d' | sort -n > test.txt
    sed -i '' -e '$a\' test.txt
    sed -i '' -e '$d' output_programme.txt


    if diff -c output_programme.txt test.txt > /dev/null ; then
    echo "✅ Test $test_num réussi !"
    else
    echo "❌ Test $test_num échoué !"
    diff -c output_programme.txt test.txt
    fi

  echo "======================"
done
