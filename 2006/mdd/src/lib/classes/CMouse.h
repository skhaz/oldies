
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *         2006 - Projeto MDD - Mundo dos Drag�es - Um MMORPG Open-Source      *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Vers�o da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Vers�o deste documento: 0.03 (12/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Defini��o da Classe do Mouse                                     *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CMouse_h
#define _CMouse_h

#include "../Globals.h"
#include "CImage.h"



class CMouse
{
    private:
        int iMouseX, iMouseY;
        Uint8 ui8Button;
        SDL_Rect SR_Region;
		int iCount;
		CImage* Point[MAX_MPOINTS];

	public:
        CMouse(const char* path);
		void Draw(SDL_Surface* SS_p_Dest);
		void Refresh();
        void ShowMouse(bool state);
        void WarpMouse(int iX, int iY);
		void Center();
        int GetX(void);
        int GetY(void);
		Uint8 GetButton();
        ~CMouse();
};

#endif // _CMouse_h
