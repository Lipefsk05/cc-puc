#include <iostream>

// Supondo que as classes Data e Horario estejam definidas assim:
class Data {
public:
    int ano, mes, dia;

    Data(int a = 0, int m = 0, int d = 0) : ano(a), mes(m), dia(d) {}

    // Diferença em dias entre duas datas
    int diferenca(const Data& outra) const {
        // Este é um cálculo simplificado que não considera meses com diferentes quantidades de dias ou anos bissextos.
        int dias1 = ano * 365 + mes * 30 + dia;
        int dias2 = outra.ano * 365 + outra.mes * 30 + outra.dia;
        return dias1 - dias2;
    }
};

class Horario {
public:
    int hora, minuto, segundo;

    Horario(int h = 0, int m = 0, int s = 0) : hora(h), minuto(m), segundo(s) {}

    // Diferença em segundos entre dois horários
    int diferenca(const Horario& outro) const {
        int segundos1 = hora * 3600 + minuto * 60 + segundo;
        int segundos2 = outro.hora * 3600 + outro.minuto * 60 + outro.segundo;
        return segundos1 - segundos2;
    }
};

class DataHorario : public Data, public Horario {
public:
    DataHorario(const Data& data, const Horario& horario)
        : Data(data), Horario(horario) {}

    // Método para calcular a diferença entre dois DataHorario e retornar como Horario
    Horario diferenca(const DataHorario& outro) const {
        int diferencaDias = Data::diferenca(outro);
        int diferencaSegundos = Horario::diferenca(outro);
        
        // Considerar a diferença de dias em segundos
        diferencaSegundos += diferencaDias * 24 * 3600;

        int h = diferencaSegundos / 3600;
        int m = (diferencaSegundos % 3600) / 60;
        int s = diferencaSegundos % 60;

        return Horario(h, m, s);
    }

    // Sobrecarga do operador -
    Horario operator-(const DataHorario& outro) const {
        return diferenca(outro);
    }

    // Método amigo para formato de saída "AAAA/MM/DD-hh:mm:ss"
    friend std::ostream& operator<<(std::ostream& os, const DataHorario& dt) {
        os << dt.ano << "/" 
           << (dt.mes < 10 ? "0" : "") << dt.mes << "/" 
           << (dt.dia < 10 ? "0" : "") << dt.dia << "-"
           << (dt.hora < 10 ? "0" : "") << dt.hora << ":" 
           << (dt.minuto < 10 ? "0" : "") << dt.minuto << ":" 
           << (dt.segundo < 10 ? "0" : "") << dt.segundo;
        return os;
    }
};

int main() {
    Data data1(2024, 7, 1);
    Horario horario1(12, 30, 45);
    DataHorario dt1(data1, horario1);

    Data data2(2023, 6, 30);
    Horario horario2(14, 45, 30);
    DataHorario dt2(data2, horario2);

    Horario diferenca = dt1 - dt2;

    std::cout << "Data e horário 1: " << dt1 << std::endl;
    std::cout << "Data e horário 2: " << dt2 << std::endl;
    std::cout << "Diferença: " << diferenca.hora << " horas, " << diferenca.minuto << " minutos, " << diferenca.segundo << " segundos" << std::endl;

    return 0;
}
