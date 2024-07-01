#include <iostream>
#include <stdexcept>

class Data {
protected:
    int ano;
    int mes;
    int dia;

    // Verifica se uma data é válida
    bool dataValida(int a, int m, int d) const {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > diasNoMes(a, m)) return false;
        return true;
    }

    // Retorna o número de dias em um determinado mês
    int diasNoMes(int a, int m) const {
        if (m == 2) {
            // Verifica ano bissexto
            if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
                return 29;
            } else {
                return 28;
            }
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            return 30;
        }
        return 31;
    }

    // Adiciona dias a data armazenada
    void addDias(int n) {
        dia += n;
        while (dia > diasNoMes(ano, mes)) {
            dia -= diasNoMes(ano, mes);
            if (++mes > 12) {
                mes = 1;
                ano++;
            }
        }
    }

public:
    // Construtor com validação
    Data(int a, int m, int d) {
        if (!dataValida(a, m, d)) {
            throw std::invalid_argument("Data invalida");
        }
        ano = a;
        mes = m;
        dia = d;
    }

    // Métodos gets
    int getAno() const { return ano; }
    int getMes() const { return mes; }
    int getDia() const { return dia; }

    // Método para adicionar dias à data
    void addDiasArmazen(int n) {
        if (!dataValida(ano, mes, dia)) {
            throw std::invalid_argument("Data invalida");
        }
        addDias(n);
    }

    // Sobrecarga do operador +
    Data operator+(int n) const {
        Data novaData(ano, mes, dia);
        novaData.addDiasArmazen(n);
        return novaData;
    }

    // Método amigo para impressão
    friend std::ostream& operator<<(std::ostream& os, const Data& data) {
        os << (data.dia < 10 ? "0" : "") << data.dia << "/"
           << (data.mes < 10 ? "0" : "") << data.mes << "/"
           << data.ano;
        return os;
    }

    // Método para calcular a diferença de dias entre datas
    int diferencaDias(const Data& outra) const {
        // Simplificação: usando uma contagem simples de dias desde o início do ano 0
        auto diasDesdeZero = [](const Data& d) {
            int totalDias = d.ano * 365 + d.dia;
            for (int i = 0; i < d.mes - 1; ++i) {
                totalDias += d.diasNoMes(d.ano, i + 1);
            }
            return totalDias;
        };
        return abs(diasDesdeZero(*this) - diasDesdeZero(outra));
    }

    // Sobrecarga do operador -
    int operator-(const Data& outra) const {
        return diferencaDias(outra);
    }
};

int main() {
    try {
        Data data1(2024, 6, 30);
        Data data2(2023, 7, 1);

        std::cout << "Data 1: " << data1 << std::endl;
        std::cout << "Data 2: " << data2 << std::endl;

        data1.addDiasArmazen(5);
        std::cout << "Data 1 após adicionar 5 dias: " << data1 << std::endl;

        Data data3 = data1 + 10;
        std::cout << "Data 3 (Data 1 + 10 dias): " << data3 << std::endl;

        int diferenca = data1 - data2;
        std::cout << "Diferença de dias entre Data 1 e Data 2: " << diferenca << " dias" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
