// Alunos: Juliano Cesar Ferreira Ramos, Bruna Motta de Macedo, Livia Pessoa de Andrade
// Turma: 22A

#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

struct dataBase
{
    int id;
    string name;
    int age;
    string platform;
    string description;
};

void load(dataBase *&games, int &size, int &lines)
{
    int location = 0;
    string line = "";

    ifstream inputFile("Banco_de_dados.csv");

    if (!inputFile)
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    getline(inputFile, line); // linha de descrição de dados

    while (getline(inputFile, line))
    // while (lines <= 2)
    {
        if (lines >= size)
        {
            // Redimensionar o array se necessário
            dataBase *newGames = new dataBase[size + 10];
            for (int i = 0; i < size; i++)
            {
                newGames[i] = games[i];
            }
            delete[] games;
            games = newGames;
            size += 10;
        }

        // cout << "Verificando ID..." << endl;

        location = line.find(';');
        games[lines].id = stoi(line.substr(1, location));
        line = line.substr(location + 1, line.length());

        // cout << "Verificando nome..." << endl;

        location = line.find(';');
        games[lines].name = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        // cout << "Verificando ano..." << endl;

        location = line.find(';');
        games[lines].age = stoi(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        // cout << "Verificando plataforma..." << endl;

        location = line.find(';');
        games[lines].platform = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        // cout << "Verificando descrição..." << endl;

        games[lines].description = line.substr(0, line.length() - 1);

        lines++;

        // cout << "A linha " << lines << " foi escrita com sucesso" << endl;
        // cout << endl;
    }

    cout << endl;
    cout << "Pré-leitura do arquivo concluida com sucesso" << endl;
    cout << endl;
}

string search(dataBase *&games, int &lines)
{
    for (int i = 0; i < lines; i++)
    {
        cout << games[i].id << endl;
        cout << games[i].name << endl;
        cout << games[i].age << endl;
        cout << games[i].platform << endl;
        cout << games[i].description << endl;
        cout << endl;
    }

    cout << "Leitura da lista de jogos concluida com sucesso" << endl;

    return "";
}

string add(dataBase *&games, int &size, int &lines)
{
    // setlocale(LC_ALL, "UTF-8");
    if (lines >= size)
    {
        // Redimensionar o array se necessário
        dataBase *newGames = new dataBase[size + 10];
        for (int i = 0; i < size; i++)
        {
            newGames[i] = games[i];
        }
        delete[] games;
        games = newGames;
        size += 10;
    }

    dataBase newGame;

    // cout << lines << endl;

    cout << "--------- MENU DE CADASTRO ---------";

    cout << "Digite o ID do jogo: ";
    cin >> newGame.id;
    cout << endl;

    cout << "Digite o nome do jogo: ";
    cin >> newGame.name;
    cout << endl;

    cout << "Digite o ano de lançamento do jogo: ";
    cin >> newGame.age;
    cout << endl;

    cout << "Digite a(s) plataforma(s) em que o jogo foi lançado: ";
    cin >> newGame.platform;
    cout << endl;

    cout << "Digite uma breve descrição sobre o jogo: ";
    cin >> newGame.description;
    cout << endl;

    games[lines] = newGame;

    lines++;

    cout << "O jogo foi adicionado com sucesso" << endl;

    return "";
}

int main()
{
    setlocale(LC_ALL, "UTF-8");

    int lines = 0, size = 40;

    dataBase *games = new dataBase[size];

    load(games, size, lines);

    int option = 0;
    while (option != 6)
    {
        cout << "--------- MENU PRINCIPAL ---------" << endl;
        cout << endl;
        cout << "[1] - Cadastro de jogos" << endl;
        cout << "[2] - Consulta de jogos" << endl;
        cout << "[3] - Ordernar a lista de jogos" << endl;
        cout << "[4] - Excluir jogo" << endl;
        cout << "[5] - Salvar as alterações" << endl;
        cout << "[6] - Sair" << endl;
        cout << endl;
        cout << "Escolha uma opção: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case 1:
            cout << add(games, size, lines) << endl;
            break;
        case 2:
            cout << search(games, lines) << endl;
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
            cout << endl;
            break;
        default:
            cout << "Digite uma opcao valida" << endl;
            cout << endl;
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