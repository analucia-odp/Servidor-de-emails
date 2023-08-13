//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: simulação de um servidor de emails
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-01 - arquivo criado
//---------------------------------------------------------------------

#include "email.h"
#include "inbox.h"
#include "servidor.h"
#include "memlog.h"
#include "msgassert.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

typedef struct file
// estrutra para armazenar os atributos de execução da entrada padrão
{
    string key;
    int ID;
    int PRI;
    string MSG;
} file;

int main(int argc, char **argv)
{
    string line;

    servidor p;

    file file_;
    file_.ID = 0;
    file_.PRI = 0;

    /*// iniciar registro de acesso
    iniciaMemLog("/home/analop/ED_AnaLuciaOliveiradePaula/analisamem/teste/log.out");

    if (true)
        ativaMemLog();
    else
        desativaMemLog();

    defineFaseMemLog(0);  */ 

    ifstream fin (argv[1]);


    while (getline(fin, line))
    {
        try
        {
            istringstream ss{line};
            ss >> file_.key >> file_.ID;

            if (file_.ID < 0 || file_.ID > 1000000)
                throw file_.ID;

            if (file_.key == "CADASTRA")
                cout << p.cadastraUsuario(file_.ID);
            else if (file_.key == "REMOVE")
                cout << p.removerUsuario(file_.ID);
            else if (file_.key == "ENTREGA")
            {
                try{
                    ss >> file_.PRI;
                        if (file_.PRI < 0 || file_.PRI > 9)
                            throw file_.PRI;
                    getline(ss, file_.MSG);
                    cout << p.entregaEMAIL(file_.ID, file_.PRI, file_.MSG.substr(1, file_.MSG.length() - 4));
                }catch(int e){
                    cout << "main - PRIORIDADE: " << e << " invalida\n";
                }
            }
            else if (file_.key == "CONSULTA")
                cout << p.consultaUsuario(file_.ID);
            else
                throw file_.key;
        }catch(int e)
        {
            cout << "main - ID: " << e << " invalido\n";
        }
        catch (string e)
        {
            cout << "main - Comando " << e << " invalido\n";
        }
            
    }
    cout << "\n";
    //return finalizaMemLog();
    return 0;
}