#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data() {
        time_t tempoAtual = time(NULL);
        tm* dataLocal = localtime(&tempoAtual);
        this->dia = dataLocal->tm_mday;
        this->mes = dataLocal->tm_mon + 1;
        this->ano = dataLocal->tm_year + 1900;
    }

    Data(int dia, int mes, int ano) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    }

    void setDia(int dia) { this->dia = dia; }
    void setMes(int mes) { this->mes = mes; }
    void setAno(int ano) { this->ano = ano; }

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }

    string getData() const {
        char buffer[11];
        sprintf(buffer, "%02d/%02d/%04d", dia, mes, ano);
        return string(buffer);
    }

    int calcularIdade() const {
        time_t tempoAtual = time(NULL);
        tm* dataLocal = localtime(&tempoAtual);

        int anoAtual = dataLocal->tm_year + 1900;
        int mesAtual = dataLocal->tm_mon + 1;
        int diaAtual = dataLocal->tm_mday;

        int idade = anoAtual - ano;
        if (mesAtual < mes || (mesAtual == mes && diaAtual < dia)) {
            idade--;
        }
        return idade;
    }
};

class Contato {
private:
    string email;
    string nome;
    string telefone;
    Data dtnasc;

public:
    Contato() : email(""), nome(""), telefone(""), dtnasc() {}

    Contato(string nome, string email, string telefone, const Data& dtnasc)
        : nome(nome), email(email), telefone(telefone), dtnasc(dtnasc) {}

    void setNome(string nome) { this->nome = nome; }
    void setEmail(string email) { this->email = email; }
    void setTelefone(string telefone) { this->telefone = telefone; }
    void setDtnasc(const Data& dtnasc) { this->dtnasc = dtnasc; }

    string getNome() const { return nome; }
    string getEmail() const { return email; }
    string getTelefone() const { return telefone; }
    Data getDtnasc() const { return dtnasc; }

    int getIdade() const { return dtnasc.calcularIdade(); }

    string getNomeCitacaoBibliografica() const {
        stringstream ss(nome);
        vector<string> partes;
        string palavra;

        while (ss >> palavra) {
            partes.push_back(palavra);
        }

        if (partes.empty()) return "";

        string sobrenome = partes.back();
        partes.pop_back();

        string resultado = sobrenome;
        transform(resultado.begin(), resultado.end(), resultado.begin(), ::toupper);
        resultado += ",";

        for (const auto& p : partes) {
            resultado += " " + p;
        }

        return resultado;
    }
};

int main() {
    const int TAM = 10;
    Contato contatos[TAM];
    double somaIdades = 0;
    int maioresDeIdade = 0;
    int idadeMaxima = 0;

    for (int i = 0; i < TAM; i++) {
        string nome, email, telefone, dataNascStr;
        int dia, mes, ano;
        char barra1, barra2;

        cout << "Cadastro do contato #" << (i + 1) << endl;
        cout << "Nome: ";
        getline(cin, nome);
        cout << "Email: ";
        getline(cin, email);
        cout << "Telefone: ";
        getline(cin, telefone);
        cout << "Data de nascimento (dd/mm/aaaa): ";
        getline(cin, dataNascStr);

        stringstream ss(dataNascStr);
        ss >> dia >> barra1 >> mes >> barra2 >> ano;

        Data dataNasc(dia, mes, ano);
        Contato contato(nome, email, telefone, dataNasc);
        contatos[i] = contato;

        int idade = contato.getIdade();
        somaIdades += idade;
        if (idade >= 18) maioresDeIdade++;
        if (idade > idadeMaxima) idadeMaxima = idade;

        cout << endl;
    }

    double mediaIdade = somaIdades / TAM;

    cout << "\n=== Relatório ===" << endl;
    cout << "Média das idades: " << mediaIdade << endl;

    cout << "\nContatos com idade acima da média:" << endl;
    for (int i = 0; i < TAM; i++) {
        if (contatos[i].getIdade() > mediaIdade) {
            cout << "- " << contatos[i].getNomeCitacaoBibliografica() << " (" << contatos[i].getIdade() << " anos)" << endl;
        }
    }

    cout << "\nQuantidade de contatos maiores de idade: " << maioresDeIdade << endl;

    cout << "\nContato(s) mais velho(s):" << endl;
    for (int i = 0; i < TAM; i++) {
        if (contatos[i].getIdade() == idadeMaxima) {
            cout << "- Nome: " << contatos[i].getNomeCitacaoBibliografica() << endl;
            cout << "  Email: " << contatos[i].getEmail() << endl;
            cout << "  Telefone: " << contatos[i].getTelefone() << endl;
        }
    }

    return 0;
}
