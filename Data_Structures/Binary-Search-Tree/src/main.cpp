#include"ABB.hpp"

int main(int argc, char *argv[]){
    string arquivo_arvore, arquivo_comandos;
    stringstream ss;

    if(argc != 3){
        cerr << "Por favor execute da seguinte forma:\n" << endl;
        cerr << "./executavel arquivo_arvore arquivo_comandos\n" << endl;
        cerr << "arquivo_arvore: arquivo com a entrada da arvore" << endl;
        cerr << "arquivo_comandos: arquivo com os comandos" << endl;
        return 1;
    }else{
        ss << argv[1];
        ss >> arquivo_arvore;

        ss.str("");
        ss.clear();

        ss << argv[2];
        ss >> arquivo_comandos;

        ss.str("");
        ss.clear();
    }
    ABB arvore;
    ifstream arquivo;
    string s;
    int N;

    arquivo.open(arquivo_arvore);
    if(arquivo.is_open()){
        while(!arquivo.eof()){
            getline(arquivo, s);
            ss.clear();
            ss.str(s);

            while(!ss.eof()){
                ss >> N;
                arvore.inserir(N);
            }
        }
        arquivo.close();
    }

    arquivo.open(arquivo_comandos);
    if (arquivo.is_open()){
      while(!arquivo.eof()){
        getline(arquivo,s);
        ss.clear();
        ss.str(s);
        while(!ss.eof()){
            if(ss.str() == "") break;

            s.clear();
            ss >> s;

            if(s == "ENESIMO"){
                ss >> N;
                cout << arvore.enesimo_elemento(N) << endl;
            }else if(s == "POSICAO"){
                ss >> N;
                cout << arvore.posicao(N) << endl;
            }else if(s == "REMOVA"){
                ss >> N;
                arvore.remover(N);
                // if(arvore.remover(N)) cout << "No removido\n";
                // else cout << "No nao removido\n";
            }else if(s == "INSIRA"){
                ss >> N;
                arvore.inserir(N);
                // if(arvore.inserir(N)) cout << "No inserido\n";
                // else cout << "No nao inserido\n";
            }else if(s == "MEDIANA"){
                cout << arvore.mediana() << endl;
            }else if(s == "CHEIA"){
                if(arvore.eh_cheia()) cout << "Arvore eh cheia\n";
                else cout << "Arvore nao eh cheia\n";
            }else if(s == "COMPLETA"){
                if(arvore.eh_completa()) cout << "Arvore eh completa\n";
                else cout << "Arvore nao eh completa\n";
            }else if(s == "IMPRIMA"){
                cout << arvore.to_string() << endl;
            }else{
                cout << arvore.tamanho() << endl;
                cout << arvore.altura() << endl;
                cout << "Instrucao nao esperada\n";
            }
        }
      }
      arquivo.close();
    }
}
