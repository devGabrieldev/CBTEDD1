#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::string transformarNomeParaAgenda(const std::string& nomeCompleto) {
    std::stringstream ss(nomeCompleto);
    std::string palavra;
    std::vector<std::string> nomes;
    
    // Separar o nome completo em partes
    while (ss >> palavra) {
        nomes.push_back(palavra);
    }

    // O sobrenome está no final e o primeiro nome no início
    if (nomes.size() > 1) {
        std::string sobrenome = nomes.back();
        nomes.pop_back(); // Remove o sobrenome da lista
        
        // O nome completo (sem o sobrenome) vai na frente
        std::string nomeFormatado = sobrenome + ", ";
        for (size_t i = 0; i < nomes.size(); ++i) {
            nomeFormatado += nomes[i];
            if (i != nomes.size() - 1) {
                nomeFormatado += " ";
            }
        }

        return nomeFormatado;
    }

    return nomeCompleto; // Caso não haja sobrenome, retorna o nome original
}

int main() {
    std::string caminhoArquivo;
    
    std::cout << "Digite o caminho do arquivo de nomes: ";
    std::getline(std::cin, caminhoArquivo);
   
    std::ifstream arquivo(caminhoArquivo.c_str());  // Usando c_str() para passar como const char*
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo. Verifique o caminho e tente novamente." << std::endl;
        return 1;
    }

    std::string nome;
    while (std::getline(arquivo, nome)) {        
        std::string nomeAgenda = transformarNomeParaAgenda(nome);
        std::cout << nomeAgenda << std::endl;
    }

    arquivo.close();
    return 0;
}
