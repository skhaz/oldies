
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
 * Vers�o deste documento: 0.02 (12/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Reposit�rio das Variaveis Globais do Jogo                        *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _Globals_h
#define _Globals_h

#include "Libraries.h"		// Todas as bibliotecas 'padr�es'
#include "SDL_All.h"		// Includes usadas pela biblioteca SDL
#include "Guichan_All.h"	// Includes usadas pela biblioteca Guichan
#include "Definitions.h"	// Todas as Defini��es (define)
#include "Enums.h"			// Todas as listas enumumeradas utilizadas(enum)
#include "Types.h"			// Todos os tipos defindos (typedef)


// V A R S   G L O B A L S
extern unsigned int	g_uiWWindow,	// Largura da Janela (width)
					g_uiHWindow,	// Altura da Janela (height)
					g_uiBPPWindow,	// Profundida de cores (bpp)
					g_uiFlags,		// Flags usadas para iniciar a SDL
					g_uiColorKey;	// A cor que ser� usada para trasparencia

extern bool g_bHaveAudio;		// Booleano para abilitar ou desabilitar o audio
extern int  g_iMixerFrequency,	// Frequencia usada no mixer (padr�o 44100)
		    g_iMixerChannels;	// Numero de canais usado no mixer (padr�o 2)


// V A R S   C O N S T S
static const char *g_spAPPName		= "MDD - Mundo dos Drag�es",	// Nome do MDD (duh!)
				  *g_spAPPVersion	= "0.0.2b",						// Vers�o do MDD
				  *g_spAPPIcon		= "data/icons/MDD_Icon.png";	// O Icone da janela



#endif // _Globals_h
