#include <iostream>
#include <cstdlib>

using namespace std;

struct No {
    int valor;
    No* proximo;
};

struct Fila {
    No* inicio;
    No* fim;
    int tamanho;

    Fila() {
        inicio = NULL;
        fim = NULL;
        tamanho = 0;
    }
};

bool filaVazia(Fila* fila) {
    return fila->inicio == NULL;
}

void enfileirar(Fila* fila, int valor) {
    No* novo = new No;
    novo->valor = valor;
    novo->proximo = NULL;

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

    if (fila->inicio == NULL) fila->fim = NULL;
    fila->tamanho--;
    return true;
}

void liberarFila(Fila* fila) {
    int valor;
    while (desenfileirar(fila, &valor));
}

struct Guiche {
    int id;
    Fila senhasAtendidas;
    Guiche* proximo;

    Guiche(int idGuiche) {
        id = idGuiche;
        proximo = NULL;
    }
};

struct ListaGuiches {
    Guiche* inicio;
    int quantidade;

    ListaGuiches() {
        inicio = NULL;
        quantidade = 0;
    }
};

Guiche* encontrarGuiche(ListaGuiches* lista, int id) {
    Guiche* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void adicionarGuiche(ListaGuiches* lista, int id) {
    if (encontrarGuiche(lista, id)) {
        cout << "Guich� com ID " << id << " j� existe.\n";
        return;
    }
    Guiche* novo = new Guiche(id);
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->quantidade++;
    cout << "Guich� " << id << " aberto com sucesso.\n";
}

void listarSenhasGuiche(Guiche* guiche) {
    No* atual = guiche->senhasAtendidas.inicio;
    if (atual == NULL) {
        cout << "Nenhuma senha foi atendida por este guich�.\n";
        return;
    }
    cout << "Senhas atendidas pelo guich� " << guiche->id << ": ";
    while (atual != NULL) {
        cout << atual->valor << " ";
        atual = atual->proximo;
    }
    cout << endl;
}

int main() {
    Fila senhasGeradas;
    ListaGuiches guiches;
    int senhaAtual = 1, opcao;

    do {
        cout << "\n=== SISTEMA DE ATENDIMENTO ===\n";
        cout << "0. Sair\n";
        cout << "1. Gerar senha\n";
        cout << "2. Abrir guich�\n";
        cout << "3. Realizar atendimento\n";
        cout << "4. Listar senhas atendidas\n";
        cout << "Senhas aguardando: " << senhasGeradas.tamanho
             << " | Guich�s abertos: " << guiches.quantidade << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                if (!filaVazia(&senhasGeradas)) {
                    cout << "Ainda h� senhas aguardando atendimento.\n";
                    opcao = -1; // impede sair
                }
                break;
            case 1:
                enfileirar(&senhasGeradas, senhaAtual++);
                cout << "Senha gerada.\n";
                break;
            case 2: {
                int id;
                cout << "Digite o ID do novo guich�: ";
                cin >> id;
                adicionarGuiche(&guiches, id);
                break;
            }
            case 3: {
                if (filaVazia(&senhasGeradas)) {
                    cout << "Nenhuma senha para atender.\n";
                    break;
                }
                int id;
                cout << "Digite o ID do guich� que ir� atender: ";
                cin >> id;
                Guiche* guiche = encontrarGuiche(&guiches, id);
                if (guiche == NULL) {
                    cout << "Guich� n�o encontrado.\n";
                    break;
                }
                int senha;
                if (desenfileirar(&senhasGeradas, &senha)) {
                    cout << "Guich� " << id << " atendendo senha: " << senha << endl;
                    enfileirar(&guiche->senhasAtendidas, senha);
                }
                break;
            }
            case 4: {
                int id;
                cout << "Digite o ID do guich�: ";
                cin >> id;
                Guiche* guiche = encontrarGuiche(&guiches, id);
                if (guiche == NULL) {
                    cout << "Guich� n�o encontrado.\n";
                    break;
                }
                listarSenhasGuiche(guiche);
                break;
            }
            default:
                cout << "Op��o inv�lida.\n";
        }
    } while (opcao != 0 || !filaVazia(&senhasGeradas));

    int totalAtendidas = 0;
    Guiche* atual = guiches.inicio;
    while (atual != NULL) {
        totalAtendidas += atual->senhasAtendidas.tamanho;
        liberarFila(&atual->senhasAtendidas);
        Guiche* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    liberarFila(&senhasGeradas);

    cout << "\nSistema encerrado. Total de senhas atendidas: " << totalAtendidas << endl;
    return 0;
}
