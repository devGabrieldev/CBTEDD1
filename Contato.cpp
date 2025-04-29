#include <iostream>
#include <string>
#include <ctime>                       
#include <cstdio>    
#include <sstream>

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

    std::string getData() const {
        char buffer[11];
        sprintf(buffer, "%02d/%02d/%04d", dia, mes, ano);
        return std::string(buffer);
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
    Contato() : email(""), nome(""), telefone(""), dtnasc() { }

    Contato(string nome, string email, string telefone, const Data& dtnasc)
        : nome(nome), email(email), telefone(telefone), dtnasc(dtnasc) { }

    void setNome(string nome) { this->nome = nome; }
    void setEmail(string email) { this->email = email; }
    void setTelefone(string telefone) { this->telefone = telefone; }
    void setDtnasc(const Data& dtnasc) { this->dtnasc = dtnasc; }

    string getNome() const { return nome; }
    string getEmail() const { return email; }
    string getTelefone() const { return telefone; }
    Data getDtnasc() const { return dtnasc; }
};

int main() {
    Contato contatos[5];
    for (int i = 0; i < 5; i++) {
        string nome, email, telefone;
        int dia, mes, ano;

        cout << "Cadastro do contato #" << (i + 1) << endl;
        cout << "Nome: ";
        getline(cin, nome);
        cout << "Email: ";
        getline(cin, email);
        cout << "Telefone: ";
        getline(cin, telefone);
        cout << "Data de nascimento (dd/mm/aaaa): ";
		string dataNascStr;
		getline(cin, dataNascStr);		
		char barra1, barra2;
		stringstream ss(dataNascStr);
		ss >> dia >> barra1 >> mes >> barra2 >> ano;
        
        

        Data dataNasc(dia, mes, ano);
        contatos[i] = Contato(nome, email, telefone, dataNasc);

        cout << endl;
    }

    cout << "Contatos cadastrados:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Contato #" << (i + 1) << ":" << endl;
        cout << "Nome: " << contatos[i].getNome() << endl;
        cout << "Email: " << contatos[i].getEmail() << endl;
        cout << "Telefone: " << contatos[i].getTelefone() << endl;
        cout << "Idade: " << contatos[i].getDtnasc().calcularIdade() << " anos" << endl;
        cout << endl;
    }

    return 0;
}
