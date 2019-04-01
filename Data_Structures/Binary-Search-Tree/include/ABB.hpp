#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<queue>
#include<math.h>

using namespace std;

class ABB{
public:
    struct no{
        int _chave;
        no* _esq, *_dir;
        size_t _qnt_sub_esq;
        size_t _qnt_sub_dir;

        size_t _altura;

        no(int chave=0):_chave(chave), _esq(nullptr), _dir(nullptr),
                      _qnt_sub_esq(0),_qnt_sub_dir(0),_altura(0){}
    };
private:
    size_t _tamanho;
    size_t _altura;
    no* _no_cabeca;

    void _atualizar_altura(no *atual){
        size_t nova_altura = 0;
        if(atual->_esq != nullptr) nova_altura = max(nova_altura, atual->_esq->_altura + 1);
        if(atual->_dir != nullptr) nova_altura = max(nova_altura, atual->_dir->_altura + 1);
        atual->_altura = nova_altura;
    }

    bool _inserir(int chave, no* atual){
        if(atual->_chave == chave) return false;
        else if(chave < atual->_chave){
            // TENTA INSERIR NA ESQUERDA
            if(atual->_esq == nullptr){
                atual->_esq = new no(chave);
                _atualizar_altura(atual);
                atual->_qnt_sub_esq++;
                return true;
            }else{
                if(_inserir(chave, atual->_esq)){
                    atual->_qnt_sub_esq++;
                    _atualizar_altura(atual);
                    return true;
                }else{
                    return false;
                }
            }
        }else{
            if(atual->_dir == nullptr){
                atual->_dir = new no(chave);
                atual->_qnt_sub_dir++;
                _atualizar_altura(atual);
                return true;
            }else{
                if(_inserir(chave, atual->_dir)){
                    atual->_qnt_sub_dir++;
                    _atualizar_altura(atual);
                    return true;
                }else{
                    return false;
                }
            }
        }
    }

    size_t _caso_remocao(no *atual){
        if(atual->_esq == nullptr && atual->_dir == nullptr) return 1;
        else if(atual->_esq != nullptr && atual->_dir != nullptr) return 3;
        else return 2;
    }

    void _remover_filho(no* pai, bool dir){
        if(dir){
            if(pai->_dir->_esq == nullptr && pai->_dir->_dir == nullptr){ // eh folha
                delete pai->_dir;
                pai->_dir = nullptr;
            }else if(pai->_dir->_esq != nullptr && pai->_dir->_dir == nullptr){ // tem filho a esq
                no* temp = pai->_dir;
                pai->_dir = pai->_dir->_esq;
                delete temp;
            }else{ // tem filho a dir
                no* temp = pai->_dir;
                pai->_dir = pai->_dir->_dir;
                delete temp;
            }
        }else{
            if(pai->_esq->_esq == nullptr && pai->_esq->_dir == nullptr){ // eh folha
                delete pai->_esq;
                pai->_esq = nullptr;
            }else if(pai->_esq->_esq != nullptr && pai->_esq->_dir == nullptr){ // tem filho a esq
                no* temp = pai->_esq;
                pai->_esq = pai->_esq->_esq;
                delete temp;
            }else{ // tem filho a dir
                no* temp = pai->_esq;
                pai->_esq = pai->_esq->_dir;
                delete temp;
            }
        }
    }

    no* _antecessor(no *atual){
        if(atual->_esq != nullptr){
            atual = atual->_esq;
            while(atual->_dir != nullptr){
                atual = atual->_dir;
            }
        } return atual;
    }

    void _remocao_caso12(no* pai, bool dir){
        _remover_filho(pai, dir);
    }

    void _remocao_caso3(no* pai, bool dir){
        no* alvo, *antecessor;
        if(dir) alvo = pai->_dir;
        else alvo = pai->_esq;

        antecessor = _antecessor(alvo);

        int chave_antecessor = antecessor->_chave;

        if(dir) _remover(chave_antecessor, pai->_dir);
        else _remover(chave_antecessor, pai->_esq);


        alvo->_chave = chave_antecessor;
    }

    bool _remover(int chave, no* atual){
        if(atual == nullptr) return false;
        else if(atual != _no_cabeca && chave < atual->_chave){
            if(atual->_esq != nullptr && atual->_esq->_chave == chave){
                size_t caso_remocao = _caso_remocao(atual->_esq);
                if(caso_remocao == 3) _remocao_caso3(atual, false);
                else _remocao_caso12(atual, false);
                atual->_qnt_sub_esq--;
                _atualizar_altura(atual);
                return true;
            }else{
                if(_remover(chave, atual->_esq)){
                    atual->_qnt_sub_esq--;
                    _atualizar_altura(atual);
                    return true;
                }else{
                    return false;
                }
            }
        }else{
            if(atual->_dir != nullptr && atual->_dir->_chave == chave){
                size_t caso_remocao = _caso_remocao(atual->_dir);
                if(caso_remocao == 3) _remocao_caso3(atual, true);
                else _remocao_caso12(atual, true);
                atual->_qnt_sub_dir--;
                _atualizar_altura(atual);
                return true;
            }else{
                if(_remover(chave, atual->_dir)){
                    atual->_qnt_sub_dir--;
                    _atualizar_altura(atual);
                    return true;
                }else{
                    return false;
                }
            }
        }
    }

    void _destrutor(no* atual){
        if(atual->_esq != nullptr) _destrutor(atual->_esq);
        if(atual->_dir != nullptr) _destrutor(atual->_dir);
        delete atual;
    }
public:
    ABB():_tamanho(0), _altura(0), _no_cabeca(new no){}
    ~ABB(){
        _destrutor(_no_cabeca);
        _tamanho = _altura = 0;
    }

    // CONSULTA
    size_t tamanho() const{
        return _tamanho;
    }

    size_t altura() const{
        return _altura;
    }

    no* buscar(int chave) const{
        no *atual = _no_cabeca->_dir;

        while(atual != nullptr){
            if(chave == atual->_chave) return atual;
            else if(chave < atual->_chave) atual = atual->_esq;
            else atual = atual->_dir;
        }
        return nullptr;
    }

    int enesimo_elemento(size_t n) const{
        no *atual = _no_cabeca->_dir;
        size_t posicao_atual;

        if(_tamanho < n || n < 1){ //falar com a prof
            return 0;
        }

        size_t cont = 0;
        while(true){
            // cout << "no atual: " << atual->_chave << endl;
            // cout << "qnts nos a esq: " << atual->_qnt_sub_esq << endl;
            posicao_atual = atual->_qnt_sub_esq + 1 + cont;

            if(n == posicao_atual){
                return atual->_chave;
            }else if(n < posicao_atual){
                atual = atual->_esq;
            }else{
                cont += atual->_qnt_sub_esq + 1;
                atual = atual->_dir;
            }
        }
    }

    size_t posicao(int x) const{
        no *atual = _no_cabeca->_dir;

        int cont = 0;
        while(atual != nullptr){
            if(x == atual->_chave){
                return atual->_qnt_sub_esq + 1 + cont;
            }else if(x < atual->_chave){
                atual = atual->_esq;
            }else{
                cont += atual->_qnt_sub_esq + 1;
                atual = atual->_dir;
            }
        }

        return 0;
    }

    int mediana() const{
        if(_tamanho % 2 == 1) return enesimo_elemento(_tamanho/2 + 1);
        else return enesimo_elemento(_tamanho/2);
    }

    bool eh_cheia() const{
        // cout << _altura<< " "<< (_altura<<1) << endl;
        return pow(2,_altura)-1 == _tamanho;
    }

    bool eh_completa() const{
        queue<pair<no*,size_t>> fila;

        no* atual;
        size_t nivel_atual;
        size_t cont = 0;

        if(_tamanho <= 2)
            return true;

        fila.push({_no_cabeca->_dir, 0});

        while (!fila.empty()){
            atual = fila.front().first;
            nivel_atual = fila.front().second;

            if(nivel_atual == _altura-1){
                break;
            }

            cont++;

            fila.pop();
            if (atual->_esq != nullptr){
                fila.push({atual->_esq, nivel_atual + 1});
            }
            if (atual->_dir != nullptr){
                fila.push({atual->_dir, nivel_atual + 1});
            }
        }
        return (pow(2,_altura-1))-1 == cont;
    }

    string to_string() const{
        if(_no_cabeca->_dir == nullptr) return "";

        stringstream ss;
        queue<no*> fila;
        no* atual;
        fila.push(_no_cabeca->_dir);
        while (!fila.empty()){
            atual = fila.front();
            ss << atual->_chave << " ";
            fila.pop();
            if (atual->_esq != nullptr){
                fila.push(atual->_esq);
            }
            if (atual->_dir != nullptr){
                fila.push(atual->_dir);
            }
        }
        string saida = ss.str();
        saida.pop_back();
        return saida;
    }

    // MANIPULACAO
    bool inserir(int chave){
        if(_no_cabeca->_dir == nullptr){
            _no_cabeca->_dir = new no(chave);
        }else if(!_inserir(chave, _no_cabeca->_dir)){
            return false;
        }

        _tamanho++;
        _atualizar_altura(_no_cabeca);
        _altura = _no_cabeca->_altura;
        return true;
    }

    bool remover(int chave){
        bool ret = _remover(chave, _no_cabeca);
        if(ret){
            _tamanho--;
            _altura = _no_cabeca->_altura;
        }
        return ret;
    }

};
