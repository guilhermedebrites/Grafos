#include <iostream>

class Celula {
public:
    int elemento;
    Celula* proximo;

    Celula() {
        this->elemento = 0;
        this->proximo = nullptr;
    }

    Celula(int elemento) {
        this->elemento = elemento;
        this->proximo = nullptr;
    }
};

class ListaEncadeada {
public:
    Celula* primeiro;
    Celula* ultimo;

    ListaEncadeada() {
        primeiro = new Celula();
        ultimo = primeiro;
    }

    void inserirInicio(int x) {
        Celula* tmp = new Celula(x);
        tmp->proximo = primeiro->proximo;
        primeiro->proximo = tmp;

        if(primeiro == ultimo) {
            ultimo = tmp;
        }
    }

    void inserirFim(int x) {
        ultimo->proximo = new Celula(x);
        ultimo = ultimo->proximo;
    }

    int removerInicio() {
        if(primeiro == ultimo) {
            std::cerr << "Erro ao remover (vazia)!" << std::endl;
        }
        Celula* tmp = primeiro->proximo;
        primeiro = primeiro->proximo;
        int elemento = tmp->elemento;

        return elemento;
    }

    int removerFim() {
        if(primeiro == ultimo) {
            std::cerr << "Erro ao remover (vazia)!" << std::endl;
        }

        Celula* tmp = primeiro;
        while (tmp->proximo != ultimo) {
            tmp = tmp->proximo;
        }

        int elemento = ultimo->elemento;
        ultimo = tmp;

        return elemento;
    }

    void inserir(int pos, int x) {
        Celula* newCelula = new Celula(x);
        Celula* tmp = primeiro;

        for(int i = 0; i < pos; i++) {
            tmp = tmp->proximo;
        }

        newCelula->proximo = tmp->proximo;
        tmp->proximo = newCelula;
    }

    void remover(int pos) {
        Celula* tmp = primeiro;

        for(int i = 0; i < pos; i++) {
            tmp = tmp->proximo;
        }

        Celula* newCelula = tmp->proximo;
        tmp->proximo = newCelula->proximo;
    }

    void imprimir() {
        Celula* tmp = primeiro->proximo;
        while (tmp != nullptr) {
            std::cout << tmp->elemento << " ";
            tmp = tmp->proximo;
        }
        std::cout << std::endl;
    }

    int pesquisar(int x) {
        Celula* tmp = primeiro->proximo;
        while (tmp != nullptr) {
            if(tmp->elemento == x) {
                return 1;
            }
            tmp = tmp->proximo;
        }
        return 0;
    }


};

int main() {
    ListaEncadeada lista;
    lista.inserirInicio(1);
    lista.inserirInicio(2);
    lista.inserirInicio(3);
    lista.inserirFim(4);
    lista.inserirFim(5);
    lista.imprimir();
    
    std::cout << lista.removerInicio() << std::endl;
    std::cout << lista.removerFim() << std::endl;
    lista.imprimir();

    lista.pesquisar(3) ? std::cout << "Encontrado" << std::endl : std::cout << "Não encontrado" << std::endl;
    lista.pesquisar(4) ? std::cout << "Encontrado" << std::endl : std::cout << "Não encontrado" << std::endl;

    return 0;
}