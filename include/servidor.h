//---------------------------------------------------------------------
// Arquivo	: servidor.h
// Conteudo	: TAD para manipular e armazenar (em uma lista) as diferentes contas de usuário
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-03 - arquivo criado
//---------------------------------------------------------------------

#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <string>
#include "inbox.h"
#include "memlog.h"

using namespace std;

struct user
{
    int ID;
    inbox box;
    user* prox;
};

class servidor
{
   public:
        servidor();
        ~servidor();
        
        string cadastraUsuario (int ID);
        string removerUsuario (int ID);
        string entregaEMAIL (int ID, int PRI, string MSG);
        string consultaUsuario (int ID);

    private:
        user* first_;
        user* last_;
        int tam;

        bool searchIDRemove(int ID);
        string searchIDConsulta(int ID);
        bool searchIDEntrega(int ID, bool procura, string MSG, int PRI);
        void removeFirst();
        int getTamanho ();
};
#endif