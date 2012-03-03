
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
 * Versão deste documento: 0.03 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Declaração da classe CFPS (Frame Per Secound)                    *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CFPS_h
#define _CFPS_h

#include "../Globals.h"



class CFPS
{
    private:
        int	iFpsTarget;
        float fFps;
        Uint32 uiFrames,
			   uiStart;

    public:
        CFPS(int target);
		float GetFPS();
        void FPSProcess();
        void ChangeFPS(int valor);
        Uint32 Delay();
        ~CFPS();

};

#endif // _CFPS_h
