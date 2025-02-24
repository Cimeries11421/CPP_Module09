#!/bin/bash

NUM_TESTS=3 #nombre de test

for ((test_num=1; test_num<=NUM_TESTS; test_num++)); do
    echo "===== Test $test_num ====="

    # Générer les nombres aléatoires et les stocker dans une variable
    random_numbers=$(shuf -i 1-100 -n 15 | tr "\n" " ")
    
    # Afficher les nombres aléatoires générés
   echo "Nombres aléatoires générés: $random_numbers"
    
    # Exécution du programme avec ces nombres
    ./PmergeMe $random_numbers | tr ' ' '\n' > output_programme.txt

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

