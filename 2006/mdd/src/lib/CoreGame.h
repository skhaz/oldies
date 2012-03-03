
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Drag�es - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Vers�o da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Vers�o deste documento: 0.04 (12/03/06)                                     *
 * Responsavel da Vers�o: Equipe MDD                                           *
 * Descri��o: Declara��o das Fun��es Principais do CoreGame (N�cleo do Jogo)   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CoreGame_h
#define _CoreGame_h

#include "Globals.h"
#include "GameClasses.h"



extern void InitSDL(const char *title, const char* icon);	/* Inicializa a Janela e Vari�veis do SDL
															 * 1� Inicializa o SDL e o SDL_TTF
															 * 2� Seta Resolu��o do Video
															 * 3� Esconde o Cursor do Mouse
															 */


extern void InitGame(void);  /* Inicializa as Vari�veis do Jogo
							  * 1� L� as Imagens (lib/engine/imagem.h)
							  * 2� Seta Posi��o Inicial da Bola de Fogo
							  * 3� Posiciona Personagem
							  * 4� Posiciona NPC
							  * 5� Posiciona Texto
							  */


extern void InitGui(void);	/* Inicializa as Vari�veis da GUI (temporaio)
							 * 1� Configura Guichan
							 */


extern void DrawGame(SDL_Surface *SS_p_Dest, bool bShowWeapowPainel);	/* Desenha a Cena do Jogo
																		 * 1� Desenha o BackGround (os 4 Layers)
																		 * 2� Os Personagens
																		 */
extern void ShowLoad(void);

extern void MainLoop(void);	/* Loop Principal do Jogo
							 * 1� Verifica as Entradas do Sistema
							 * 2� Atualiza o Tick
							 * 3� Limpa a Tela e Desenha as Novas Informa��es
							 * 4� Calcula FPS
							 */


extern void ShowCredits(void);	/* Mostra os Cr�ditos do Jogo
								 * 1� Cria uma Imagem de Cr�ditos
								 * 2� Mostra ela na Tela
								 * 3� Limpa a Mem�ia
								 */

extern void HaltGui(void);	/* Deleta a GUI
							 */

extern void ExitGame(void);		/* Saida do Jogo
								 * 1� Descarrega da Mem�ria Todos os Tiles do Mapa
								 * 2� Descarrega da Mem�ria Todos os Itens
								 * 3� Descarrega da Mem�ria Todos os Personagens
								 * 4� Descarrega da Mem�ria a Tela do Jogo
								 * 5� Descarrega da Mem�ria a Fonte do Jogo
								 * 6� Descarrega da Mem�ria Temp (?)
								 * 7� Descarrega da Mem�ria TempPar (?)
								 * 8� Descarrega da Mem�ria a Tela de Cr�ditos
								 */



#endif // _CoreGame_h
