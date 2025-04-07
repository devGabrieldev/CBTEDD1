#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <cctype>

//remover acentos do texto
std::string removerAcentos(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_str = converter.from_bytes(str);
    std::wstring result;
    for (wchar_t wc : wide_str) {
        if (wc >= 0x00C0 && wc <= 0x00FF) {
            // Remover os acentos, ou seja, ignorar os caracteres acentuados
            if (wc == L'á' || wc == L'à' || wc == L'ã' || wc == L'ä' || wc == L'â') wc = L'a';
            if (wc == L'é' || wc == L'è' || wc == L'ê' || wc == L'ë') wc = L'e';
            if (wc == L'í' || wc == L'ì' || wc == L'î' || wc == L'ï') wc = L'i';
            if (wc == L'ó' || wc == L'ò' || wc == L'ô' || wc == L'õ' || wc == L'ö') wc = L'o';
            if (wc == L'ú' || wc == L'ù' || wc == L'û' || wc == L'ü') wc = L'u';
            if (wc == L'ç') wc = L'c';
        }
        result += wc;
    }
    
    return converter.to_bytes(result);
}

//verifica se é um palíndromo
bool verificaPalindromo(std::string mensagem) {
    // Remover espaços
    mensagem.erase(std::remove(mensagem.begin(), mensagem.end(), ' '), mensagem.end());
    
    // Remove acentos
    mensagem = removerAcentos(mensagem);
    
    // Converte os caracteres para minúsculos
    std::transform(mensagem.begin(), mensagem.end(), mensagem.begin(), ::tolower);

    // Criar uma cópia e inverter
    std::string mensagemInvertida = mensagem;
    std::reverse(mensagemInvertida.begin(), mensagemInvertida.end());

    // Comparar original e invertida
    return mensagem == mensagemInvertida;
}

int main() {
    std::string mensagem;
    std::cout << "Digite uma mensagem: ";
    std::getline(std::cin, mensagem);

    if (verificaPalindromo(mensagem)) {
        std::cout << "\n A mensagem é um palíndromo!" << std::endl;
    } else {
        std::cout << "\n A mensagem não é um palíndromo." << std::endl;
    }

    return 0;
}
