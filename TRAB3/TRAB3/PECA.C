/***************************************************************************
*
*  $MCD M�dulo de defini��o: PEC  Peca do tabuleiro
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: INF 1301 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: aw - Alexandre Werneck
*           fr - Fernanda Camelo Ribeiro
*			vo - Vinicius de Luiz de Oliveira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       afv   19/out/2013 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

#include "LISTA.H"

#define MAX_NOME 10

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor do elemento Peca
*
*
***********************************************************************/

   typedef struct PEC_tagElemPeca {

		char Nome[MAX_NOME];
		
		int diagonal;
		
		int reta;
		
		int qtde;
		  
   } PEC_tpElemPeca ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PEC  &Criar peca
*  ****/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , int Qtde , char * Nome)
{
	
	PEC_tppPeca mPeca = NULL;
	
	mPeca = (PEC_tppPeca) malloc(sizeof(PEC_tpElemPeca));

	if(mPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria ;
	}	
	
	mPeca->diagonal = Diag;
	mPeca->reta     = Reta;
	mPeca->qtde     = Qtde;
	strcpy(mPeca->Nome , Nome);
	
	(*pPeca) = (PEC_tpElemPeca *) malloc(sizeof(PEC_tppPeca));
	
	(*pPeca) = mPeca;
	
	return PEC_CondRetOK;
	
} /* Fim fun��o: PEC &Criar Peca */

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void ** NomePeca)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	}
	
	strcpy((char *)NomePeca , pPeca->Nome);

	
	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_ObterDadosTipoPeca (PEC_tppPeca pPeca , void ** Nome, int * Diag , int * Reta , int * Qtde)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	}
	printf("Nome aqui %s" ,pPeca->Nome );

	strcpy((char *)Nome , pPeca->Nome);
	*Diag = pPeca->diagonal ;
	*Reta = pPeca->reta;
	*Qtde = pPeca->qtde;

	return PEC_CondRetOK;

}


/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/
