//---------------------------------------------------------------------
// Arquivo	: servidor.cpp
// Conteudo	: implementação da TAD servidor
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-03 - arquivo criado
//---------------------------------------------------------------------

#include "servidor.h"

servidor::servidor()
//DESCRICAO: Cria uma lista de usuários vazia
{
    tam=0;
    first_ = nullptr;
    last_ = nullptr;
}

/*Funções auxiliares*/
void servidor::removeFirst()
//DESCRICAO: Remove o primeiro usuário
{
    user* aux = first_;
    first_ = aux->prox;
    delete aux;
}

bool servidor::searchIDRemove(int ID)
//DESCRICAO: Função Auxiliar para buscar e remover diretamente aqueles usuários que precisam ser posicionados na lista
//ENTRADA: ID do usuário
//SAIDA: true or false
{
    if (getTamanho() == 0)
        return false;

    user* aux=first_;
    for (int i=0; i<getTamanho(); i++)
    {
        //LEMEMLOG((long int)(&(aux->ID)), sizeof(int), 0);
        if (aux->ID == ID && i==0)
        {
            removeFirst();
            return true;
        }
        
       if (i != getTamanho()-1 && aux->prox->ID == ID )
        {
            user* k = aux->prox;
            //LEMEMLOG((long int)(&(k->ID)), sizeof(int), 0);
            if (k->prox == nullptr)
            {
                aux->prox = nullptr;
                last_ = aux;
                delete k;
            }

            else{
                aux->prox = k->prox;
                delete k;
            }

            return true;
        }
           
        aux=aux->prox;
    }

    return false;
}

string servidor::searchIDConsulta(int ID)
//DESCRICAO: Função Auxiliar para buscar o usuário e retornar o primeiro email da fila de maior prioridade 
//ENTRADA: ID do usuário
//SAIDA: Primeiro email de maior prioridade
{
    user* aux=first_;
    for (int i=0; i<getTamanho(); i++)
    {
        //LEMEMLOG((long int)(&(aux->ID)), sizeof(int), 1);
        if (aux->ID == ID)
            return aux->box.getItemInbox();
        aux = aux->prox; 
    }

    return "\0";
}
bool servidor::searchIDEntrega(int ID, bool procura, string MSG, int PRI)
//DESCRICAO: Função Auxiliar para buscar o usuário na lista e caso procura = true, ira inserir a mensagem na fila
//ENTRADA: ID do usuário, Mensagem de email, Prioridade da mensagem
//SAIDA: true or false
{
    user* aux=first_;
    for (int i=0; i<getTamanho(); i++)
    {
        //LEMEMLOG((long int)(&(aux->ID)), sizeof(int), 0);
        //if (!procura)
            //LEMEMLOG((long int)(&(aux->ID)), sizeof(int), 1);
        if (aux->ID == ID)
        {
            if(!procura)
                aux->box.insert(MSG, PRI);
            return true;
        } 

        aux = aux->prox;
    }

    return false;
}

int servidor::getTamanho ()
//DESCRICAO: retorna o tamanho da lista
//SAIDA: tamanho da lista
{
    return tam;
}

/*Funções padrões*/
string servidor::cadastraUsuario (int ID)
//DESCRICAO: Insere o usuário na lista
//ENTRADA: ID do usuário
//SAIDA: OK: CONTA ID CADASTRADA || ERRO: CONTA ID JA EXISTENTE
{
    //mudei aqui: 15-10
    if (getTamanho() > 0 && searchIDEntrega(ID, true, " ", 0))
        return "ERRO: CONTA " + std::to_string(ID) + " JA EXISTENTE\n";
    
    if (getTamanho() == 0)
    {
        user* nova = new user;
        nova->ID = ID;
        nova->prox = nullptr;
        first_ = last_ = nova;
        //ESCREVEMEMLOG((long int)(&(nova->ID)), sizeof(int), 0);

    }

    else{
        user* nova = new user;
        nova->ID = ID;
        nova->prox = nullptr;
        last_->prox = nova;
        last_ = nova;
        //ESCREVEMEMLOG((long int)(&(nova->ID)), sizeof(int), 0);
    }

    tam++;
    return "OK: CONTA " + std::to_string(ID)  + " CADASTRADA\n";
}
string servidor::removerUsuario (int ID)
//DESCRICAO: Remove o usuário na lista
//ENTRADA: ID do usuário
//SAIDA: OK: CONTA ID REMOVIDA || ERRO: CONTA ID NAO EXISTE
{
    //mudei aqui: 15-10
    if (getTamanho() == 0 || !searchIDRemove(ID))
        return "ERRO: CONTA " + std::to_string(ID) + " NAO EXISTE\n";
    
    tam--;
    return "OK: CONTA " + std::to_string(ID)  + " REMOVIDA\n";
}
string servidor::entregaEMAIL (int ID, int PRI, string MSG)
//DESCRICAO: Insere o email na caixa de entrada
//ENTRADA: ID do usuário, prioridade da mensagem, Mensagem
//SAIDA: OK: MENSAGEM PARA ID ENTREGUE || ERRO: CONTA ID NAO EXISTE
{
    if (getTamanho() == 0 || !searchIDEntrega(ID, false, MSG, PRI))
        return "ERRO: CONTA " + std::to_string(ID) + " NAO EXISTE\n";
    
    return "OK: MENSAGEM PARA " + std::to_string(ID)  + " ENTREGUE\n";
}
string servidor::consultaUsuario (int ID)
//DESCRICAO: Consulta a caixa de entrada do Usuário
//ENTRADA: ID do usuário
//SAIDA: CAIXA DE ENTRADA VAZIA || ERRO: CONTA ID NAO EXISTE
{
    string MSG = searchIDConsulta(ID);
    if (MSG == "\0")
        return "ERRO: CONTA " + std::to_string(ID) + " NAO EXISTE\n";
    
    return "CONSULTA " + std::to_string(ID) + ": " + MSG; 
}

servidor::~servidor()
//DESCRICAO: Desaloca toda a lista
{
    while (first_ != nullptr)
    {
        removeFirst();
        tam--;
    }
}