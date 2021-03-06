/***************************************************************************
*  $MCI M�dulo de implementa��o: VER Vertice
*
*  Arquivo gerado:              VERTICE.C
*  Letras identificadoras:      VER
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\VERTICE.BSW
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

#define VERTICE_OWN
#include "VERTICE.H"
#undef VERTICE_OWN

VER_tpCondRet Ret;

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor do v�rtice
*
*
***********************************************************************/

   typedef struct VER_tagVertice {

	   char Nome[20];

   } VER_tpVertice ;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: VER  &Criar v�rtice
*  ****/

   VER_tpCondRet VER_CriarVertice( VER_tppVerticeCont * pVertice , char * Nome )
   {

      VER_tppVerticeCont pVerticeM = ( VER_tppVerticeCont ) malloc( sizeof( VER_tpVertice )) ;
      if ( pVerticeM == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

	  strcpy (pVerticeM->Nome, Nome);

	  (*pVertice) = ( VER_tpVertice * ) malloc( sizeof( VER_tpVertice )) ;
	  
	  if ( pVertice == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

	  (*pVertice) = pVerticeM;


	  return VER_CondRetOK ;

   } /* Fim fun��o: VER  &Criar v�rtice */

/***************************************************************************
*
*  Fun��o: VER  &Destruir v�rtice
*  ****/

   VER_tpCondRet VER_DestruirVertice( VER_tppVerticeCont * pVertice )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

      VER_tpVertice * pConteudo;
      pConteudo = *pVertice;

	  free(pVertice);

	  return VER_CondRetOK ;

   } /* Fim fun��o: VER  &Destruir v�rtice */

/***************************************************************************
*
*  Fun��o: VER  &Mudar valor do v�rtice
*  ****/

   VER_tpCondRet VER_MudarNomeVertice( VER_tppVerticeCont pVertice , char * Nome  )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(pVertice == NULL)
	  {
		  return VER_CondRetNaoAchou ;
	  } /* if */
	  if(strcmp(pVertice->Nome , "")==0)
	  {
		  return VER_CondRetVerVazio;
	  } /* if */

      strcpy (pVertice->Nome , Nome);

	  if(strcmp(pVertice->Nome , Nome)==0)
	  {
		  return VER_CondRetOK;
	  } /* if */

	  return VER_CondRetNaoAchou ;

   } /* Fim fun��o: VER  &Mudar valor do v�rtice */

/***************************************************************************
*
*  Fun��o: VER  &Obter valor do v�rtice
*  ****/

   VER_tpCondRet VER_ObterValor( VER_tppVerticeCont pVertice , char * Nome  )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(strcmp( pVertice->Nome , "") == 0)
	  {
		  return VER_CondRetVerVazio;
	  } /* if */

	  if(strcmp(pVertice->Nome , Nome) == 0)
	  {
		  return VER_CondRetOK;
	  } /* if */

	  return VER_CondRetNaoAchou ;

   } /* Fim fun��o: VER  &Obter valor do v�rtice */

   /***************************************************************************
*
*  Fun��o: VER  &Retorna valor do v�rtice
*  ****/

   VER_tpCondRet VER_RetornaValor( VER_tppVerticeCont pVertice , char * Nome )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(pVertice == NULL)
	  {
		  return VER_CondRetNaoAchou ;
	  } /* if */

	  if(strcmp( pVertice->Nome , "") == 0)
	  {
		  Nome = pVertice->Nome;
		  return VER_CondRetVerVazio;
	  } /* if */

	  Nome = pVertice->Nome;
	  return VER_CondRetOK;
	
   } /* Fim fun��o: VER  &Retorna valor do v�rtice */

/********** Fim do m�dulo de implementa��o: VER  V�rtice **********/
