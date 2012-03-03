
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Drag�es - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * eMail: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Vers�o da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Vers�o deste documento: 0.02 (12/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Defini��o da Classe das Telas de Loading                         *
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
