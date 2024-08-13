#include <iostream>
#include <stdexcept>

class Horario {
protected:
    int hora;
    int minuto;
    int segundo;

    // Método para validar o horário
    void validarHorario(int h, int m, int s) {
        if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            throw std::invalid_argument("Horario invalido");
        }
    }

public:
    // Construtor padrão
    Horario() : hora(0), minuto(0), segundo(0) {}

    // Construtor com parâmetros
    Horario(int h, int m, int s) {
        validarHorario(h, m, s);
        hora = h;
        minuto = m;
        segundo = s;
    }

    // Métodos getters
    int getHora() const { return hora; }
    int getMinuto() const { return minuto; }
    int getSegundo() const { return segundo; }

    // Método para adicionar um horário
    void addHorario(const Horario& outro) {
        segundo += outro.segundo;
        minuto += segundo / 60;
        segundo %= 60;

        minuto += outro.minuto;
        hora += minuto / 60;
        minuto %= 60;

        hora += outro.hora;
        hora %= 24;
    }

    // Sobrecarga do operador +
    Horario operator+(const Horario& outro) const {
        Horario resultado = *this;
        resultado.addHorario(outro);
        return resultado;
    }

    // Método para subtrair um horário
    Horario subtHorario(const Horario& outro) const {
        int h = hora - outro.hora;
        int m = minuto - outro.minuto;
        int s = segundo - outro.segundo;

        if (s < 0) {
            s += 60;
            m--;
        }
        if (m < 0) {
            m += 60;
            h--;
        }
        if (h < 0) {
            h += 24;
        }

        return Horario(h, m, s);
    }

    // Sobrecarga do operador -
    Horario operator-(const Horario& outro) const {
        return subtHorario(outro);
    }

    // Método amigo para imprimir o horário
    friend std::ostream& operator<<(std::ostream& os, const Horario& horario) {
        os << (horario.hora < 10 ? "0" : "") << horario.hora << ":"
           << (horario.minuto < 10 ? "0" : "") << horario.minuto <<'' ":"
           << (horario.segundo < 10 ? "0" : "") << horario.segundo;
        return os;
    }
};

int main() {
    try {
        Horario h1(23, 59, 50);
        Horario h2(0, 0, 15);

        Horario soma = h1 + h2;
        Horario subtracao = h1 - h2;

        std::cout << "Horario 1: " << h1 << std::endl;
        std::cout << "Horario 2: " << h2 << std::endl;
        std::cout << "Soma: " << soma << std::endl;
        std::cout << "Subtracao: " << subtracao << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
