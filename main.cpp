// Alunos: Juliano Cesar Ferreira Ramos, Bruna Motta de Macedo, Livia Pessoa de Andrade
// Turma: 22A

#include <iostream>
#include <fstream>
#include <locale.h>
#include <iomanip>

using namespace std;

int main()
{
    ifstream file("Banco_de_dados.csv");
    string line, name, plataform, description;
    int location = 0, id = 0, age = 0;

    getline(file, line); // Linha de descrição
    getline(file, line); // Linha de dados

    location = line.find(';');
    id = stoi(line.substr(1, location));
    line = line.substr(location + 1, line.length());

    location = line.find(';');
    name = line.substr(2, location - 4);
    line = line.substr(location + 1, line.length());

    location = line.find(';');
    age = stoi(line.substr(0, location));
    line = line.substr(location + 1, line.length());

    location = line.find(';');
    plataform = line.substr(0, location);
    line = line.substr(location + 1, line.length());

    description = line.substr(2, line.length() - 5);

    setlocale(LC_ALL, "");
    cout
        << id << endl
        << name << endl
        << age << endl
        << plataform << endl
        << description << endl;

    return 0;
}