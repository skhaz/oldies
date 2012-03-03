
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
 * Descri��o: Defini��o da Classe das Telas de Loading                         *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#include "CLoadScreen.h"


CLoadScreen::CLoadScreen()
{
	char sFile[STD_BUF];
	Screen = new CImage("data/screens/loading.jpg", false);
	Screen->Set_DisplayFormat();

	for(int i=0; i <= MAX_BARS; i++)
	{
		snprintf(sFile, STD_BUF, "data/bars/Bar_XPanim%04d.png", i);
		Bars[i] = new CImage(sFile, false);
		Bars[i]->Set_DisplayFormat();
	}

}

void CLoadScreen::Draw(SDL_Surface* SS_p_Dest)
{
	static int iCount = 0;
	SR_Local.x = SR_Local.y = 0;
	Screen->Draw(SS_p_Dest, &SR_Local);

	SR_Local.x = 272;
	SR_Local.y = 550;
	Bars[iCount]->Draw(SS_p_Dest, &SR_Local);

	iCount++;
	if(iCount >= MAX_BARS)
		iCount = 0;
}

CLoadScreen::~CLoadScreen()
{
	for(int i=0; i <= MAX_BARS; i++)
		delete Bars[i];

	delete Screen;
}
