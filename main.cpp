// Alunos: Juliano Cesar Ferreira Ramos, Bruna Motta de Macedo, Livia Pessoa de Andrade
// Turma: 22A

#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

struct database
{
    int id;
    string name;
    int age;
    string platform;
    string description;
};

string add()
{
    setlocale(LC_ALL, "UTF-8");

    int location = 0, lines = 0, size = 40;
    string line, teste;

    ifstream input_file("Banco_de_dados.csv");

    if (!input_file)
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        return "error";
    }

    database *games, *new_games;
    games = new database[40];

    while (getline(input_file, line))
    {
        if (lines >= size)
        {
            // Redimensionar o array se necessário
            new_games = new database[size + 10];
            for (int i = 0; i < size; i++)
            {
                new_games[i] = games[i];
            }
            delete[] games;
            games = new_games;
            size += 10;
        }

        cout << "Verificando ID..." << endl;

        location = line.find(';');
        teste = line.substr(1, location);
        cout << teste << endl;
        games[lines].id = stoi(line.substr(1, location));
        line = line.substr(location + 1, line.length());

        cout << "Verificando nome..." << endl;

        location = line.find(';');
        games[lines].name = line.substr(2, location - 4);
        line = line.substr(location + 1, line.length());

        cout << "Verificando ano..." << endl;

        location = line.find(';');
        games[lines].age = stoi(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        cout << "Verificando plataforma..." << endl;

        location = line.find(';');
        games[lines].platform = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        cout << "Verificando descrição..." << endl;

        games[lines].description = line.substr(2, line.length() - 5);

        lines++;

        cout << "A linha " << lines << " foi escrita com sucesso" << endl;
    }

    for (int i = 0; i < lines; i++)
    {
        cout << games[i].id << endl;
        cout << games[i].name << endl;
        cout << games[i].age << endl;
        cout << games[i].platform << endl;
        cout << games[i].description << endl;
        cout << endl;
    }

    return "success";
}

int main()
{
    setlocale(LC_ALL, "UTF-8");

    int option = 0;
    while (option != 6)
    {
        cout << "----- MENU PRINCIPAL -----\n\n";
        cout << "[1] - Cadastro de jogos" << endl;
        cout << "[2] - Consulta de jogos" << endl;
        cout << "[3] - Ordernar a lista de jogos" << endl;
        cout << "[4] - Excluir jogo" << endl;
        cout << "[5] - Salvar as alterações" << endl;
        cout << "[6] - Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << add();
            break;
        case 2:
            cout << "";
            break;
        case 3:
            cout << "";
            break;
        case 4:
            cout << "";
            break;
        case 5:
            cout << "";
            break;
        case 6:
            cout << "Encerrando sistema..." << endl;
            break;
        default:
            cout << "Digite uma opcao valida" << endl;
            break;
        }
    }

    return 0;
}
/*int main()
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
}*/