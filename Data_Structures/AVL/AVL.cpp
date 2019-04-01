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

    void _rot_dir(no * p){
        no *u = p->_esq;
        p->_esq = u->_dir;
        u->_dir = p;
    }

    void _rot_esq(no * p){
        no *q = p->_dir;
        p->_dir = q->_esq;
        q->_esq = p;
    }

    void _dupla_rot_dir(no * p){
        no *u = p->_esq;
        no *v = u->_dir;

        u->_dir = v->_esq;
        p->_esq = v->_dir;
        v->_esq = u;
        v->_dir = p;
    }

    void _dupla_rot_esq(no * p){
        no *z = p->_dir;
        no *y = z->_esq;

        p->_dir = y->_esq;
        z->_esq = y->_dir;
        y->_esq = p;
        y->_dir = z;
    }

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

    string to_string() const{
        if(_no_cabeca->_dir == nullptr) return "";

        stringstream ss;
        queue<pair<no*,size_t>> fila;
        no* atual;
        fila.push({_no_cabeca->_dir, 0});
        size_t altura_atual, ultima_altura = 0;
        while (!fila.empty()){
            atual = fila.front().first;
            altura_atual = fila.front().second;
            if(altura_atual != ultima_altura){
                ss << endl;
            }
            ss << atual->_chave << " ";
            fila.pop();
            if (atual->_esq != nullptr){
                fila.push(atual->_esq);
            }
            if (atual->_dir != nullptr){
                fila.push(atual->_dir);
            }
            ultima_altura = altura_atual;
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
