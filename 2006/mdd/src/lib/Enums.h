
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
 * Versão deste documento: 0.02 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Repositorio das listas enumeradas (Enums) do jogo                *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _Enum_h
#define _Enum_h



/*
 *	DOWN - Baixo || LEFTDOWN - Diagonal Esquerda Baixa || LEFT  - Esquerda
 *	LEFTUP - Diagonal Esquerda Alta ||  Up - Alto
 *	RIGHTDOWN - Diagonal Direita Baixa || RIGHT - Direita  || RIGHTUP - Diagonal Direita Alta
 *	STOPED - Parado
 */

typedef enum eSide {	DOWN		=  0, LEFTDOWN 		=  1, LEFT			 = 2,
						LEFTUP		=  3, UP 			=  4,
						RIGHTDOWN	=  5, RIGHT 		=  6, RIGHTUP		 = 7,
						STOP_DOWN	=  8, STOP_LEFTDOWN =  9, STOP_LEFT		 = 10,
						STOP_LEFTUP = 11, STOP_UP 		= 12, STOP_RIGHTDOWN = 13,
						STOP_RIGHT	= 14, STOP_RIGHTUP	= 15 };


#endif // _Enum_h
