
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
 * Descrição: Repositório das Variaveis Globais do Jogo                        *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _Globals_h
#define _Globals_h

#include "Libraries.h"		// Todas as bibliotecas 'padrões'
#include "SDL_All.h"		// Includes usadas pela biblioteca SDL
#include "Guichan_All.h"	// Includes usadas pela biblioteca Guichan
#include "Definitions.h"	// Todas as Definições (define)
#include "Enums.h"			// Todas as listas enumumeradas utilizadas(enum)
#include "Types.h"			// Todos os tipos defindos (typedef)


// V A R S   G L O B A L S
extern unsigned int	g_uiWWindow,	// Largura da Janela (width)
					g_uiHWindow,	// Altura da Janela (height)
					g_uiBPPWindow,	// Profundida de cores (bpp)
					g_uiFlags,		// Flags usadas para iniciar a SDL
					g_uiColorKey;	// A cor que será usada para trasparencia

extern bool g_bHaveAudio;		// Booleano para abilitar ou desabilitar o audio
extern int  g_iMixerFrequency,	// Frequencia usada no mixer (padrão 44100)
		    g_iMixerChannels;	// Numero de canais usado no mixer (padrão 2)


// V A R S   C O N S T S
static const char *g_spAPPName		= "MDD - Mundo dos Dragões",	// Nome do MDD (duh!)
				  *g_spAPPVersion	= "0.0.2b",						// Versão do MDD
				  *g_spAPPIcon		= "data/icons/MDD_Icon.png";	// O Icone da janela



#endif // _Globals_h
