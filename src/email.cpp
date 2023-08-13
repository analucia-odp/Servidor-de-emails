//---------------------------------------------------------------------
// Arquivo	: email.cpp
// Conteudo	: implementação da TAD email
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-03 - arquivo criado
//---------------------------------------------------------------------
#include "email.h"

email::email()
//DESCRICAO: cria uma fila de emails vazia
{
    first_ = nullptr;
    last_ = nullptr;
}

string email::getEMAIL()
//DESCRICAO: retorna a primeira mensagem da caixa de entrada
{
    return first_->conteudo;
}

bool email::vazia()
//DESCRICAO: verifica se a fila esta vazia
//SAIDA: true or false
{
    return (first_ == nullptr);
}

void email::removeEMAIL()
//DESCRICAO: remove o primeiro email da fila
{

    msg* aux = first_;
    first_ = aux->prox;
    delete aux;
}

void email::insertEMAIL(string k)
//DESCRICAO: insere o email no ultimo lugar da fila
{
    if (vazia())
        first_ = last_ = new msg{k,nullptr};
    else{
        msg* novo = new msg{k, nullptr};
        last_->prox = novo;
        last_ = novo;
    }
}

void email::imprimeFila ()
//DESCRICAO: imprime a fila completa
{
    msg* p = first_;
    while (p != nullptr)
    {
        std::cout << p->conteudo << "\n";
        p = p->prox;
    }
}

email::~email()
//DESCRICAO: exclui todos os emails
{
    while (!vazia())
        removeEMAIL();
}
