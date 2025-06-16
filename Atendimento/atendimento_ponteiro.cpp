#include <iostream>
#include <cstdlib>

using namespace std;

struct No {
    int valor;
    No* proximo;
};

struct Fila {
    No* inicio = nullptr;
    No* fim = nullptr;
    int tamanho = 0;
};

bool filaVazia(Fila* fila) {
    return fila->inicio == nullptr;
}

void enfileirar(Fila* fila, int valor) {
    No* novo = new No{valor, nullptr};
    if (filaVazia(fila)) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

bool desenfileirar(Fila* fila, int* valor) {
    if (filaVazia(fila)) return false;

    No* temp = fila->inicio;
    *valor = temp->valor;
    fila->inicio = temp->proximo;
    delete temp;

    if (fila->inicio == nullptr) fila->fim = nullptr;
    fila->tamanho--;
    return true;
}

void liberarFila(Fila* fila) {
    int valor;
    while (desenfileirar(fila, &valor));
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
                if (!filaVazia(&senhasGeradas))
                    cout << "Ainda ha senhas aguardando atendimento.\n";
                break;
            case 1:
                enfileirar(&senhasGeradas, senhaAtual++);
                cout << "Senha gerada.\n";
                break;
            case 2: {
                int senha;
                if (desenfileirar(&senhasGeradas, &senha)) {
                    cout << "Atendendo senha: " << senha << endl;
                    enfileirar(&senhasAtendidas, senha);
                } else
                    cout << "Nenhuma senha para atender.\n";
                break;
            }
            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0 || !filaVazia(&senhasGeradas));

    cout << "\nSistema encerrado. Total atendidas: " << senhasAtendidas.tamanho << endl;

    liberarFila(&senhasGeradas);
    liberarFila(&senhasAtendidas);

    return 0;
}
