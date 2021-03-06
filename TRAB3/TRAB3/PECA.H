#if ! defined( PECA_ )
#define PECA_
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
*  $ED Descri��o do m�dulo
*     O presente m�dulo implementa a cria��o e manipula��o de estruturas 
*     do tipo pe�a para tabuleiro.
*	  Podem existir n tipos de pe�as em um tabuleiro simultaneamente.
*     Al�m do tipo de pe�as, podem existir n pe�as de tipo repetido.
*
***************************************************************************/
 
#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pe�a */
typedef struct PEC_tagElemPeca * PEC_tppPeca ;


/**************************************************************************
*
*  $TC Tipo de dados: PEC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da pe�a
*
**************************************************************************/

typedef enum {

	 PEC_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 PEC_CondRetPecaNula = 1 ,
	 	   /* Pe�a nula */

	 PEC_CondRetFaltouMemoria = 9
		   /* Faltou mem�ria ao tentar criar um elemento de pe�a */

} PEC_tpCondRet ;


/***************************************************************************
*
*  $FC Fun��o: PEC Criar pe�a
*
*  $ED Descri��o da fun��o
*     Inicia uma pe�a com elementos diagonal, reta, quantidade e nome.
*
*  $EP Par�metros
*     pPeca - Refer�ncia para a pe�a que ser� criada.
*     Diag  - Se a pe�a pode se mover para diagonais;
*             Valor igual a 1 se for poss�vel esse tipo de movimento;
*             Valor igual a 0 se n�o for poss�vel;
*     Reta  - Se a pe�a pode se mover horizontalmente e verticalmente;
*             Valor igual a 1 se for poss�vel esse tipo de movimento;
*             Valor igual a 0 se n�o for poss�vel;
*     Qtde  - N�mero de casas que ele pode se movimentar para diagonal 
*             ou horizontal/vertical;
*     Nome  - String com o nome da pe�a que ser� criada;
*     
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*      Diag � valor inteiro 0 ou 1;
*      Reta � valor inteiro 0 ou 1;
*      Qtde � valor inteiro entre 1 e 7;
*      String com 2 caracteres;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Pe�a criada com sucesso;
*
*	   Se CondRet = PEC_CondRetFaltouMemoria
*	   Pe�a n�o foi criada por falta de mem�ria;
*
**************************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , 
                            int Qtde, char * Nome);


/**************************************************************************
*
*  $FC Fun��o: PEC Obter nome
*
*  $ED Descri��o da fun��o
*     Retorna por par�metro o pe�a nome.
*
*  $EP Par�metros
*     pPeca - Refer�ncia para a pe�a da qual ser� retornado o valor.
*     NomePeca - Ponteiro para o qual ser� retornado o nome da pe�a.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da pe�a tem que ser uma string n�o nula.
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve nome da pe�a com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Pe�a nula, n�o retorna nada no NomePeca;
*
***********************************************************************/

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void **NomePeca);


/***********************************************************************
*
*  $FC Fun��o: PEC Obter dados do tipo pe�a
*
*  $ED Descri��o da fun��o
*     Retorna por par�metros o Nome, a Diag, a Reta e a Qtde de pPeca.
*
*  $EP Par�metros
*     pPeca - Refer�ncia para a pe�a da qual ser�o retornados 
*             os elementos.
*     Nome  - Ponteiro para o qual ser� retornado o pe�a Nome.
*     Diag  - Ponteiro para o qual ser� retornado o pe�a Diag.
*     Reta  - Ponteiro para o qual ser� retornado o pe�a Reta.
*     Qtde  - Ponteiro para o qual ser� retornado o pe�a Qtde.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da pe�a tem que ser uma string n�o nula.
*      Diag, Reta e Qtde da vari�vel de tipo PEC_tppPeca tem que
*      n�o nulos, valores inteiros.
*      Diag e Reta da pPeca valores inteiros entre 0 e 1;
*      Qtde da pPeca valor inteiro entre 1 e 7;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve Nome, Diag, Reta e Qtde com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Pe�a nula, n�o pode retornar elementos da pPeca;
*
***********************************************************************/

PEC_tpCondRet PEC_ObterDadosTipoPeca (PEC_tppPeca pPeca , void ** Nome, 
                                     int * Diag , int * Reta , 
                                     int * Qtde);

#undef PECA_EXT

/******** Fim do m�dulo de defini��o: PEC  Peca do tabuleiro **********/

#else
#endif
