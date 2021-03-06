/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo GRAFO
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Exemplo de teste automatizado
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
*       1.00   afv   19/out/2013 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN


LIS_tpCondRet ListaRet , ListaRetCaminho;
VER_tpCondRet ContVertRet;



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da aresta do v�rtice do grafo
*
*
*  $ED Descri��o do tipo
*     Possui as refer�ncias para r�tulo string e tpVerticeGrafo destino
*
***********************************************************************/

typedef struct tagArestaGrafo {

	char * Nome;
		/* Rotulo da aresta */

	GRA_tppVerGrafo pVerticeDest;
		/* Ponteiro do Elemento tpVerticeGrafo destino */

	
} tpArestaGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor do elemento v�rtice do grafo
*
*
*  $ED Descri��o do tipo
*     Possui as refer�ncias para lista de sucessores e antecessores
*     Possui ponteiro para tipo VER_tppVertice
*     Possui id como refer�ncia do elemento v�rtice
*
***********************************************************************/

typedef struct tagVerticeGrafo {

	LIS_tppLista pVerAnt ;
		/* Ponteiro para lista de antecessores */
	
	LIS_tppLista pVerSuc ;	
		/* Ponteiro para lista de sucessores */

	void * pConteudo ;
		/* Ponteiro para o conte�do do v�rtice */

	char pIdVertice;
		/* Identificador do v�rtice */

	void (*destruirValorV)(void *pValor);
        /* Destruir Valor do conte�do do v�rtice */
	
} tpVerticeGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabe�a do grafo
*
*
*  $ED Descri��o do tipo
*     A cabe�a do grafo indica o in�cio do grafo, possui refer�ncias para
*     lista de origens e v�rtices do grafo, o n� corrente referenciado
*     na cabe�a, permite apontar em qual v�rtice est� o elemento corrente.
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pListaOrigens;
		/* Ponteiro para lista de v�rtices de origens */

	LIS_tppLista pListaVertices;
		/* Ponteiro para lista com todos os v�rtices */

	tpVerticeGrafo * pCorrente;
		/* Ponteiro do Elemento v�rtice corrente */

	void (*destruirValor)(void *pValor);
		/* Ponteiro para implementa��o do destruir grafo gen�rico */

} GRA_tpGrafo ;

/************* Fun��es encapsuladas no m�dulo *************************/

static void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);
 
static void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);

static void GRA_CriaListaVertices( GRA_tppGrafo pGrafo ) ;

static void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo ) ;

static void * GRA_CriaContVertice( char * Conteudo );

static void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice) ;

static void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice) ;

static void GRA_excluirValorLista ( void * pValor ) ;

static void GRA_excluirValorListaAresta ( void * pValor );

static int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO ) ;

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char Id) ;

static void LiberarAresta(GRA_tppArestaGrafo pAres);

static int ChecaArestaExiste(tpVerticeGrafo * pVertice , char * String, char Dest);

static int ChecaVerticeExiste(GRA_tppGrafo pGrafo, char Vert);

static void DestruirMalloc(LIS_tppLista pLista);


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***************************************************************************
*
*  Fun��o: GRA  &Criar Grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo , void   ( * ExcluirValor ) ( void * pDado ) )
{
	
	GRA_tppGrafo mGrafo ;

	mGrafo = (GRA_tppGrafo) malloc ( sizeof( GRA_tpGrafo ));

	if(mGrafo == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	mGrafo->pCorrente = NULL;
	mGrafo->destruirValor = ExcluirValor;
	GRA_CriaListaOrigens (mGrafo);
	GRA_CriaListaVertices (mGrafo);


	(*pGrafo) = ( GRA_tpGrafo * ) malloc( sizeof( GRA_tppGrafo )) ;

	if(pGrafo == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	(*pGrafo) = mGrafo;

	
	return GRA_CondRetOK;
}


/***************************************************************************
*
*  Fun��o: GRA  &Criar V�rtice Grafo
*  ****/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char id, void   ( * ExcluirValor ) ( void * pDado ))
{

	GRA_tppVerGrafo pVert;
	int ret = 0;

	if(pGrafo==NULL){

		return GRA_CondRetGrafoNulo ;

	} /* if */

	ret = ChecaVerticeExiste(pGrafo, id);
	if(ret == 1){
		return GRA_VerticeJaExiste ;
	} /* if */

	pVert = (GRA_tppVerGrafo) malloc (sizeof (tpVerticeGrafo));


	if(pVert == NULL){
		return GRA_CondRetFaltouMemoria ;
	} /* if */

	pVert->pIdVertice = id ;
	pVert->pConteudo = GRA_CriaContVertice (String) ;
	pVert->destruirValorV = ExcluirValor ;
	GRA_CriaListaSucessoresVertice (pVert);
	GRA_CriaListaAntecessoresVertice (pVert);
	
	LIS_InserirElementoApos(pGrafo->pListaVertices, pVert );
		/* Insere v�rtice na lista de v�rtices do grafo */

	pGrafo->pCorrente = pVert;

	return GRA_CondRetOK ;

	
}

/***************************************************************************
*
*  Fun��o: GRA  &Criar Aresta do v�rtice Grafo
*  ****/

GRA_tpCondRet GRA_CriarAresta (char pVertOrig , char pVertDest , GRA_tppGrafo pGrafo, char * String)
{

	GRA_tppArestaGrafo pAres;
	tpVerticeGrafo * pVertO;
	tpVerticeGrafo * pVertD;
	int ret = 0;

	if(pGrafo==NULL){
		return GRA_CondRetGrafoNulo ;
	} /* if */ 

	pVertO = GRA_BuscarVertice(pGrafo, pVertOrig);
	if(pVertO == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */
	
	pVertD = GRA_BuscarVertice(pGrafo, pVertDest);
	if(pVertD == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */
	
	ret = ChecaArestaExiste(pVertO , String, pVertD->pIdVertice);
	if(ret==1){
		return GRA_ArestaJaExiste ;
	} /* if */

	pAres = (GRA_tppArestaGrafo) malloc (sizeof (tpArestaGrafo));

	if(pAres == NULL){
		return GRA_CondRetFaltouMemoria ;
	} /* if */
	
	pAres->Nome = String;
	pAres->pVerticeDest = pVertD;

	pGrafo->pCorrente = pVertO;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerSuc , pAres);
		/* Inserir aresta na lista de sucessores do vertorigem */

	pGrafo->pCorrente = pVertD;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerAnt , pVertO);
		/* Inserir vertice na lista de antecessores do vertdestino */

	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Fun��o: GRA  &Insere v�rtice como origem do Grafo
*  ****/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char IdVert)
{
	tpVerticeGrafo * VerCorr;
	tpVerticeGrafo * pVertO;
	ListaRetCaminho = LIS_CondRetOK ;

	VerCorr = GRA_BuscarVertice(pGrafo, IdVert);
	if(VerCorr == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	LIS_IrInicioLista(pGrafo->pListaOrigens);

	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor (pGrafo->pListaOrigens , (void**)&pVertO);

		if(VerCorr->pIdVertice == pVertO->pIdVertice){

			return GRA_CondRetMaisdeUmaOrigem;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

	} /* while */

	LIS_InserirElementoApos(pGrafo->pListaOrigens , VerCorr);

	pGrafo->pCorrente = VerCorr;

	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Fun��o: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(char pVertOrig , char pVertDest , GRA_tppGrafo pGrafo)
{
	tpVerticeGrafo * pVertO;
	tpVerticeGrafo * pVertD;
	tpArestaGrafo * pAres;
	
	pVertO = GRA_BuscarVertice(pGrafo, pVertOrig);
	if(pVertO == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	pVertD = GRA_BuscarVertice(pGrafo, pVertDest);
	if(pVertD == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	pGrafo->pCorrente = pVertO;

	ListaRetCaminho = LIS_IrInicioLista(pVertO->pVerSuc);
		
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
		LIS_ObterValor (pVertO->pVerSuc , (void**)&pAres);

		if(pAres->pVerticeDest->pIdVertice == pVertDest){

			GRA_excluirValorListaAresta(pAres);

			LIS_ExcluirElemento(pVertO->pVerSuc);

			break;

		} /* if */
		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertO->pVerSuc, 1);

	} /* while */

	pGrafo->pCorrente = pVertD;

	ListaRetCaminho = LIS_IrInicioLista(pVertD->pVerAnt);
		
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
		LIS_ObterValor (pVertD->pVerAnt , (void**)&pVertO);

		if(pVertO->pIdVertice == pVertOrig){

			LIS_ExcluirElemento(pVertD->pVerAnt);

			break;

		} /* if */
		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertD->pVerAnt, 1);

	} /* while */


	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Fun��o: GRA  &Definir v�rtice corrente
*  ****/

GRA_tpCondRet GRA_DefinirCorrente(GRA_tppGrafo pGrafo, char IdVert)
{

	tpVerticeGrafo * pVerticeBusca ;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	while(ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista){

		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pVerticeBusca);

		if(pVerticeBusca->pIdVertice == IdVert){
			pGrafo->pCorrente = pVerticeBusca;
			return GRA_CondRetOK;
		} /* if */

		if(ListaRet==LIS_CondRetFimLista){
			break;
		} /* if */

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */

	return GRA_CondRetNaoAchou ;
}


/***************************************************************************
*
*  Fun��o: GRA  &Excluir v�rtice
*  ****/


GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo)
{
	int ts;
	tpVerticeGrafo * pVertOrigem;
	tpVerticeGrafo * pVerticeCaminho;
	GRA_tppArestaGrafo pAres;

	pVertOrigem = pGrafo->pCorrente;

	LIS_IrInicioLista(pVertOrigem->pVerAnt);

	ListaRet        = LIS_CondRetOK ;
	ListaRetCaminho = LIS_CondRetOK;	
	

	LIS_NumElem(pVertOrigem->pVerAnt,&ts);

	if(ts > 0 ){

		while(ListaRet!=LIS_CondRetListaVazia)
		{

			LIS_ObterValor (pVertOrigem->pVerAnt , (void**)&pVerticeCaminho);
		
			ListaRetCaminho = LIS_IrInicioLista(pVerticeCaminho->pVerSuc);		


			while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
				LIS_ObterValor (pVerticeCaminho->pVerSuc , (void**)&pAres);

				if(pAres->pVerticeDest->pIdVertice == pVertOrigem->pIdVertice){

					GRA_ExcluirAresta(pVerticeCaminho->pIdVertice , pVertOrigem->pIdVertice , pGrafo);
					
				} /* if */
				if(ListaRetCaminho == LIS_CondRetFimLista){
					break;
				} /* if */
				ListaRetCaminho = LIS_AvancarElementoCorrente(pVerticeCaminho->pVerSuc, 1);


			} /* while */

		
			ListaRet = LIS_ChecaOrigemNulo(pVertOrigem->pVerAnt);

		} /* while */
	} /* if */

	ListaRet = LIS_IrInicioLista(pVertOrigem->pVerSuc);

	ListaRet = LIS_CondRetOK ;

	LIS_NumElem(pVertOrigem->pVerSuc,&ts);
	
	if(ts > 0 ){

		while(ListaRet!=LIS_CondRetListaVazia)
		{
		
			LIS_ObterValor (pVertOrigem->pVerSuc , (void**)&pAres);

			ListaRetCaminho = LIS_IrInicioLista((LIS_tppLista)pAres->pVerticeDest->pVerAnt);

			while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

				LIS_ObterValor (pAres->pVerticeDest->pVerAnt , (void**)&pVerticeCaminho);
			
				if(pVerticeCaminho->pIdVertice == pVertOrigem->pIdVertice){

					GRA_ExcluirAresta(pVertOrigem->pIdVertice , pAres->pVerticeDest->pIdVertice  , pGrafo);

					break;

				} /* if */
				if(ListaRetCaminho == LIS_CondRetFimLista){

					break;

				} /* if */

				ListaRetCaminho = LIS_AvancarElementoCorrente(pAres->pVerticeDest->pVerAnt, 1);


			} /* while */


			ListaRet = LIS_ChecaOrigemNulo(pVertOrigem->pVerAnt);

		} /* while */

	} /* if */
		
	LIS_DestruirLista (pVertOrigem->pVerAnt);
		/* Destroi a lista de antecessores ap�s eliminar as referencias */

	LIS_DestruirLista (pVertOrigem->pVerSuc);
		/* Destroi a lista de antecessores ap�s eliminar as referencias */

	GRA_ExcluirdeVertices(pGrafo,pVertOrigem);
		/* Destroi a refer�ncia da lista de origens  */

	GRA_ExcluirdeOrigens(pGrafo,pVertOrigem);
		/* Destroi a refer�ncia da lista de v�rtices */
	
	pGrafo->pCorrente->destruirValorV(pVertOrigem->pConteudo);

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	if(ListaRet == LIS_CondRetOK){
		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVerticeCaminho);
		pGrafo->pCorrente = pVerticeCaminho;
	}

	free (pVertOrigem);

	pVertOrigem->pIdVertice = '\0';	
	pVertOrigem->pConteudo = NULL;

	pVertOrigem = NULL;

	return GRA_CondRetOK;
	
}


/***************************************************************************
*
*  Fun��o: GRA  &Obter valor do v�rtice corrente
*  ****/

GRA_tpCondRet GRA_ChecarNomeVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{

	VER_tppVerticeCont valorElem ;

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */
	if(pGrafo->pCorrente == NULL){

		return GRA_CondRetConteudoNulo ;

	} /* if */
	
	valorElem = (VER_tppVerticeCont)pGrafo->pCorrente->pConteudo ;
	
	ContVertRet = VER_ObterValor((VER_tppVerticeCont)pGrafo->pCorrente->pConteudo , nomeForn) ;

	if(ContVertRet == VER_CondRetOK){

		return GRA_CondRetOK ;
 
	} /* if */

	return GRA_CondRetConteudoNulo ;
}

/***************************************************************************
*
*  Fun��o: GRA  &Mudar valor do v�rtice corrente
*  ****/

GRA_tpCondRet GRA_MudarNomeVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{
	
	if(pGrafo == NULL){

		return GRA_CondRetVerticeNulo;

	} /* if */
	if(VER_MudarNomeVertice((VER_tppVerticeCont)pGrafo->pCorrente->pConteudo , nomeForn)==0){

		return GRA_CondRetOK ;

	} /* if */

	return GRA_CondRetConteudoNulo;
}

/***************************************************************************
*
*  Fun��o: GRA  &Obter valor por refer�ncia
*  ****/

GRA_tpCondRet GRA_ObterValorCorrente(GRA_tppGrafo pGrafo , void ** pValor)
{

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */
	
	*pValor = pGrafo->pCorrente->pConteudo;

	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Fun��o: GRA  &Destruir Grafo
*  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo)
{
	int numElem = 0;
	tpVerticeGrafo * pVert ;
	GRA_tpCondRet RET;

	if(pGrafo==NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */

	LIS_IrInicioLista(pGrafo->pListaVertices);

	LIS_NumElem(pGrafo->pListaVertices , &numElem);

	while(numElem > 0){

		LIS_IrInicioLista(pGrafo->pListaVertices);

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVert);

		pGrafo->pCorrente = pVert;

	    GRA_ExcluirVerticeCorrente(pGrafo);
		
		LIS_NumElem(pGrafo->pListaVertices , &numElem);


	} /* while */

	LIS_DestruirLista(pGrafo->pListaOrigens);

	LIS_DestruirLista(pGrafo->pListaVertices);

	free(pGrafo);

	pGrafo  = NULL;

	return GRA_CondRetOK;

}

GRA_tpCondRet GRA_AvancarCorrente(GRA_tppGrafo pGrafo , int val)
{
	
	tpVerticeGrafo * pVert;

	if(pGrafo == NULL){
		return GRA_CondRetGrafoNulo ;
	} /* if */
	if(pGrafo->pCorrente == NULL){
		return GRA_CondRetConteudoNulo ;
	} /* if */

	LIS_IrInicioLista(pGrafo->pListaVertices);

	LIS_ObterValor(pGrafo->pListaVertices , (void **)&pVert);

	pGrafo->pCorrente = pVert;

	return GRA_CondRetOK ;
}

/*****  C�digo das fun��es encapsuladas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: GRA  - &Limpa o conte�do da lista de v�rtices do grafo 
*
***********************************************************************/

void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	tpVerticeGrafo * pVert;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	while(ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista)
	{

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVert);
		if(pVertice->pIdVertice == pVert->pIdVertice){
			LIS_ExcluirElemento (pGrafo->pListaVertices);
		}
		if(ListaRet == LIS_CondRetFimLista){
			break;
		}
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	}
	

} /* Fim fun��o: GRA &Limpa o conte�do da lista de v�rtices do grafo  */


/***********************************************************************
*
*  $FC Fun��o: GRA  - Limpa o conte�do da lista de origens do grafo 
*
***********************************************************************/

void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	
	tpVerticeGrafo * pVert;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaOrigens);


	while(ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista)
	{
		LIS_ObterValor(pGrafo->pListaOrigens , (void**)&pVert);
		if(pVertice->pIdVertice == pVert->pIdVertice){
			LIS_ExcluirElemento (pGrafo->pListaOrigens);
		}
		if(ListaRet == LIS_CondRetFimLista){
			break;
		}
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

	}


} /* Fim fun��o: GRA &Limpa o conte�do da lista de origens do grafo  */


 /***************************************************************************
*
*  Fun��o: GRA  &Criar conte�do do v�rtice do Grafo
*  
************************************************************************/

void * GRA_CriaContVertice(char * Conteudo )
{
	
	VER_tppVerticeCont pVerticeCont ;

	ContVertRet = VER_CriarVertice(&pVerticeCont , Conteudo);

	if(ContVertRet == VER_CondRetOK){

		return pVerticeCont ;

	} 
	return NULL;

} /* Fim fun��o: GRA  &Criar conte�do do v�rtice do Grafo */


/***************************************************************************
*
*  Fun��o: GRA  &Criar Lista de origens Grafo
*
*************************************************************************/

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo )
{


	LIS_tppLista pListaOrig ;

	LIS_CriarLista (GRA_excluirValorLista , &pListaOrig);

	pGrafo->pListaOrigens = pListaOrig ;

} /* Fim fun��o: GRA  &Criar Lista de origens Grafo */


/***************************************************************************
*
*  Fun��o: GRA  &Criar Lista de v�rtices Grafo
*
*************************************************************************/

void GRA_CriaListaVertices( GRA_tppGrafo pGrafo )
{

	
	LIS_tppLista pListaVert ;

	LIS_CriarLista (GRA_excluirValorLista, &pListaVert);

	pGrafo->pListaVertices= pListaVert ;

} /* Fim fun��o: GRA  &Criar Lista de v�rtices Grafo */


/***************************************************************************
*
*  Fun��o: GRA  &Criar Lista de sucessores do vertice do Grafo
*
*************************************************************************/

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaSuc ;

	LIS_CriarLista (GRA_excluirValorLista, &pListaSuc);

	pVertice->pVerSuc = pListaSuc ;

} /* Fim fun��o: GRA  &Criar Lista de sucessores do vertice do Grafo */


/***************************************************************************
*
*  Fun��o: GRA  &Criar Lista de antecessores do vertice do Grafo
*
*************************************************************************/

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaAnt ;

	LIS_CriarLista (GRA_excluirValorLista , &pListaAnt);

	pVertice->pVerAnt = pListaAnt ;

} /* Fim fun��o: GRA  &Criar Lista de antecessores do vertice do Grafo */


/***************************************************************************
*
*  Fun��o: GRA  &Excluir valor lista
*
****************************************************************************/

void GRA_excluirValorLista ( void * pValor )
{


} /* Fim fun��o: GRA  &Excluir valor lista */


/***************************************************************************
*
*  Fun��o: GRA  &Excluir valor lista do tipo Aresta
*
****************************************************************************/

void GRA_excluirValorListaAresta ( tpArestaGrafo * pAresta )
{

	free(pAresta);

} /* Fim fun��o: GRA  &Excluir valor lista */


/***************************************************************************
*
*  Fun��o: GRA  &Compara conteudo do vertice
*
****************************************************************************/

int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO )
{

	int ret = 0;
	char * Corrente ;
	char * Buscado ;
	tpVerticeGrafo * pValorVert ;
    LIS_tppLista pVerticeLista ;

	Corrente = "";
	Buscado  = "";
	
	pVerticeLista = ( LIS_tppLista ) pVerticeO ;
    
	LIS_ObterValor (pVerticeLista , (void**)&pValorVert);


	VER_RetornaValor ((VER_tppVerticeCont)pValorVert->pConteudo , Corrente) ;

	VER_RetornaValor ((VER_tppVerticeCont)pValorO , Buscado) ;
	
	if(strcmp(Corrente , Buscado) == 0){

		return 0;
	}

	return 1;


} /* Fim fun��o: GRA  &Compara valores */

/***************************************************************************
*
*  Fun��o: GRA  &Avancar Vertice corrente
*
****************************************************************************/

int AvancarVerticeCorrente (GRA_tppGrafo pGrafo , int numElem)
{

	GRA_tppVerGrafo pValorVert ;

	ListaRet = LIS_AvancarElementoCorrente (pGrafo->pListaVertices , 1);
	
	if(ListaRet == LIS_CondRetOK){

		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pValorVert);

	    pGrafo->pCorrente = pValorVert ;

		return 1 ;

	}

	return 0 ;
} /* Fim fun��o: GRA  &Avancar Vertice corrente */


/***************************************************************************
*
*  Fun��o: GRA  &Destruir valor do grafo
*
****************************************************************************/

GRA_tpCondRet destruirValor(GRA_tppGrafo pGrafo)
{

	if(pGrafo==NULL){
		return GRA_CondRetGrafoNulo;
	}

	pGrafo->pCorrente = NULL;

	LIS_DestruirLista(pGrafo->pListaOrigens);
	LIS_DestruirLista(pGrafo->pListaVertices);

	free(pGrafo);

	pGrafo = NULL;

	return GRA_CondRetOK;

} /* Fim fun��o: GRA  &Destruir valor do grafo */



/***************************************************************************
*
*  Fun��o: GRA  &Buscar Vertice
*
****************************************************************************/

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char Id)
{
	tpVerticeGrafo * pVerticeRes;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	
	while (ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista){
	
		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pVerticeRes);

		if(pVerticeRes->pIdVertice == Id){
			return pVerticeRes ;
		}
		if(ListaRet ==LIS_CondRetFimLista){
			break;
		} /* if */

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
	}

	return NULL ;

}  /* Fim fun��o: GRA &Buscar Vertice */

/***************************************************************************
*
*  Fun��o: GRA  &Limpar conte�do de aresta
*
****************************************************************************/

void LiberarAresta(GRA_tppArestaGrafo pAres)
{
	pAres->Nome = NULL;
	pAres->pVerticeDest = NULL;
	free(pAres);
	pAres = NULL;
} /* Fim fun��o: GRA &Limpar conte�do de aresta */

/***************************************************************************
*
*  Fun��o: GRA  &Checa se aresta existe
*
****************************************************************************/

int ChecaArestaExiste(tpVerticeGrafo * pVertice , char * String, char Dest)
{
	tpArestaGrafo * pAres ;

	if(pVertice==NULL){
		return 0;
	} /* if */

	ListaRetCaminho=LIS_IrInicioLista(pVertice->pVerSuc);

	
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor(pVertice->pVerSuc , (void**)&pAres);

		if(strcmp(pAres->Nome , String)==0 && pAres->pVerticeDest->pIdVertice == Dest){

			return 1;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){
			return 0;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);

	} /* while */

	pAres = NULL;

	return 0;
} /* Fim fun��o: GRA &Checa se aresta existe */

/***************************************************************************
*
*  Fun��o: GRA  &Checa se v�rtice existe
*
****************************************************************************/

int ChecaVerticeExiste(GRA_tppGrafo pGrafo, char Vert)
{
	tpVerticeGrafo * pVertice;

	if(pGrafo==NULL){
		return 0;
	} /* if */

	ListaRetCaminho=LIS_IrInicioLista(pGrafo->pListaVertices);
	
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVertice);

		if(pVertice->pIdVertice == Vert){

			return 1;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){
			return 0;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */

	pVertice = NULL;

	return 0;
} /* Fim fun��o: GRA &Checa se vertice existe */


/********** Fim do m�dulo de implementa��o: M�dulo GRAFO **********/
