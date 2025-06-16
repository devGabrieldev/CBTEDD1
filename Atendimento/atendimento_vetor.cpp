#include <iostream>
#define TAM_MAX 100

using namespace std;

struct Fila {
    int dados[TAM_MAX];
    int inicio = 0;
    int fim = 0;
    int tamanho = 0;
};

bool filaVazia(Fila& fila) {
    return fila.tamanho == 0;
}

bool filaCheia(Fila& fila) {
    return fila.tamanho == TAM_MAX;
}

bool enfileirar(Fila& fila, int valor) {
    if (filaCheia(fila)) return false;
    fila.dados[fila.fim] = valor;
    fila.fim = (fila.fim + 1) % TAM_MAX;
    fila.tamanho++;
    return true;
}

bool desenfileirar(Fila& fila, int& valor) {
    if (filaVazia(fila)) return false;
    valor = fila.dados[fila.inicio];
    fila.inicio = (fila.inicio + 1) % TAM_MAX;
    fila.tamanho--;
    return true;
}

int main() {
    Fila senhasGeradas, senhasAtendidas;
    int senhaAtual = 1, opcao;

    do {
        cout << "\n=== SISTEMA DE ATENDIMENTO ===" << endl;
        cout << "0. Sair\n1. Gerar senha\n2. Realizar atendimento\n";
        cout << "Senhas aguardando: " << senhasGeradas.tamanho << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                if (!filaVazia(senhasGeradas))
                    cout << "Ainda ha senhas aguardando atendimento.\n";
                break;
            case 1:
                if (enfileirar(senhasGeradas, senhaAtual))
                    cout << "Senha " << senhaAtual++ << " gerada.\n";
                else
                    cout << "Fila cheia.\n";
                break;
            case 2: {
                int senha;
                if (desenfileirar(senhasGeradas, senha)) {
                    cout << "Atendendo senha: " << senha << endl;
                    enfileirar(senhasAtendidas, senha);
                } else
                    cout << "Nenhuma senha para atender.\n";
                break;
            }
            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0 || !filaVazia(senhasGeradas));

    cout << "\nSistema encerrado. Total atendidas: " << senhasAtendidas.tamanho << endl;
    return 0;
}
