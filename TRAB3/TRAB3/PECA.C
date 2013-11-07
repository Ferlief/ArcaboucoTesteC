/***************************************************************************
*
*  $MCD M�dulo de defini��o: PEC  Pe�a do tabuleiro
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 - Verificador de Xeque-Mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*			         vo - Vinicius de Luiz de Oliveira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     Y       afv   xx/xx/2013  finaliza��o do desenvolvimento do modulo
*     1       afv   24/out/2013 in�cio do desenvolvimento do m�dulo
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

//teste
#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

#include "LISTA.H"

#define MAX_NOME 10

/**************************************************************************
*
*  $TC Tipo de dados: PEC Descritor do tipo de peca
*
*
**************************************************************************/

   typedef struct PEC_tagElemPeca {

		char Nome[MAX_NOME];
		/* String com o nome da pe�a */

		int diagonal;
		/* Se pe�a pode ir para diagonal 
		(1 para sim, 0 caso contr�rio) */

		int reta;
		/* Se pe�a pode ir para horizontal e vertical
		 (1 para sim, 0 caso contr�rio) */

		int qtde;
		/* Quantidade casas que a pe�a pode andar */
		  
   } PEC_tpElemPeca ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PEC  &Criar peca
*  ****/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , 
									 int Qtde , char * Nome)
{
	
	PEC_tppPeca mPeca = NULL;
	
	mPeca = (PEC_tppPeca) malloc(sizeof(PEC_tpElemPeca));

	if(mPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria ;
	} /* if */
	
	mPeca->diagonal = Diag;
	mPeca->reta     = Reta;
	mPeca->qtde     = Qtde;
	strcpy(mPeca->Nome , Nome);
	
	(*pPeca) = (PEC_tpElemPeca *) malloc(sizeof(PEC_tppPeca));

	if(pPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria ;
	} /* if */
	
	(*pPeca) = mPeca;
	
	return PEC_CondRetOK;
	
} /* Fim fun��o: PEC &Criar Peca */

/***************************************************************************
*
*  Fun��o: PEC  &Obter nome
*  ****/

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void ** NomePeca)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	} /* if */
	
	strcpy((char *)NomePeca , pPeca->Nome);

	
	return PEC_CondRetOK;
} /* Fim fun��o: PEC &Obter nome */

/***************************************************************************
*
*  Fun��o: PEC  &Obter dados do tipo pe�a
*  ****/

PEC_tpCondRet PEC_ObterDadosTipoPeca (PEC_tppPeca pPeca , void ** Nome, 
                                      int * Diag , int * Reta , int * Qtde)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	} /* if */

	strcpy((char *)Nome , pPeca->Nome);
	*Diag = pPeca->diagonal;
	*Reta = pPeca->reta;
	*Qtde = pPeca->qtde;

	return PEC_CondRetOK;

} /* Fim fun��o: PEC &Obter dados do tipo pe�a */


/*****  C�digo das fun��es encapsuladas pelo m�dulo  *****/


/********** Fim do m�dulo de implementa��o: PEC  Pe�a do tabuleiro **********/

