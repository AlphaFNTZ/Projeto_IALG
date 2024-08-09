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
    string date;
    string category;
    string creator;
    bool available;
};

// Função para trocar dois elementos
void swap(dataBase &x, dataBase &y)
{
    dataBase temp = x;
    x = y;
    y = temp;
}

// Função de particionamento do Quick Sort para o ID
int partitionId(dataBase *games, int low, int high, bool order)
{
    int pivot = games[high].id;
    int i = (low - 1);

    if (order == true)
    {
        for (int j = low; j < high; j++)
        {
            if (games[j].id < pivot)
            {
                i++;
                swap(games[i], games[j]);
            }
        }
    }
    else
    {
        for (int j = low; j < high; j++)
        {
            if (games[j].id > pivot)
            {
                i++;
                swap(games[i], games[j]);
            }
        }
    }

    swap(games[i + 1], games[high]);

    return (i + 1);
}

// Função de particionamento do Quick Sort para o nome
int partitionName(dataBase *games, int low, int high, bool order)
{
    string pivot = games[high].name;
    int i = (low - 1);

    if (order == true)
    {
        for (int j = low; j < high; j++)
        {
            if (games[j].name < pivot)
            {
                i++;
                swap(games[i], games[j]);
            }
        }
    }
    else
    {
        for (int j = low; j < high; j++)
        {
            if (games[j].name > pivot)
            {
                i++;
                swap(games[i], games[j]);
            }
        }
    }

    swap(games[i + 1], games[high]);

    return (i + 1);
}

// Função de ordenação Quick Sort para o nome e o ID
void quickSort(dataBase *games, int low, int high, bool order, string type)
{
    if (low < high)
    {
        if (type == "id")
        {
            int pi = partitionId(games, low, high, order);
            quickSort(games, low, pi - 1, order, type);
            quickSort(games, pi + 1, high, order, type);
        }
        else
        {
            int pi = partitionName(games, low, high, order);
            quickSort(games, low, pi - 1, order, type);
            quickSort(games, pi + 1, high, order, type);
        }
    }
}

void loadFromCsv(dataBase *&games, int &size, int &lines)
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
        games[lines].date = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        // cout << "Verificando plataforma..." << endl;

        location = line.find(';');
        games[lines].category = line.substr(0, location);
        line = line.substr(location + 1, line.length());

        // cout << "Verificando descrição..." << endl;

        location = line.find(';');
        games[lines].creator = line.substr(0, location);
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

    inputFile.close();

    cout << endl;
    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "Pre-leitura do arquivo concluida com sucesso" << endl;
    cout << endl;
}

void loadFromBinary(dataBase *&games, int &size, int &lines)
{
    ifstream inputFile("Banco_de_dados.bin", ios::binary);

    if (!inputFile)
    {
        cerr << "Erro ao abrir o arquivo binario." << endl;
        return;
    }

    while (inputFile.peek() != EOF) // Verifica se chegou ao fim do arquivo
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

        // Leitura do ID
        inputFile.read(reinterpret_cast<char *>(&games[lines].id), sizeof(games[lines].id));

        // Leitura do nome
        int stringSize;
        inputFile.read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));
        games[lines].name.resize(stringSize);
        inputFile.read(&games[lines].name[0], stringSize);

        // Leitura da data
        inputFile.read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));
        games[lines].date.resize(stringSize);
        inputFile.read(&games[lines].date[0], stringSize);

        // Leitura da categoria
        inputFile.read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));
        games[lines].category.resize(stringSize);
        inputFile.read(&games[lines].category[0], stringSize);

        // Leitura do criador
        inputFile.read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));
        games[lines].creator.resize(stringSize);
        inputFile.read(&games[lines].creator[0], stringSize);

        // Leitura da disponibilidade
        inputFile.read(reinterpret_cast<char *>(&games[lines].available), sizeof(games[lines].available));

        lines++;
    }

    inputFile.close();

    cout << endl;
    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "Pre-leitura do arquivo binario concluida com sucesso" << endl;
    cout << endl;
}

void saveToCsv(dataBase *games, int lines)
{

    ofstream outputFile("Banco_de_dados.csv");

    if (!outputFile)
    {
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        cout << endl;
        return;
    }

    // Escrever cabeçalho se necessário
    outputFile << '"' << "Id;Nome;Data;Categoria;Criadora;Disponibilidade" << '"' << endl;

    for (int i = 0; i < lines; i++)
    {
        outputFile << '"' << games[i].id << ";" << games[i].name << ";" << games[i].date << ";" << games[i].category << ";" << games[i].creator << ";" << (games[i].available ? "true" : "false") << '"' << endl;
    }

    outputFile.close();

    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "Dados salvos com sucesso no arquivo" << endl;
    cout << endl;
}

void saveToBinary(dataBase *games, int size)
{
    ofstream outputFile("Banco_de_dados.bin", ios::binary);

    if (!outputFile)
    {
        cerr << "Erro ao abrir o arquivo binario para escrita." << endl;
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        outputFile.write(reinterpret_cast<char *>(&games[i]), sizeof(dataBase));
    }

    outputFile.close();
    cout << "Dados salvos em formato binario com sucesso no arquivo: Banco_de_dados.bin" << endl;
    cout << endl;
}

void ordination(dataBase *&games, int lines)
{
    int option = 0;

    cout << "-------- MENU DE ORDENACAO --------" << endl;
    cout << endl;
    cout << "[1] - Ordenar por ID em ordem crescente" << endl;
    cout << "[2] - Ordenar por ID em ordem decrescente" << endl;
    cout << "[3] - Ordenar por nome em ordem crescente" << endl;
    cout << "[4] - Ordenar por nome em ordem decrescente" << endl;
    cout << "[5] - Sair" << endl;
    cout << endl;
    cout << "Escolha uma opcao: ";
    cin >> option;
    cout << endl;
    switch (option)
    {
    case 1:
        quickSort(games, 0, lines - 1, true, "id");
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Ordenacao por ID crescente concluida" << endl;
        cout << endl;
        break;
    case 2:
        quickSort(games, 0, lines - 1, false, "id");
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Ordenacao por ID decrescente concluida" << endl;
        cout << endl;
        break;
    case 3:
        quickSort(games, 0, lines - 1, true, "name");
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Ordenacao por nome crescente concluida" << endl;
        cout << endl;
        break;
    case 4:
        quickSort(games, 0, lines - 1, false, "name");
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Ordenacao por nome decrescente concluida" << endl;
        cout << endl;
        break;
    case 5:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Retornado ao menu pricipal" << endl;
        cout << endl;
        break;
    default:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Numero de opcao invalida" << endl;
        cout << endl;
        break;
    }
}

void search(dataBase *games, int lines)
{
    int option = 0, idSearch = 0, error = 0, start = 0, end = 0;
    string nameSearch = "";

    int left = 0;
    int right = (lines - 1);
    bool found = false;

    cout << "----------- MENU DE PESQUISA -----------" << endl;
    cout << endl;

    cout << "[1] - Pequisar atraves do ID" << endl;
    cout << "[2] - Pequisar atraves do Nome" << endl;
    cout << "[3] - Pequisar atraves de um intervalo entre linhas" << endl;
    cout << "[4] - Listar todos os jogos" << endl;
    cout << "[5] - Sair" << endl;
    cout << endl;
    cout << "Escolha uma opcao: ";
    cin >> option;
    cout << endl;

    switch (option)
    {
    case 1:
        /*cout << "Digite o ID do jogo: ";
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
                cout << "Data de lancamento: " << games[i].date << endl;
                cout << "Categoria: " << games[i].category << endl;
                cout << "Desenvolvedor: " << games[i].creator << endl;
                cout << endl;
            }
            else
            {
                error++;
            }
        }
        if (error == lines)
        {
            cout << "O jogo com o ID " << idSearch << " nao esta cadastrado" << endl;
        }
        error = 0;*/

        cout << "Digite o ID do jogo: ";
        cin >> idSearch;
        cout << endl;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (games[mid].id == idSearch)
            {
                if (games[mid].available)
                {
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "ID do jogo: " << games[mid].id << endl;
                    cout << "Nome do jogo: " << games[mid].name << endl;
                    cout << "Data de lancamento: " << games[mid].date << endl;
                    cout << "Categoria: " << games[mid].category << endl;
                    cout << "Desenvolvedor: " << games[mid].creator << endl;
                    cout << endl;
                }
                else
                {
                    cout << "O jogo com o ID " << idSearch << " nao esta disponivel" << endl;
                }
                found = true;
                break;
            }
            else if (games[mid].id < idSearch)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        if (found == false)
        {
            cout << "O jogo com o ID " << idSearch << " nao esta cadastrado" << endl;
        }

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
                cout << "Data de lancamento: " << games[i].date << endl;
                cout << "Categoria: " << games[i].category << endl;
                cout << "Desenvolvedor: " << games[i].creator << endl;
                cout << endl;
            }
            else
            {
                error++;
            }
        }
        if (error == lines)
        {
            cout << "O jogo com o nome " << nameSearch << " não esta cadastrado" << endl;
        }
        error = 0;
        break;
    case 3:
        cout << "----------- MENU DE PESQUISA -----------" << endl;
        cout << endl;

        cout << "Requer dois numeros indicando o inicio e o fim do intervalo dentro da lista" << endl;
        cout << endl;
        cout << "Digite o primeiro numero: ";
        cin >> start;
        cout << endl;
        cout << "Digite o segundo numero: ";
        cin >> end;
        cout << endl;

        if (start < 0 || start > lines)
        {
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "O primeiro numero nao tem uma linha correspondente" << endl;
            break;
        }

        if (end < 0 || end > lines)
        {
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "O segundo numero nao tem um linha correspondente" << endl;
            break;
        }

        if (start < end)
        {
            for (int i = (start - 1); i < end; i++)
            {
                if (games[i].available == true)
                {
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "ID do jogo: " << games[i].id << endl;
                    cout << "Nome do jogo: " << games[i].name << endl;
                    cout << "Data de lancamento: " << games[i].date << endl;
                    cout << "Categoria: " << games[i].category << endl;
                    cout << "Desenvolvedor: " << games[i].creator << endl;
                    cout << endl;
                }
            }
        }
        else if (end < start)
        {
            for (int i = (end - 1); i < start; i++)
            {
                if (games[i].available == true)
                {
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "ID do jogo: " << games[i].id << endl;
                    cout << "Nome do jogo: " << games[i].name << endl;
                    cout << "Data de lancamento: " << games[i].date << endl;
                    cout << "Categoria: " << games[i].category << endl;
                    cout << "Desenvolvedor: " << games[i].creator << endl;
                    cout << endl;
                }
            }
        }
        else
        {
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "Os numero digitados nao corresponde a um intervalo valido" << endl;
        }
        break;
    case 4:
        for (int i = 0; i < lines; i++)
        {
            if (games[i].available == true)
            {
                cout << "------------------------------------" << endl;
                cout << endl;
                cout << "ID do jogo: " << games[i].id << endl;
                cout << "Nome do jogo: " << games[i].name << endl;
                cout << "Data de lancamento: " << games[i].date << endl;
                cout << "Categoria: " << games[i].category << endl;
                cout << "Desenvolvedor: " << games[i].creator << endl;
                cout << endl;
            }
        }
        break;
    case 5:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Retornado ao menu pricipal" << endl;
        cout << endl;
        break;
    default:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Numero de opcao invalida" << endl;
        cout << endl;
        break;
    }
}

void add(dataBase *&games, int &size, int &lines)
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

    newGame.id = (lines + 1);

    cout << "Digite o nome do jogo: ";
    cin.ignore();
    getline(cin, newGame.name);
    cout << endl;

    cout << "Digite a data de lancamento do jogo: ";
    cin >> newGame.date;
    cout << endl;

    cout << "Digite a categoria do jogo: ";
    cin.ignore();
    getline(cin, newGame.category);
    cout << endl;

    cout << "Digite a desenvolvedora do jogo: ";
    getline(cin, newGame.creator);
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
        cout << "O jogo com o nome (" << newGame.name << ") ja foi cadastrado" << endl;
    }
    else
    {
        games[lines] = newGame;
        lines++;
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "O jogo foi adicionado com sucesso" << endl;
    }
}

void deleted(dataBase *&games, int lines)
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
        }
        else if (games[i].id == deleted && games[i].available == false)
        {
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "O jogo com o ID " << deleted << " ja foi apagado" << endl;
        }
        else
        {
            nonexistent++;
        }
    }

    if (nonexistent == lines)
    {
        cout << "O jogo com o ID " << deleted << " nao foi encontrado" << endl;
    }
}

void edit(dataBase *&games, int lines)
{
    int option = 0, idSearch = 0;
    string nameSearch = "";

    dataBase newData;

    cout << "--------- MENU DE CADASTRO ---------" << endl;
    cout << endl;
    cout << "[1] - Pequisar atraves do ID" << endl;
    cout << "[2] - Pequisar atraves do Nome" << endl;
    cout << "[3] - Sair" << endl;
    cout << endl;
    cout << "Escolha uma opcao: ";
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
                cout << "----- DADOS DO JOGO ESCOLHIDO -----" << endl;
                cout << endl;
                cout << "ID do jogo: " << games[i].id << endl;
                cout << "Nome do jogo: " << games[i].name << endl;
                cout << "Data de lancamento: " << games[i].date << endl;
                cout << "Categoria: " << games[i].category << endl;
                cout << "Desenvolvedor: " << games[i].creator << endl;
                cout << endl;
                cout << "------------------------------------" << endl;
                cout << endl;
                cout << "---------- EDICAO DE DADOS ---------" << endl;
                cout << endl;

                newData.id = games[i].id;

                cout << "Digite o nome do jogo: ";
                cin.ignore();
                getline(cin, newData.name);
                cout << endl;

                cout << "Digite a data de lancamento do jogo: ";
                cin >> newData.date;
                cout << endl;

                cout << "Digite a categoria do jogo: ";
                cin.ignore();
                getline(cin, newData.category);
                cout << endl;

                cout << "Digite a desenvolvedora do jogo: ";
                getline(cin, newData.creator);
                cout << endl;

                newData.available = games[i].available;

                if (games[i].available == false)
                {
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "Esse jogo nao esta disponivel" << endl;
                }
                else
                {
                    games[i] = newData;
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "O jogo foi editado com sucesso" << endl;
                }
            }
        }
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
                cout << "----- DADOS DO JOGO ESCOLHIDO -----" << endl;
                cout << endl;
                cout << "ID do jogo: " << games[i].id << endl;
                cout << "Nome do jogo: " << games[i].name << endl;
                cout << "Data de lancamento: " << games[i].date << endl;
                cout << "Categoria: " << games[i].category << endl;
                cout << "Desenvolvedor: " << games[i].creator << endl;
                cout << endl;
                cout << "------------------------------------" << endl;
                cout << endl;
                cout << "---------- EDICAO DE DADOS ---------" << endl;
                cout << endl;

                newData.id = games[i].id;

                cout << "Digite o nome do jogo: ";
                cin.ignore();
                getline(cin, newData.name);
                cout << endl;

                cout << "Digite a data de lancamento do jogo: ";
                cin >> newData.date;
                cout << endl;

                cout << "Digite a categoria do jogo: ";
                cin.ignore();
                getline(cin, newData.category);
                cout << endl;

                cout << "Digite a desenvolvedora do jogo: ";
                getline(cin, newData.creator);
                cout << endl;

                newData.available = games[i].available;

                if (games[i].available == false)
                {
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "Esse jogo nao esta disponivel" << endl;
                }
                else
                {
                    games[i] = newData;
                    cout << "------------------------------------" << endl;
                    cout << endl;
                    cout << "O jogo foi adicionado com sucesso" << endl;
                }
            }
        }
        break;
    case 3:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Retornado ao menu pricipal" << endl;
        cout << endl;
        break;
    default:
        cout << "------------------------------------" << endl;
        cout << endl;
        cout << "Numero de opcao invalida" << endl;
        cout << endl;
        break;
    }
}

int main()
{
    int lines = 0, size = 40, option = 0;

    dataBase *games = new dataBase[size];

    cout << "------- MENU DE CARREGAMENTO -------" << endl;
    cout << endl;
    cout << "Escolha qual e o formato do arquivo que sera carregado" << endl;
    cout << endl;
    cout << "[1] - Arquivo formato .csv" << endl;
    cout << "[2] - Arquivo formato .bin" << endl;
    cout << endl;
    cout << "Escolha uma opcao: ";
    cin >> option;

    switch (option)
    {
    case 1:
        loadFromCsv(games, size, lines);
        break;
    case 2:
        loadFromBinary(games, size, lines);
        break;
    default:
        break;
    }

    option = 0;

    while (option != 8)
    {
        cout << "---------- MENU PRINCIPAL ----------" << endl;
        cout << endl;
        cout << "[1] - Cadastro de jogos" << endl;
        cout << "[2] - Editar cadastro de jogos" << endl;
        cout << "[3] - Consulta de jogos" << endl;
        cout << "[4] - Ordernar a lista de jogos" << endl;
        cout << "[5] - Excluir jogo" << endl;
        cout << "[6] - Salvar as alteracoes como .CSV" << endl;
        cout << "[7] - Salvar as alteracoes como .BIN" << endl;
        cout << "[8] - Sair" << endl;
        cout << endl;
        cout << "Escolha uma opcao: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case 1:
            add(games, size, lines);
            cout << endl;
            break;
        case 2:
            edit(games, lines);
            cout << endl;
            break;
        case 3:
            search(games, lines);
            cout << endl;
            break;
        case 4:
            ordination(games, lines);
            break;
        case 5:
            deleted(games, lines);
            cout << endl;
            break;
        case 6:
            saveToCsv(games, lines);
            break;
        case 7:
            saveToBinary(games, lines);
            break;
        case 8:
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "Encerrando sistema..." << endl;
            cout << endl;
            break;
        default:
            cout << "------------------------------------" << endl;
            cout << endl;
            cout << "Numero de opcao invalida" << endl;
            cout << endl;
            break;
        }
    }

    delete[] games;

    return 0;
}