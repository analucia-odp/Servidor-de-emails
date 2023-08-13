//---------------------------------------------------------------------
// Arquivo	: inbox.cpp
// Conteudo	: implementação da TAD inbox
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2022-10-03 - arquivo criado
//---------------------------------------------------------------------

#include "inbox.h"

inbox::inbox()
//DESCRICAO: Cria uma lista de prioridade vazia
{
    tam = 0;
    first_= nullptr;
    last_ = nullptr;
}

/*Funções auxiliares*/
bool inbox::prioritySearch(int PRI, string k)
//DESCRICAO: Função Auxiliar para buscar a prioridade e adicionar a mensagem na fila (caso exista a prioridade em questão)
//ENTRADA: PRIORIDADE da mensagem, mensagem
//SAIDA: true or false
{
    box* aux = first_;
    for (int i=0; i<getTamanho(); i++)
    {
        if (aux->PRI == PRI)
        {
            aux->men.insertEMAIL(k);
            return true;
        }
        aux = aux->prox;
    }
    return false;
}

void inbox::insertFirst(string k, int PRI)
//DESCRICAO: Função Auxiliar para inserir no começo da lista
//ENTRADA: mensagem, prioridade da mensagem
{
    box* nova = new box;
    nova->PRI = PRI;
    nova->men.insertEMAIL(k);
    nova->prox = first_;
    first_ = nova;
    //ESCREVEMEMLOG((long int)(&(nova->PRI)), sizeof(int), 1);
}

void inbox::insertLast(string k, int PRI)
//DESCRICAO: Função Auxiliar para inserir no final da lista
//ENTRADA: mensagem, prioridade da mensagem
{
    box* nova = new box;
    nova->PRI = PRI;
    nova->men.insertEMAIL(k);
    nova->prox = nullptr;
    last_->prox = nova;
    last_ = nova;
    //ESCREVEMEMLOG((long int)(&(nova->PRI)), sizeof(int), 1);
}

/*Funções padrões*/
bool inbox::Vazia()
//DESCRICAO: Função que verifica se a lista está vazia
//SAIDA: true or false
{
    return tam == 0;
}
void inbox::insert(string k, int PRI)
//DESCRICAO: Função Auxiliar para inserir a mensagem na lista
//ENTRADA: mensagem, prioridade da mensagem
{
    if (Vazia())
    {
        box* nova = new box;
        nova->PRI = PRI;
        nova->men.insertEMAIL(k);
        nova->prox = nullptr;
        first_ = last_ = nova;
        tam++;
    }
    else
    {
        if (!prioritySearch(PRI, k))
        {
            box* aux = first_;
            for (int i=0; i<getTamanho(); i++)
            {
                if (PRI>aux->PRI && i==0)
                {
                    insertFirst(k, PRI);
                    break;
                }
                if (aux->prox == nullptr)
                { 
                    insertLast(k, PRI);
                    break;
                }
                if (i != tam-1 && PRI> aux->prox->PRI)
                {
                    box* nova = new box;
                    nova->PRI = PRI;
                    nova->men.insertEMAIL(k);
                    nova->prox = aux->prox;
                    aux->prox = nova;
                    //ESCREVEMEMLOG((long int)(&(nova->PRI)), sizeof(int), 1);
                    break;
                }
                aux = aux->prox;
            } 

            tam++;
        }
    }
     
}
int inbox::getTamanho()
//DESCRICAO: retorna o tamanho da lista
//SAIDA: tamanho da lista
{
    return tam;
}

void inbox::imprimeLista ()
//DESCRICAO: imprime a lista completa
{
    box* p = first_;
    while (p != nullptr)
    {
        cout << "Prioridade: " << p->PRI << " Mensagens: ";
        p->men.imprimeFila();
        p = p->prox;
    }
}

string inbox::getItemInbox()
//DESCRICAO: Retorna a primeira mensagem do primeiro elemento da lista
//SAIDA: mensagem
{ 
    if (Vazia())
        return "CAIXA DE ENTRADA VAZIA\n";
    else{
        /*if (first_->men.vazia())
            removeInicio();*/
        if (Vazia())
            return "CAIXA DE ENTRADA VAZIA\n";
        //LEMEMLOG((long int)(&(first_->PRI)), sizeof(int), 1);
        string aux = first_->men.getEMAIL();
        first_->men.removeEMAIL();
        if (first_->men.vazia())
            removeInicio();
        return aux + "\n";
    }
}

void inbox::removeInicio()
//DESCRICAO: Remove o primeiro elemento da lista
{
    tam--;
    box* aux = first_;
    first_ = aux->prox;
    delete aux;
}
inbox::~inbox()
//DESCRICAO: Desaloca toda a memória da lista
{
    while (!Vazia())
    {
        removeInicio();
    }
}