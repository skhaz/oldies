
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Dragões - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Versão da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Versão deste documento: 0.04 (12/03/06)                                     *
 * Responsavel da Versão: Equipe MDD                                           *
 * Descrição: Declaração das Funções Principais do CoreGame (Núcleo do Jogo)   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CoreGame_h
#define _CoreGame_h

#include "Globals.h"
#include "GameClasses.h"



extern void InitSDL(const char *title, const char* icon);	/* Inicializa a Janela e Variáveis do SDL
															 * 1º Inicializa o SDL e o SDL_TTF
															 * 2º Seta Resolução do Video
															 * 3º Esconde o Cursor do Mouse
															 */


extern void InitGame(void);  /* Inicializa as Variáveis do Jogo
							  * 1º Lê as Imagens (lib/engine/imagem.h)
							  * 2º Seta Posição Inicial da Bola de Fogo
							  * 3º Posiciona Personagem
							  * 4º Posiciona NPC
							  * 5º Posiciona Texto
							  */


extern void InitGui(void);	/* Inicializa as Variáveis da GUI (temporaio)
							 * 1° Configura Guichan
							 */


extern void DrawGame(SDL_Surface *SS_p_Dest, bool bShowWeapowPainel);	/* Desenha a Cena do Jogo
																		 * 1º Desenha o BackGround (os 4 Layers)
																		 * 2º Os Personagens
																		 */
extern void ShowLoad(void);

extern void MainLoop(void);	/* Loop Principal do Jogo
							 * 1º Verifica as Entradas do Sistema
							 * 2º Atualiza o Tick
							 * 3º Limpa a Tela e Desenha as Novas Informações
							 * 4º Calcula FPS
							 */


extern void ShowCredits(void);	/* Mostra os Créditos do Jogo
								 * 1º Cria uma Imagem de Créditos
								 * 2º Mostra ela na Tela
								 * 3º Limpa a Memóia
								 */

extern void HaltGui(void);	/* Deleta a GUI
							 */

extern void ExitGame(void);		/* Saida do Jogo
								 * 1º Descarrega da Memória Todos os Tiles do Mapa
								 * 2º Descarrega da Memória Todos os Itens
								 * 3º Descarrega da Memória Todos os Personagens
								 * 4º Descarrega da Memória a Tela do Jogo
								 * 5º Descarrega da Memória a Fonte do Jogo
								 * 6º Descarrega da Memória Temp (?)
								 * 7º Descarrega da Memória TempPar (?)
								 * 8º Descarrega da Memória a Tela de Créditos
								 */



#endif // _CoreGame_h
