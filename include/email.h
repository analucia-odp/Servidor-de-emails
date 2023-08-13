//---------------------------------------------------------------------
// Arquivo	: email.h
// Conteudo	: TAD para manipular e armazenar (em uma fila) os emails
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-03 - arquivo criado
//---------------------------------------------------------------------

#ifndef EMAIL_H
#define EMAIL_H

#include <iostream>
#include <string>
#include "memlog.h"

using namespace std;

struct msg   
{
    string conteudo;
    msg* prox;
};

class email
{
    public: 
        email(); 
        ~email();

        void insertEMAIL(string k); 
        void removeEMAIL();
        bool vazia ();
        string getEMAIL(); 
        void imprimeFila ();

    private:
        msg* first_;
        msg* last_;
};
#endif