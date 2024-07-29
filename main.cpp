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
    bool available;
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

    // while (lines <= 2)
    while (getline(inputFile, line))
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

        location = line.find(';');
        games[lines].description = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        if ((line.substr(0, line.length() - 1)) == "true")
        {
            games[lines].available = true;
        }
        else
        {
            games[lines].available = false;
        }

        lines++;

        // cout << "A linha " << lines << " foi escrita com sucesso" << endl;
        // cout << endl;
    }

    cout << endl;
    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "Pré-leitura do arquivo concluida com sucesso" << endl;
    cout << endl;
}

void save(dataBase *games, int lines)
{
    ofstream outputFile("Banco_de_dados.csv");

    if (!outputFile)
    {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    // Escrever cabeçalho se necessário
    outputFile << '"' << "Identificador;Nome;Ano de lancamento;Plataforma;Descricao;Disponibilidade" << '"' << endl;

    for (int i = 0; i < lines; i++)
    {
        outputFile << '"' << games[i].id << ";" << games[i].name << ";" << games[i].age << ";" << games[i].platform << ";" << games[i].description << ";" << (games[i].available ? "true" : "false") << '"' << endl;
    }

    outputFile.close();

    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "Dados salvos com sucesso no arquivo" << endl;
    cout << endl;
}

string search(dataBase *games, int lines)
{
    int option = 0, idSearch = 0, error = 0;
    string nameSearch = "";

    cout << "----------- MENU DE PESQUISA -----------" << endl;
    cout << endl;

    cout << "[1] - Pequisar atráves do ID" << endl;
    cout << "[2] - Pequisar atráves do Nome" << endl;
    cout << "[3] - Listar todos os jogos" << endl;
    cout << "[4] - Sair" << endl;
    cout << endl;
    cout << "Escolha uma opção: ";
    cin >> option;
    cout << endl;

    switch (option)
    {
    case 1:
        cout << "Digite o ID do jogo: ";
        cin >> idSearch;
        cout << endl;
        for (int i = 0; i < lines; i++)
        {
            if (games[i].available == true && games[i].id == idSearch)
            {
                cout << "------------------------------------" << endl;
                cout << endl;
                cout << "ID do jogo: " << games[i].id << endl;
                cout << "Nome do jogo: " << games[i].name << endl;
                cout << "Ano de lançamento: " << games[i].age << endl;
                cout << "Plataforma de lançamento: " << games[i].platform << endl;
                cout << "Descrição do jogo: " << games[i].description << endl;
                cout << endl;
            }
            else
            {
                error++;
            }
        }
        if (error == lines)
        {
            cout << "O jogo com o ID " << idSearch << " não está cadastrado" << endl;
        }
        error = 0;
        break;
    case 2:
        cout << "Digite o nome do jogo: ";
        cin.ignore();
        getline(cin, nameSearch);
        cout << endl;
        for (int i = 0; i < lines; i++)
        {
            if (games[i].available == true && games[i].name == nameSearch)
            {
                cout << "------------------------------------" << endl;
                cout << endl;
                cout << "ID do jogo: " << games[i].id << endl;
                cout << "Nome do jogo: " << games[i].name << endl;
                cout << "Ano de lançamento: " << games[i].age << endl;
                cout << "Plataforma de lançamento: " << games[i].platform << endl;
                cout << "Descrição do jogo: " << games[i].description << endl;
                cout << endl;
            }
            else
            {
                error++;
            }
        }
        if (error == lines)
        {
            cout << "O jogo com o nome " << nameSearch << " não está cadastrado" << endl;
        }
        error = 0;
        break;
    case 3:
        for (int i = 0; i < lines; i++)
        {
            if (games[i].available == true)
            {
                cout << "------------------------------------" << endl;
                cout << endl;
                cout << "ID do jogo: " << games[i].id << endl;
                cout << "Nome do jogo: " << games[i].name << endl;
                cout << "Ano de lançamento: " << games[i].age << endl;
                cout << "Plataforma de lançamento: " << games[i].platform << endl;
                cout << "Descrição do jogo: " << games[i].description << endl;
                cout << endl;
            }
        }
        break;
    case 4:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Retornado ao menu pricipal" << endl;
        cout << endl;
        break;
    }

    return "";
}

string add(dataBase *&games, int &size, int &lines)
{
    bool equal = false;
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

    cout << "--------- MENU DE CADASTRO ---------" << endl;
    cout << endl;

    // cout << "Digite o ID do jogo: ";
    // cin >> newGame.id;
    // cout << endl;

    newGame.id = (lines + 1);

    cout << "Digite o nome do jogo: ";
    cin.ignore();
    getline(cin, newGame.name);
    cout << endl;

    cout << "Digite o ano de lançamento do jogo: ";
    cin >> newGame.age;
    cout << endl;

    cout << "Digite a(s) plataforma(s) em que o jogo foi lançado: ";
    cin.ignore();
    getline(cin, newGame.platform);
    cout << endl;

    cout << "Digite uma breve descrição sobre o jogo: ";
    getline(cin, newGame.description);
    cout << endl;

    newGame.available = true;

    for (int i = 0; i < lines; i++)
    {
        if (newGame.name == games[i].name && games[i].available == true)
        {
            equal = true;
        }
    }

    if (equal == true)
    {
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "O jogo com o nome (" << newGame.name << ") já foi cadastrado" << endl;
    }
    else
    {
        games[lines] = newGame;
        lines++;
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "O jogo foi adicionado com sucesso" << endl;
    }

    return "";
}

string deleted(dataBase *&games, int lines)
{
    int deleted = 0, nonexistent = 0;

    cout << "--------- MENU DE APAGAR JOGOS ---------" << endl;
    cout << endl;

    cout << "Digite o ID do jogo que deseja apagar: ";
    cin >> deleted;
    cout << endl;

    for (int i = 0; i < lines; i++)
    {
        // cout << games[i].id << endl;
        if (games[i].id == deleted && games[i].available == true)
        {
            games[i].available = false;
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "O jogo com o ID " << deleted << " foi apagado com sucesso" << endl;
            return "";
        }
        else if (games[i].id == deleted && games[i].available == false)
        {
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "O jogo com o ID " << deleted << " já foi apagado" << endl;
            return "";
        }
        else
        {
            nonexistent++;
        }
    }

    if (nonexistent == lines)
    {
        cout << "O jogo com o ID " << deleted << " não foi encontrado" << endl;
        return "";
    }

    return "";
}

int main()
{
    int lines = 0, size = 40;

    dataBase *games = new dataBase[size];

    load(games, size, lines);

    int option = 0;

    setlocale(LC_ALL, "UTF-8");

    while (option != 6)
    {
        cout << "---------- MENU PRINCIPAL ----------" << endl;
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
            cout << deleted(games, lines) << endl;
            break;
        case 5:
            save(games, lines);
            break;
        case 6:
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "Encerrando sistema..." << endl;
            cout << endl;
            break;
        default:
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "Número de opção invalida" << endl;
            cout << endl;
            break;
        }
    }

    return 0;
}