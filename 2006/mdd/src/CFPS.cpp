
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
 * Versão deste documento: 0.05 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CFPS (Frame Per Second)                  *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "lib/classes/CFPS.h"




CFPS::CFPS(int target)
{
	iFpsTarget	 = 0;
	fFps 		 = 0.0f;
	uiFrames	 = 0;
	uiStart		 = 0;

	iFpsTarget	 = target;
	uiStart		 = SDL_GetTicks();
}

float CFPS::GetFPS(void)
{
	return fFps;
}

void CFPS::FPSProcess(void)
{
	uiFrames++; // Incrementa a quantidade de frames
	fFps = (float)uiFrames / (SDL_GetTicks() - uiStart) * 1000.0; // Calcula o FPS
}

void CFPS::ChangeFPS(int valor)
{
    if ((iFpsTarget + valor <= FPS_MAX) && (iFpsTarget + valor >= FPS_MIN))
		iFpsTarget += valor;
}

Uint32 CFPS::Delay()
{
	// Tenta estabilizar o FPS
	if((int)fFps <= FPS - 7)
		ChangeFPS(10);

	if((int)fFps >= FPS + 7)
		ChangeFPS(-10);

	return (1000/iFpsTarget);
}

CFPS::~CFPS(void)
{   ;   }
