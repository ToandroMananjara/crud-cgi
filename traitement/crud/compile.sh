#!/bin/bash

# Compiler AdminLogin.cpp
g++ -c -std=c++17 ./source/Crud.cpp -o Crud.o
echo "Crud.cpp compilé avec succès."

# Compiler main.cpp
g++ -c -std=c++17 main.cpp -o main.o
echo "main.cpp compilé avec succès."

# Linker les fichiers objets pour créer l'exécutable final
g++ main.o Crud.o -o crud.cgi
echo "Les fichiers objets ont été linkés. Exécutable créé : crud.cgi"
