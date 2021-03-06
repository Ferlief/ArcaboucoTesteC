#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo grafo
*
*  Arquivo gerado:              GRAFO.H
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
*       1.00   afv   09/out/2013 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa a cria��o e manipula��o de grafos dirigidos.
*	  Podem existir n grafos operando simultaneamente.
*	  O m�dulo grafo possui cabe�a apontando para uma lista de origens,
*	  v�rtices e um ponteiro corrente que caminha pelo grafo apontando
*     para v�rtice.
*
*	  A lista de origens referencia a origem de cada sub-grafo, caso
*	  exista, no m�dulo grafo.
*
*	  A lista de v�rtices possui refer�ncia para todos os v�rtices do
*	  grafo.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "LISTA.H"
#include "TABULEIRO.H"
#include "MATRIZ.H"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/* Tipo refer�ncia para um vertice de grafo */
typedef struct tagVerticeGrafo * GRA_tppVerGrafo ;

/* Tipo refer�ncia para uma aresta do vertice de grafo */
typedef struct tagArestaGrafo * GRA_tppArestaGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

        GRA_CondRetOK = 0 ,
            /* Executou correto */

		GRA_CondRetValorNulo = 1 ,
			/* Valor fornecido nulo */

		GRA_CondRetVerticeNulo = 2 ,
			/* Vertice de parametro nulo */

		GRA_CondRetListaNula = 3 ,
			/* Valor lista nula */

		GRA_CondRetConteudoNulo = 4 ,
			/* Conteudo fornecido nulo */

	   GRA_CondRetGrafoNulo   = 5 ,
		    /* Grafo nulo */

       GRA_CondRetNaoAchou   = 6 ,
	       /* Condicao n�o encontrou */

       GRA_CondRetMaisdeUmaOrigem = 7 ,
	       /* N�o foi poss�vel inserir em origem */

		GRA_ArestaJaExiste = 8 ,
	       /* N�o foi poss�vel criar aresta */

        GRA_CondRetFaltouMemoria = 9 ,
            /* Faltou mem�ria ao alocar dados */

		GRA_VerticeJaExiste = 10 ,
			/* Vertice j� existe na lista de v�rtices desse grafo */

		GRA_CondRetFimLista = 11
		    /*	Fim da lista de v�rtices */

} GRA_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: GRA Criar grafo
*
*  $ED Descri��o da fun��o
*     Inicia um grafo vazio, sem v�rtices.
*
*  $EP Par�metros
*     pGrafo  - Posi��o do vetor de grafos criado.
*     ExcluirValor - Fun��o de exclus�o do grafo gen�rico
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Grafo criado em posi��o do vetor  de grafos
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Grafo n�o criado por falta de mem�ria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo, void   ( * ExcluirValor ) ( void * pDado ) );

/***********************************************************************
*
*  $FC Fun��o: GRA Criar v�rtice grafo
*
*  $ED Descri��o da fun��o
*     Cria um elemento v�rtice do grafo e insere
*     este na lista de v�rtices do grafo, sentando
*     como corrente.
*
*  $EP Par�metros
*     pGrafo    - Grafo que receber� o vertice criado
*     conteudo  - Ponteiro para elemento de conte�do v�rtice
*	  id        - Identificador do v�rtice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE Grafo criado
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   V�rtice criado com conte�do e id
*      ponteiro ListaAnt � apontado para lista vazia criada
*      ponteiro ListaSuc � apontado para lista vazia criada
*      V�rtice inserido na lista de v�rtices do grafo
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   V�rtice n�o criado por falta de mem�ria
*
*
***********************************************************************/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char * id , void   ( * ExcluirValor ) ( void * pDado ));


/***********************************************************************
*
*  $FC Fun��o: GRA Excluir v�rtice
*
*  $ED Descri��o da fun��o
*     Excluir elemento v�rtice corrente do grafo. Esta fun��o percorre 
*	  a lista de antecessores e sucessores do v�rtice a excluir 
*     eliminando as refer�ncias e as arestas da lista de sucessores. 
*     A fun��o tamb�m elimina, caso exista as refer�ncias em origens.
*     Elimina da lista de v�rtices do grafo.
*
*  $EP Par�metros
*     pGrafo   - Ponteiro para o grafo contendo o v�rtice corrente
*
*  $FV Valor retornado
*      GRA_CondRetOK
*
*  $AE Grafo j� deve ter sido criado
*      Corrente do grafo n�o pode estar nulo
*      Grafo dever� conter v�rtices na lista de v�rtices
*
*  $AS Se CondRet = GRA_CondRetOK
*      pVertice � exclu�do da lista de v�rtices do grafo
*      Caso exista, pVertice � exclu�do da lista de origens
*      pVertice perde as refer�ncias nas listas de antecessores e sucessores
*      As listas do v�rtice s�o exclu�das
*      pV�rtice � exclu�do
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Fun��o: GRA Obter valor do v�rtice corrente
*
*  $ED Descri��o da fun��o
*      Checa se a string fornecida � igual a do elemento
*      v�rtice corrente no grafo.     
*
*  $EP Par�metros
*      pGrafo - Ponteiro para o grafo que cont�m o corrente
*      nomeForn - String de compara��o     
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetConteudoNulo
*      GRA_CondRetOK
*
*  $AE Grafo deve estar iniciado
*      Corrente n�o pode estar apontando para NULL
*      String fornecida n�o vazia
*      Grafo n�o vazio, ou seja, sem v�rtices
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo 
*      Grafo fornecido n�o criado
*
*	   Se CondRet = GRA_CondRetConteudoNulo
*      Valor n�o encontrado ou string fornecida vazia
*
*	   Se CondRet = GRA_CondRetOK
*      Valor fornecido igual ao do v�rtice corrente
*
***********************************************************************/

GRA_tpCondRet GRA_ChecarNomeVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

/***********************************************************************
*
*  $FC Fun��o: GRA Mudar valor do v�rtice corrente
*
*  $ED Descri��o da fun��o
*     Recebe uma string como segundo par�metro e altera o valor
*     do conte�do do v�rtice corrente do grafo.
*
*  $EP Par�metros
*     pGrafo - Ponteiro para o grafo
*     nomeForn - String a ser usada como novo valor para o conteudo do v�rtice
*
*  $FV Valor retornado
*      GRA_CondRetVerticeNulo
*      GRA_CondRetConteudoNulo
*      GRA_CondRetOK
*
*  $AE Grafo deve estar iniciado
*      Corrente n�o pode estar apontando para NULL
*      String fornecida n�o vazia
*      Grafo n�o vazio, ou seja, sem v�rtices
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo 
*      Grafo fornecido n�o criado
*
*	   Se CondRet = GRA_CondRetConteudoNulo
*	   String fornecida vazia
*
*	   Se CondRet = GRA_CondRetOK
*      Valor do conte�do do v�rtice corrente do grafo alterado
*
***********************************************************************/

GRA_tpCondRet GRA_MudarNomeVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

/***********************************************************************
*
*  $FC Fun��o: GRA Inserir v�rtice na lista de origens
*
*  $ED Descri��o da fun��o
*      Insere o v�rtice corrente na lista de origens
*      do grafo fornecido.
*     
*
*  $EP Par�metros
*      pGrafo - Ponteiro para o grafo contendo o v�rtice corrente
*      IdVert - Char contendo o conteudo de ID do v�rtice corrente     
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE O grafo deve possuir v�rtice com id igual ao fornecido
*      Grafo deve estar iniciado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*	   Nenhum v�rtice com este id foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      V�rtice inserido na lista de origens do grafo
*
***********************************************************************/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char * IdVert);


/***********************************************************************
*
*  $FC Fun��o: GRA Criar Aresta
*
*  $ED Descri��o da fun��o
*      Ao receber dois char, a fun��o procura os v�rtices correspondentes.
*      O primeiro representa a origem e portanto a aresta ser� criada e inserida
*      na lista de sucessores deste v�rtice. A aresta apontar� para o v�rtice
*      do segundo par�metro, o destino, que tamb�m insere o v�rtice origem 
*      em sua respectiva lista de antecessores.
*     
*
*  $EP Par�metros
*      pVertOrig - Id do v�rtice de origem
*      pvertDest - id do v�rtice de destino
*      pGrafo    - Grafo que cont�m estes v�rtices
*      String    - Nome que ser� inserido em aresta     
*
*  $FV Valor retornado
*      GRA_CondRetFaltouMemoria
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo j� deve ter sido iniciado
*      Os v�rtices fornecidos devem fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetFaltouMemoria
*	   Aresta n�o criada por falta de mem�ria
*
*      Se CondRet = GRA_CondRetNaoAchou
*      Um dos v�rtices fornecidos n�o foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta criada com sucesso fazendo a liga��o entre v�rtices
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo, char * String);

/***********************************************************************
*
*  $FC Fun��o: GRA Excluir Aresta
*
*  $ED Descri��o da fun��o
*      Excluir a aresta que faz a liga��o entre os v�rtices fornecidos.
*      Excluir tamb�m a rela��o da lista de antecessores da lista do v�rtice destino.
*     
*
*  $EP Par�metros
*      pVertOrig - Id do v�rtice de origem
*      pvertDest - id do v�rtice de destino
*      pGrafo    - Grafo que cont�m estes v�rtices    
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo j� deve ter sido iniciado
*      Os v�rtices fornecidos devem fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      Um dos v�rtices fornecidos n�o foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta exclu�da com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Fun��o: GRA Definir v�rtice corrente
*
*  $ED Descri��o da fun��o
*      Procura o v�rtice com base no id fornecido e seta este como corrente
*      do grafo.
*     
*
*  $EP Par�metros
*      pGrafo    - Grafo que cont�m o v�rtice  
*      IdVert    - id do v�rtice a ser usado
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo j� deve ter sido iniciado
*      O v�rtices fornecido deve fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      O v�rtice fornecido n�o foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      V�rtice setado como corrente
*
***********************************************************************/

GRA_tpCondRet GRA_DefinirCorrente( GRA_tppGrafo pGrafo , char * IdVert);


/***********************************************************************
*
*  $FC Fun��o: GRA Destruir grafo
*
*  $ED Descri��o da fun��o
*      Destr�i o grafo fornecido como par�metro
*     
*
*  $EP Par�metros
*      pGrafo    - Grafo a ser exclu�do
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo j� deve ter sido iniciado
*      A lista de Origens e V�rtices n�o deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido n�o foi criado ou est� nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Grafo exclu�do com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo);

/*

*/
GRA_tpCondRet GRA_ObterVertice(GRA_tppGrafo pGrafo , void ** pValor);

GRA_tpCondRet GRA_IrInicio(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_BuscaIdVertice(GRA_tppGrafo pGrafo , char ** pValor);
GRA_tpCondRet GRA_AvancarCorrenteVert(GRA_tppGrafo pGrafo , int val);
GRA_tpCondRet GRA_NumeroVertices(GRA_tppGrafo pGrafo , int * val);

GRA_tpCondRet GRA_SetarCorrente(GRA_tppGrafo pGrafo , char * pValor);

GRA_tpCondRet GRA_InsereConteudoVertice(GRA_tppGrafo pGrafo , void * pConteudo);

GRA_tpCondRet GRA_PegaConteudo(GRA_tppGrafo pGrafo , void ** pConteudo);

#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: M�dulo grafo **********/

#else
#endif
