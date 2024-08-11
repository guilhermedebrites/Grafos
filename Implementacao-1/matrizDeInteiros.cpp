#include <iostream>

class Celula {
public:
    int valor;
    Celula *direita, *abaixo, *acima, *esquerda;

    Celula(int valor = 0) : valor(valor), direita(nullptr), abaixo(nullptr), acima(nullptr), esquerda(nullptr) {}
};

class Matriz {
private:
    Celula *inicio;
    int linhas, colunas;

    Celula *getCelula(int linha, int coluna) {
        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            return nullptr;
        }

        Celula *aux = inicio;
        for (int i = 0; i < linha; i++) {
            aux = aux->abaixo;
        }
        for (int i = 0; i < coluna; i++) {
            aux = aux->direita;
        }
        return aux;
    }

public:
    // Construtor
    Matriz(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
        inicio = new Celula(0);
        Celula *aux = inicio;

        for (int i = 1; i < colunas; i++) {
            aux->direita = new Celula(0);
            aux->direita->esquerda = aux;
            aux = aux->direita;
        }

        aux = inicio;

        for (int i = 1; i < linhas; i++) {
            aux->abaixo = new Celula(0);
            aux->abaixo->acima = aux;
            aux = aux->abaixo;

            Celula *aux2 = aux;

            for (int j = 1; j < colunas; j++) {
                aux2->direita = new Celula(0);
                aux2->direita->esquerda = aux2;
                aux2->direita->acima = aux2->acima->direita;
                aux2->acima->direita->abaixo = aux2->direita;
                aux2 = aux2->direita;
            }
        }
    }

    // Destrutor
    ~Matriz() {
        Celula* linhaAtual = inicio;
        while (linhaAtual) {
            Celula* celAtual = linhaAtual;
            linhaAtual = linhaAtual->abaixo;
            while (celAtual) {
                Celula* temp = celAtual;
                celAtual = celAtual->direita;
                delete temp;
            }
        }
    }

    // Inserir
    void inserir(int linha, int coluna, int valor) {
        Celula *aux = getCelula(linha, coluna);
        if (aux) {
            aux->valor = valor;
        } else {
            std::cerr << "Indice fora dos limites" << std::endl;
        }
    }

    // Pesquisar
    bool contem(int valor) {
        Celula *linhaAtual = inicio;
        while (linhaAtual) {
            Celula *celAtual = linhaAtual;
            while (celAtual) {
                if (celAtual->valor == valor) {
                    return true;
                }
                celAtual = celAtual->direita;
            }
            linhaAtual = linhaAtual->abaixo;
        }
        return false;
    }

    // Remover
    int remover(int linha, int coluna) {
        Celula *aux = getCelula(linha, coluna);
        if (aux) {
            int valor = aux->valor;
            aux->valor = 0;
            return valor;
        }
        std::cerr << "Indice fora dos limites" << std::endl;
        return 0;
    }

    // Imprimir Matriz
    void imprimir() {
        Celula *linhaAtual = inicio;
        while (linhaAtual) {
            Celula *celAtual = linhaAtual;
            while (celAtual) {
                std::cout << celAtual->valor << " ";
                celAtual = celAtual->direita;
            }
            std::cout << std::endl;
            linhaAtual = linhaAtual->abaixo;
        }
        std::cout << std::endl;
    }
};

int main() {
    int linhas = 3, colunas = 3;
    Matriz matriz(linhas, colunas);

    matriz.inserir(0, 0, 5);
    matriz.inserir(1, 1, 10);
    matriz.inserir(2, 2, 15);

    std::cout << "INSERCAO:\n\n";
    std::cout << "Matriz:" << std::endl;
    matriz.imprimir();
    std::cout << "----------------------------"<< std::endl;


    std::cout << "PESQUISA:\n\n";
    int target = 10;
    if (matriz.contem(target)) {
        std::cout << "O elemento " << target << " esta na matriz\n\n";
    } else {
        std::cout << "O elemento " << target << " nao esta na matriz\n\n";
    }
    std::cout << "----------------------------"<< std::endl;



    std::cout << "REMOCAO:\n\n";
    int removido = matriz.remover(1, 1);
    std::cout << "Elemento removido: " << removido << std::endl << std::endl;

    
    std::cout << "Matriz:" << std::endl;
    matriz.imprimir();
    std::cout << "----------------------------"<< std::endl;

    return 0;
}