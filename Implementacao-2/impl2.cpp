#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>

class Arestas {
public:
    int vertice1, vertice2;

    Arestas(int a, int b) : vertice1(a), vertice2(b) {}

    std::string toString() const {
        return "(" + std::to_string(vertice1) + ", " + std::to_string(vertice2) + ")";
    }
};

class Grafo {
public:
    int num_vertices;
    std::vector<int> vertices;
    int num_arestas;

    Grafo(int n) : num_vertices(n), num_arestas((n * (n - 1)) / 2) {
        for (int i = 1; i <= n; i++) {
            vertices.push_back(i);
        }
    }

    int fatorial(int n) {
        return (n == 1 || n == 0) ? 1 : n * fatorial(n - 1);
    }

    double getQuantidadeSubgrafos(int n, int p = 1, double resp = 0) {
        double factorial_part = static_cast<double>(fatorial(n)) / (fatorial(p) * fatorial(n - p));
        double exponent = pow(2, (p * (p - 1)) / 2);
        resp += factorial_part * exponent;

        if (p == n) {
            return resp;
        }

        return getQuantidadeSubgrafos(n, p + 1, resp);
    }

    std::vector<std::vector<int>> getNVertices(std::vector<int> lst, int n) {
        if (n == 0) {
            return {{}};
        }
        if (n > lst.size()) {
            return {};
        }
        std::vector<std::vector<int>> combinations;

        for (size_t i = 0; i < lst.size(); i++) {
            int atual = lst[i];
            std::vector<int> restante(lst.begin() + i + 1, lst.end());
            for (auto& combo : getNVertices(restante, n - 1)) {
                combo.insert(combo.begin(), atual);
                combinations.push_back(combo);
            }
        }
        return combinations;
    }

    std::vector<Arestas> gerarArestas(const std::vector<int>& lista_vertices) {
        std::vector<Arestas> arestas;
        for (auto a : lista_vertices) {
            for (auto b : lista_vertices) {
                if (a < b) {
                    arestas.push_back(Arestas(a, b));
                }
            }
        }
        return arestas;
    }

    std::vector<std::string> iniciarSubgrafos(std::vector<int> vertices, int index, std::vector<std::string>& subgrafos) {
        auto lista_vertices = getNVertices(vertices, index);
        for (auto& subconjunto : lista_vertices) {
            auto subgraf = getSubgrafos(subconjunto);
            subgrafos.insert(subgrafos.end(), subgraf.begin(), subgraf.end());
        }
        if (index == 1) {
            return subgrafos;
        }

        return iniciarSubgrafos(vertices, index - 1, subgrafos);
    }

    std::vector<std::string> getSubgrafos(std::vector<int> lista_vertices) {
        auto arestas = gerarArestas(lista_vertices);
        std::vector<std::string> subgrafos;

        std::string vertices = ";Vertices: {";
        for (auto vertice : lista_vertices) {
            vertices += std::to_string(vertice) + ", ";
        }
        vertices = vertices.substr(0, vertices.size() - 2);
        vertices += "}";

        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                std::string subgrafo = "Arestas: {}";
                subgrafo += vertices;
                subgrafos.push_back(subgrafo);
            }

            if (i == 1 && lista_vertices.size() > 1) {
                std::vector<std::vector<int>> todas_combinacoes;
                for (size_t a = 1; a < arestas.size(); a++) {
                    std::vector<int> posicoes(arestas.size());
                    std::iota(posicoes.begin(), posicoes.end(), 0); // Fill with 0, 1, 2, ..., len(arestas)-1
                    auto combinacoes = getNVertices(posicoes, a);
                    todas_combinacoes.insert(todas_combinacoes.end(), combinacoes.begin(), combinacoes.end());
                }

                for (auto& combinacao : todas_combinacoes) {
                    std::string subgrafo = "Arestas: {";
                    for (auto aresta_index : combinacao) {
                        subgrafo += arestas[aresta_index].toString() + ", ";
                    }
                    subgrafo = subgrafo.substr(0, subgrafo.size() - 2);
                    subgrafo += "}";
                    subgrafo += vertices;
                    subgrafos.push_back(subgrafo);
                }
            }

            if (i == 2 && lista_vertices.size() > 1) {
                std::string subgrafo = "Arestas: {";
                for (auto& aresta : arestas) {
                    subgrafo += aresta.toString() + ", ";
                }
                subgrafo = subgrafo.substr(0, subgrafo.size() - 2);
                subgrafo += "}";
                subgrafo += vertices;
                subgrafos.push_back(subgrafo);
            }
        }

        return subgrafos;
    }
};

int main() {
    int n = 3;
    Grafo a(n);
    double b = a.getQuantidadeSubgrafos(n);
    std::vector<std::string> subgrafos;
    subgrafos = a.iniciarSubgrafos(a.vertices, a.num_vertices, subgrafos);
    for (size_t index = 0; index < subgrafos.size(); index++) {
        std::cout << "SUBGRAFO " << index + 1 << ":     " << subgrafos[index] << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Quantidade de subgrafos: " << b << std::endl;

    return 0;
}
