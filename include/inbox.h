//---------------------------------------------------------------------
// Arquivo	: inbox.h
// Conteudo	: TAD para manipular e armazenar (em uma lista) a caixa de entrada de cada usuário
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-03 - arquivo criado
//---------------------------------------------------------------------

#ifndef INBOX_H
#define INBOX_H

#include <iostream>
#include <string>
#include "memlog.h"
#include "email.h"

using namespace std;

struct box
{
    int PRI;
    email men;
    box* prox;
};

class inbox
{
   public:
        inbox(); 
        ~inbox();

        void insert(string k, int PRI); 
        void removeInicio();
        void imprimeLista();
        string getItemInbox();
        int getTamanho();

        bool Vazia();

   private:
        box* first_;
        box* last_;
        int tam;

        bool prioritySearch(int PRI, string k);
        void insertFirst (string k, int PRI);
        void insertLast (string k, int PRI);
        
};
#endif