#!/bin/bash

# Compiler User.cpp
g++ -Wall -c -std=c++17 ./source/User.cpp -o User.o
#clang++ -std=c++11 -o monprogramme monprogramme.cpp

echo "User.cpp compilé avec succès."

# Compiler index.cpp
g++ -c -std=c++17  index.cpp -o index.o
echo "index.cpp compilé avec succès."

# Linker les fichiers objets pour créer l'exécutable final
g++ -std=c++17  index.o User.o ../crud/Crud.o -o index.cgi
echo "Les fichiers objets ont été linkés. Exécutable créé : index.cgi"
