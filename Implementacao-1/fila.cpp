#include <stdlib.h>
#include <iostream>

class No
{
    public:
    int data;
    No *prox;

    public:
    No(int data)
    {
        this->data = data;
        this->prox = nullptr;
    }
};

class Fila 
{

    private:
    No *primeiro;
    No *ultimo;

    public:
    Fila()
    {
        this->primeiro = nullptr;
        this->ultimo = nullptr;
    }

    void printFila()
    {
        for(No *i = primeiro; i != ultimo->prox; i= i->prox)
        {
            std::cout << i->data << " ";
        }    
    }

    int tamanho()
    {
        int tamanho = 0;
        for(No* i = primeiro; i != ultimo->prox; i = i->prox)
        {
            tamanho++;
        }
        return tamanho;
    }

    void enfileira(int data)
    {
        No *novo = new No(data);
        if(primeiro == nullptr)
        {
            primeiro = novo;
            ultimo = primeiro;
        }

        ultimo->prox = novo;
        ultimo = ultimo->prox;
        ultimo->prox = nullptr;

        novo = nullptr;
    }

    bool busca(int valor)
    {
        bool resposta = false;
        for(No* i = primeiro; i != ultimo->prox; i = i->prox)
        {
            if(i->data == valor)
            {
                resposta = true;
            }
        }
        return resposta;
    }

    int remove()
    {
        No* i = primeiro;
        int retorno = primeiro->data;
        primeiro = primeiro->prox;
        i->prox = nullptr;
        
        delete(i);
        i = nullptr;
        
        return retorno;
    }

};

using std::cout;
using std::cin;
using std::endl;

int main() 
{
    Fila* fila = new Fila();

    cout << "Inserindo na fila" << endl;
    for(int i = 0; i < 4; i++)
    {
        cout << "Fila:" << endl;    
        fila->enfileira(i);
        fila->printFila();
        cout << endl;
    }

    cout << "Buscando elemento específico: 2" << endl;
    if(fila->busca(2))
    {
        cout << "Elemento encontrado!" << endl;
    }
    else
    {
        cout << "Elemento não encontrado" << endl;
    }

    cout << "Removendo da fila" << endl;

    int retorno = fila->remove();
    cout << "Elemento excluido: " << retorno << endl;

    cout << "Fila: " << endl;

    fila->printFila(); 

    cout << endl << "Removendo da fila" << endl;

    retorno = fila->remove();
    cout << "Elemento excluido: " << retorno << endl;

    cout << "Fila: " << endl;

    fila->printFila();
    

}