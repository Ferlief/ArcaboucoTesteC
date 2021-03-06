#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: ARV  M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.H
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo exemplifica como utilizar os instrumentos disponibilizados
*     pelo arcabou�o.
*     O m�dulo implementa um conjunto de fun��es para criar e explorar
*     um conjunto de zero ou mais �rvores bin�rias.
*     Cada �rvore possui uma cabe�a que referencia o n� raiz e um
*     n� corrente pertencente � �rvore.
*     Cada �rvore � identificada pela refer�ncia (ponteiro) para a sua
*     cabe�a.
*     Uma �rvore poder� estar vazia, ou seja conter zero n�s.
*     Uma �rvore vazia n�o cont�m nem raiz nem n� corrente.
*
***************************************************************************/
 
#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: ARV Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         ARV_CondRetOK = 0 ,
               /* Executou correto */

         ARV_CondRetNaoCriouRaiz = 1 ,
               /* N�o criou n� raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da �rvore est� errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* N�o � folha relativa � dire��o de inser��o desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* �rvore n�o existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* �rvore est� vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* N� corrente � raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* N� corrente n�o possui filho na dire��o desejada */

         ARV_CondRetFaltouMemoria = 8
               /* Faltou mem�ria ao alocar dados */

   } ARV_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: ARV Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaTipoCabeca        =  1 ,
               /* Modifica o tipo da cabe�a */

         DeturpaRaizNula          =  2 ,
               /* Anula ponteiro raiz */

         DeturpaCorrenteNulo      =  3 ,
               /* Anula ponteiro corrente */

         DeturpaRaizLixo          =  4 ,
               /* Faz raiz apontar para lixo */

         DeturpaCorrenteLixo      =  5 ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoNo            =  6 ,
               /* Modifica tipo n� corrente */

         DeturpaPtCabecaNulo      =  7 ,
               /* Anula ponteiro cabe�a */

         DeturpaPtPaiNulo         =  8 ,
               /* Anula ponteiro pai */

         DeturpaPtEsqNulo         =  9 ,
               /* Anula ponteiro filho esquerda */

         DeturpaPtDirNulo         = 10 ,
               /* Anula ponteiro filho direita */

         DeturpaPtCabecaLixo      = 11 ,
               /* Faz ponteiro cabe�a apontar para lixo */

         DeturpaPtPaiLixo         = 12 ,
               /* Faz ponteiro pai apontar para lixo */

         DeturpaPtEsqLixo         = 13 ,
               /* Faz ponteiro filho esquerda apontar para lixo */

         DeturpaPtDirLixo         = 14 ,
               /* Faz ponteiro filho direita apontar para lixo */

         DeturpaValor             = 15 ,
               /* Atribui valor de tamanho 1 byte maior do que o alocado */

         DeturparEspacoCabeca     = 16 ,
               /* Deturpa espa�o da cabeca */

         DeturparEspacoNo         = 17
               /* Deturpa espa�o do n� */

   } ARV_tpModosDeturpacao ;

#endif


/***********************************************************************
*
*  $FC Fun��o: ARV  &Criar �rvore
*
*  $ED Descri��o da fun��o
*     Cria uma nova �rvore vazia.
*
*  $EP Par�metros
*     $P pArvoreParm - par�metro passado por refer�ncia e que receber�
*                      o ponteiro para a �rvore criada.
*                      Se o ponteiro for n�o NULL, a �rvore apontada
*                      ser� destru�da antes de criar a nova.
*                      Receber� NULL se n�o conseguiu alocar a cabe�a.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore( void ** ppArvoreParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Destruir �rvore
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da �rvore.
*     Faz nada caso a �rvore corrente n�o exista.
*
*  $EP Par�metros
*     $P pArvoreParm - refer�ncia para o ponteiro para a cabe�a da �rvore
*                      a ser destru�da. Ao sair receber� NULL.
*                      Se == NULL, faz nada
*
***********************************************************************/

   void ARV_DestruirArvore( void ** ppArvoreParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Adicionar filho � esquerda
*
*  $ED Descri��o da fun��o
*     Adiciona um n� folha � esquerda do n� corrente. O n� corrente
*     n�o deve ter filho � esquerda ao chamar a fun��o,
*
*  $EP Par�metros
*     $P pArvoreParm - ponteiro para a cabe�a da �rvore.
*                      Se a �rvore estiver vazia, � criado o n� raiz.
*                      Se for NULL, retorna ARV_CondRetArvoreNaoExiste
*     $P ValorParm   - valor a ser inserido no novo n�
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetNaoEhFolha      - caso o n� corrente n�o seja folha para a
*                                  esquerda
*     ARV_CondRetErroEstrutura
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirEsquerda( void * pArvoreParm , char ValorParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Adicionar filho � direita
*
*  $ED Descri��o da fun��o
*     Adiciona um n� folha � direita do n� corrente. O n� corrente
*     n�o deve ter filho � direita ao chamar a fun��o,
*
*  $EP Par�metros
*     $P pArvoreParm - ponteiro para a cabe�a da �rvore.
*                      Se a �rvore estiver vazia, � criado o n� raiz.
*                      Se for NULL, retorna ARV_CondRetArvoreNaoExiste
*     $P ValorParm   - valor a ser inserido no novo n�
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetNaoEhFolha      - caso o n� corrente n�o seja folha para a
*                                  direita
*     ARV_CondRetNaoEhFolha      - caso n�o seja folha para a direita
*     ARV_CondRetErroEstrutura
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirDireita( void * pArvoreParm , char ValorParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Ir para n� pai
*
*  $ED Descri��o da fun��o
*     Torna corrente o n� pai do n� corrente.
*     Faz nada se este for a raiz da �rvore, ou se �rvore estiver vazia.
*
*  $EP Par�metros
*     $P pArvoreParm - ponteiro para a cabe�a da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNohEhRaiz
*
***********************************************************************/

   ARV_tpCondRet ARV_IrPai( void * pArvoreParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Ir para n� � esquerda
*
*  $ED Descri��o da fun��o
*     Torna corrente o n� filho � esquerda do n� corrente.
*     Faz nada se n�o existe filho � esquerda, ou se a �rvore estiver vazia.
*
*  $EP Par�metros
*     $P pArvoreParm - ponteiro para a cabe�a da �rvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho � esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoEsquerda( void * pArvoreParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Ir para n� � direita
*
*  $ED Descri��o da fun��o
*     Torna corrente o n� filho � direita do n� corrente.
*     Faz nada se n�o existe filho � direita.
*
*  $EP Par�metros
*     $P pArvoreParm - ponteiro para a cabe�a da �rvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho � direita
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoDireita( void * pArvoreParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Obter valor corrente
*
*  $ED Descri��o da fun��o
*     Retorna o valor contido no n� corrente da �rvore dada.
*     N�o altera o par�metro de retorno (retorna nada) se a �rvore
*     estiver vazia.
*
*  $EP Par�metros
*     $P pArvoreParm - ponteiro para a cabe�a da �rvore.
*     $P ValorParm   - � o par�metro que receber� o valor contido no n�.
*                      Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ObterValorCorr( void * pArvoreParm , char * ValorParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV  &Verificar uma �rvore
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica completamente uma determinada �rvore.
*     Tamb�m marca todos os espa�os por ela ocupados.
*
***********************************************************************/

#ifdef _DEBUG

   ARV_tpCondRet ARV_VerificarArvore( void * pArvoreParm ) ;

#endif


/***********************************************************************
*
*  $FC Fun��o: ARV  &Verificar um n� cabe�a
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade de um n� cabe�a da �rvore.
*
*  $EP Par�metros
*     $P pCabecaParm - ponteiro para um espa�o que deveria ser uma cabe�a
*                      de �rvore.
*
*  $FV Valor retornado
*     Condi��o de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   ARV_tpCondRet ARV_VerificarCabeca( void * pCabecaParm ) ;

#endif


/***********************************************************************
*
*  $FC Fun��o: ARV  &Verificar um n� de estrutura
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade de um n� estrutural da �rvore.
*
*  $EP Par�metros
*     $P pNoParm - ponteiro para espa�o que deveria ser um n� estrutural.
*
*  $FV Valor retornado
*     N�mero de erros encontrados.
*
***********************************************************************/

#ifdef _DEBUG

   ARV_tpCondRet ARV_VerificarNo( void * pNoParm ) ;

#endif


/***********************************************************************
*
*  $FC Fun��o: ARV  &Deturpar �rvore
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Corrompe elementos espec�ficos da estrutura da �rvore.
*     Essa fun��o destina-se a preparar os cen�rios de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da �rvore.
*     Esta fun��o n�o tem prote��o contra erros de uso, consequentemente
*     poder� levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Par�metros
*     $P pArvoreParm  - �rvore a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpa��o
*                       ARV_tpModosDeturpacao identifica os modos de
*                       deturpa��o conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void ARV_Deturpar( void * pArvoreParm ,
                      ARV_tpModosDeturpacao ModoDeturpar ) ;

#endif

#undef ARVORE_EXT

/********** Fim do m�dulo de defini��o: ARV  M�dulo �rvore **********/

#else
#endif
