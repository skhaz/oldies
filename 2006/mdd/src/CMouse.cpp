
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Dragões - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Versão da Engine: 0.0.1C                                                    *
 *                                                                             *
 * Versão deste documento: 0.03 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CMouse                                   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CMouse.h"



CMouse::CMouse(const char* path)
{
	char filename[STD_BUF];
	iCount = 0;

    ShowMouse(false);
    Center();

	for (int i=0; i < MAX_MPOINTS; i++)
	{
		snprintf(filename, STD_BUF, "%s/mpoint%02d.png", path, i);
		Point[i] = new CImage(filename, true);
	}
}


void CMouse::Draw(SDL_Surface* SS_p_Dest)
{
	Refresh();
	Point[iCount]->Draw(SS_p_Dest, &SR_Region);

 	iCount++;
	if(iCount >= MAX_MPOINTS)
		iCount = 0;
}

void CMouse::Refresh()
{
	ui8Button = SDL_GetMouseState(&iMouseX, &iMouseY);

	SR_Region.x = iMouseX;
	SR_Region.y = iMouseY;
}

void CMouse::ShowMouse(bool state)
{
    SDL_ShowCursor(state);
}

void CMouse::WarpMouse(int iX, int iY)
{
	SDL_WarpMouse(iX, iY);
}

void CMouse::Center()
{
	WarpMouse(g_uiWWindow/2, g_uiHWindow/2);
}

int CMouse::GetX(void)
{
	return iMouseX;
}

int CMouse::GetY(void)
{
	return iMouseY;
}

Uint8 CMouse::GetButton()
{
	return ui8Button;
}

CMouse::~CMouse()
{
	for (int i=0; i < MAX_MPOINTS; i++)
	delete (Point[i]);
}
