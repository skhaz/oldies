
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Dragões - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * eMail: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Versão da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Versão deste documento: 0.02 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Definição da Classe das Telas de Loading                         *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CLoadScreen_h
#define _CLoadScreen_h

#include "Globals.h"
#include "classes/CImage.h"



class CLoadScreen
{
	private:
		CImage* Screen;
		CImage* Bars[MAX_BARS];

		SDL_Rect SR_Local;

	public:
		CLoadScreen();
		void Draw(SDL_Surface* SS_p_Dest);
		~CLoadScreen();

};

#endif // _CLoadScreen_h
