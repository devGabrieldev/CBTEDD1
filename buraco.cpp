#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

//gerar as cartas dos baralhos
void gerarBaralho(std::vector<std::string>& baralho) {
    int naipe, numero, baralhoIndex;
    for (baralhoIndex = 0; baralhoIndex < 2; ++baralhoIndex) {  // Para 2 baralhos
        for (naipe = 1; naipe <= 4; ++naipe) {  // Para cada naipe (1-4)
            for (numero = 1; numero <= 13; ++numero) {  // Para cada número (1-13)
                std::string carta = std::to_string(naipe) + "-" + (numero < 10 ? "0" : "") + std::to_string(numero) + "-" + std::to_string(baralhoIndex + 1);
                baralho.push_back(carta);
            }
        }
    }
}

//embaralhar
void embaralhar(std::vector<std::string>& baralho) {
    std::random_shuffle(baralho.begin(), baralho.end());
}

//distribuir as cartas
void distribuir(std::vector<std::string>& baralho, std::vector<std::vector<std::string>>& mao) {
    int cartaIndex = 0;
    for (int jogador = 0; jogador < 4; ++jogador) {
        for (int carta = 0; carta < 11; ++carta) {
            mao[jogador].push_back(baralho[cartaIndex++]);
        }
    }
}

//imprimir mãos dos jogadores
void Maos(const std::vector<std::vector<std::string>>& mao) {
    for (int jogador = 0; jogador < 4; ++jogador) {
        std::cout << "Mão do Jogador " << jogador + 1 << ":\n";
        for (int carta = 0; carta < 11; ++carta) {
            std::cout << mao[jogador][carta] << " ";
        }
        std::cout << "\n\n";
    }
}

int main() {
    // Inicializa o gerador de números aleatórios
    std::srand(std::time(0));

    // Cria o baralho
    std::vector<std::string> baralho;
    gerarBaralho(baralho);

    // Embaralha o baralho
    embaralhar(baralho);

    // Cria a estrutura para armazenar as mãos dos jogadores
    std::vector<std::vector<std::string>> mao(4);

    // Distribui as cartas entre os jogadores
    distribuir(baralho, mao);

    // Imprime as mãos de cada jogador
    Maos(mao);

    return 0;
}
