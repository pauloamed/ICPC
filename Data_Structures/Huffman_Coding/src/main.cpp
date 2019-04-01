#include"Huffman.hpp"

int main(int argc, char *argv[]){
    std::string arg, file_name;
    if(argc != 3){ // se a quantidade de argumentos for diferente de 2 apresentará um erro
        std::cerr << "ERROR 1: Argument count is not 2! Execute:\nhuffman {-c or -u} file_name\n";
        return 1;
    }else{
        arg = argv[1];
        file_name = argv[2];
        // se for a quantidade certa, fará a verificação dos argumentos, se foi inserido de forma correta
        if(arg != "-u" && arg != "-c"){ // se for inserido argumentos diferentes do esperado
            if(file_name != "-u" && file_name != "-c"){ // apresentará um erro para os dois argumentos invalidos
                std::cerr << "ERROR 2: Arguments are invalid\n";
                return 1;
            }else{ // se forem validos mas nao estiverem em ordem correta, fará uma troca na posiçao dos argumentos
                swap(arg, file_name);
            }
        }
    }

    if(arg == "-c"){ // Comprimir
        Huffman huffman(file_name, false);
        huffman.compress(file_name);
    }else{ // Descomprimir
        Huffman huffman(file_name, true);
        huffman.uncompress(file_name);
    }
}
