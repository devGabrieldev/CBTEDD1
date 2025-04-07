#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

void exibirMensagemCascata(const std::string& mensagem) {
    int larguraTela = 80;  
    int linhaInicial = 5;
    int linhaFinal = 20;
    
    //armazena as posições de cada letra
    std::vector<int> posicoes(mensagem.length(), linhaInicial); 

    // Loop para simular as letras "caindo"
    for (int i = linhaInicial; i <= linhaFinal; ++i) {        
        
        // Exibe as letras em suas novas posições
        for (size_t j = 0; j < mensagem.length(); ++j) {
            // Verifica se a letra já chegou na linha final
            if (posicoes[j] < linhaFinal) {
                std::cout << std::string((larguraTela - 1) / 2, ' ')  // Centraliza a letra na tela
                          << mensagem[j] << std::endl;
                
                // Move a letra para a próxima linha
                posicoes[j]++;
            }
        }
                
    }
}

int main() {
    std::string mensagem;
    
    std::cout << "Digite uma mensagem: ";
    std::getline(std::cin, mensagem);  // Recebe a mensagem do usuário
    
    // Exibe a mensagem "caindo"
    exibirMensagemCascata(mensagem);
    
    return 0;
}
