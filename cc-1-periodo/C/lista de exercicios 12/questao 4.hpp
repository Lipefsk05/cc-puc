#include <iostream>
#include <vector>
#include <string>

class Conta;

class Pessoa {
private:
    std::string nome;
    std::vector<Conta*> contas;
public:
    Pessoa(const std::string& nome, const std::string& cadastro);
    std::string getNome() const;
};

class Fisica : public Pessoa {
private:
    std::string CPF;
public:
    Fisica(const std::string& nome, const std::string& cadastro, const std::string& CPF);
    std::string getCPF() const;
};

class Juridica : public Pessoa {
private:
    std::string CNPJ;
public:
    Juridica(const std::string& nome, const std::string& cadastro, const std::string& CNPJ);
    std::string getCNPJ() const;
};

class Conta {
private:
    int numero;
    float saldo;
    std::string PIX;
public:
    Conta(int numero);
    float getSaldo() const;
    void sacar(float valor);
    void depositar(float valor);
    int getConta() const;
};

class Corrente : public Conta {
public:
    Corrente(int numero);
};

class Poupanca : public Conta {
private:
    int aniversario;
    float valor;
public:
    Poupanca(int numero, int aniversario);
    int getAniversario() const;
    void aplicaJuros();
};

class Especial : public Conta {
private:
    float limite;
public:
    Especial(int numero, float limite);
};

class Historico {
private:
    int numero_conta;
    int operacao;
    float valor;
public:
    void operar(Conta& conta, int operacao, float valor);
};
