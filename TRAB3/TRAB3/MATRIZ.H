#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
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
*       1.00   afv   29/08/2013 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     .......
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma matriz */

typedef struct MAT_tgMatriz * MAT_tppMatriz ;

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tpMatLista ;

/* Tipo refer�ncia para um grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/* Tipo refer�ncia para um grafo */

typedef struct tagVerticeGrafo * GRA_tppVerGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

        MAT_CondRetOK = 0 ,
            /* Executou correto */

        MAT_CondRetNaoCriouRaiz = 1 ,
            /* N�o criou n� raiz */

        MAT_CondRetErroEstrutura = 2 ,
            /* Estrutura da matriz est� errada */
			
        MAT_CondRetMatrizNaoExiste = 3 ,
            /* Matriz n�o existe */

        MAT_CondRetMatrizVazia = 4 ,
            /* Matriz est� vazia */

        MAT_CondRetNohEhRaiz = 5 ,
            /* N� corrente � raiz */

		MAT_CondRetNaoPossuiNo = 6 ,
            /* No nao encontrado */

		MAT_CondRetMatrizCheia  = 7 ,
            /* Faltou espa�o para inserir listas */

		 MAT_CondRetListaVazia = 8 ,
            /* Lista est� vazia */		

        MAT_CondRetFaltouMemoria = 9 ,
            /* Faltou mem�ria ao alocar dados */

		MAT_CondRetNoMatrizSemLista = 10 ,
            /* No nao possui lista */
			
		MAT_CondRetNoListaDiferente = 11
            /* Lista nao corresponde a corrente */

} MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: MAT Criar matriz
*
*  $ED Descri��o da fun��o
*     Cria uma nova matriz vazia.
*     Caso j� exista uma matriz, esta ser� destru�da.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

MAT_tpCondRet MAT_CriarMatriz(MAT_tppMatriz* tpMatrizModulo, GRA_tppGrafo pGrafo, int numElementos);

/***********************************************************************
*
*  $FC Fun��o: MAT Inserir Lista na matriz corrente
*
*  $ED Descri��o da fun��o
*     Insere uma lista na matriz corrente
*
*  $FV Valor retornado
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetMatrizVazia
*	  MAT_CondRetOK
*	  MAT_CondRetMatrizCheia
*
***********************************************************************/

MAT_tpCondRet MAT_InsereListaMatriz( GRA_tppVerGrafo lt, MAT_tppMatriz tpMatrizModulo);

/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� norte
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoNorte(MAT_tppMatriz tpMatrizModulo);


/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� nordeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoNordeste(MAT_tppMatriz tpMatrizModulo) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� leste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoLeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� sudeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoSudeste(MAT_tppMatriz tpMatrizModulo) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� sul
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoSul(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� sudoeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoSudoeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� oeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoOeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Ir para n� noroeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoNoroeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Obter valor corrente
*
*  $EP Par�metros
*     $P ValorParm - � o par�metro que receber� o valor contido 
* 	 				 no ponteiro da lista
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_ObterListaCorr( GRA_tppVerGrafo lst_valor  , MAT_tppMatriz tpMatrizModulo ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir raiz
*
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*	  MAT_CondRetOK
*     MAT_CondRetNohEhRaiz
*
***********************************************************************/

MAT_tpCondRet MAT_IrRaiz( MAT_tppMatriz tpMatrizModulo );

#undef MATRIZ_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
