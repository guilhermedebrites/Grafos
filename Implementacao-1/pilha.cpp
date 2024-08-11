#include <iostream>
#include <exception>

class Pilha {
public:
    class Celula {
    public:
        int elemento;
        Celula* prox;

        Celula() : elemento(0), prox(nullptr) {}

        Celula(int elemento) : elemento(elemento), prox(nullptr) {}
    };

private:
    Celula* topo;

public:
    Pilha() : topo(nullptr) {}

    void inserir(int x) {
        Celula* tmp = new Celula(x);
        tmp->prox = topo;
        topo = tmp;
    }

    int remover() {
        if (topo == nullptr) {
            throw std::runtime_error("A pilha está vazia");
        }
        int removido = topo->elemento;
        Celula* tmp = topo;
        topo = topo->prox;
        delete tmp;
        return removido;
    }

    bool pesquisar(int x) {
        bool resp = false;
        for (Celula* i = topo; i != nullptr; i = i->prox) {
            if (i->elemento == x) {
                resp = true;
                break;
            }
        }
        return resp;
    }

    ~Pilha() {
        while (topo != nullptr) {
            Celula* tmp = topo;
            topo = topo->prox;
            delete tmp;
        }
    }
};

int main() {
    Pilha pilha;
    pilha.inserir(10);
    pilha.inserir(20);
    pilha.inserir(30);
    pilha.inserir(40);
    pilha.inserir(50);

    bool resp = pilha.pesquisar(30);
    std::cout << std::boolalpha << resp << std::endl;
    int removido = pilha.remover();
    std::cout << removido << std::endl;

    return 0;
}