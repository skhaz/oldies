
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
 * Descrição: Implementação da classe CTile                                    *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CTile.h"



CTile::CTile(char* filename, SDL_Rect SR_Dest, bool walkeable)
{
	Tile = new CImage(filename, true);
	SR_Region = SR_Dest;

	bVisible = false;
	iFrames = 0;
	bWalkeable = walkeable;
}

CTile::CTile(char* filename, SDL_Rect SR_Dest, bool walkeable, int frames)
{
	Tile = new CImage(filename, true);
	SR_Region = SR_Dest;

	bVisible = false;
	iFrames = frames;
	iFrameCount = 0;
	bWalkeable = walkeable;
}

void CTile::Draw(SDL_Surface* SS_p_Dest)
{

	if(iFrames)
	{
		iFrameCount++;

		if(iFrameCount <= iFrames)
		iFrameCount = 0;
	}

	// Se o tile estiver visivel, o blita
	if(Visible())
	Tile->Draw(SS_p_Dest, &SR_Region);
}

SDL_Rect CTile::Region()
{
	return SR_Region;
}

bool CTile::Visible()
{
	if((SR_Region.x + SR_Region.w) <= (int)g_uiWWindow)
	bVisible = true;

	if((SR_Region.y + SR_Region.h) <= (int)g_uiHWindow)
	bVisible = true;

	return bVisible;
}

void CTile::GotoFrame(int frame)
{
	iFrameCount = frame;
}

CTile::~CTile()
{
	delete(Tile);
}
