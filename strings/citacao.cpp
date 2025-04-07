#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype> 

std::string transformarParaCitacaoBibliografica(const std::string& nomeCompleto) {
    std::stringstream ss(nomeCompleto);
    std::string palavra;
    std::vector<std::string> nomes;
    
    // Separar o nome completo em partes
    while (ss >> palavra) {
        nomes.push_back(palavra);
    }

    // O sobrenome é o último nome
    if (nomes.size() > 1) {
        std::string sobrenome = nomes.back();
        nomes.pop_back(); // Remove o sobrenome da lista

        // Coloca o sobrenome em maiúsculas
        for (size_t i = 0; i < sobrenome.size(); ++i) {
            sobrenome[i] = std::toupper(sobrenome[i]);  // Converte cada letra do sobrenome para maiúscula
        }

        // Agora, pegamos as iniciais dos outros nomes
        std::string citacao = sobrenome + ", ";
        for (size_t i = 0; i < nomes.size(); ++i) {
            citacao += nomes[i].substr(0, 1) + ". ";  // Pega a primeira letra de cada nome e coloca um ponto após

            if (i != nomes.size() - 1) {
                citacao += " ";  // Adiciona um espaço entre as iniciais
            }
        }

        // Remover o último espaço extra manualmente
        if (!citacao.empty()) {
            // Remove o espaço extra no final
            if (citacao[citacao.length() - 1] == ' ') {
                citacao = citacao.substr(0, citacao.length() - 1);
            }
        }

        return citacao;
    }

    return nomeCompleto;  // Caso o nome não tenha sobrenome, retornamos o nome original
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
        std::string citacao = transformarParaCitacaoBibliografica(nome);
        std::cout << citacao << std::endl;
    }

    arquivo.close();
    return 0;
}
