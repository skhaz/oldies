
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *         2006 - Projeto MDD - Mundo dos Drg�es - Um MMORPG Opensource        *
 *                                                       by <<Striker>>        *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * eMail: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Vers�o da Engine: 0.0.1C                                                    *
 *                                                                             *
 * Vers�o deste documento: 0.03 (01/03/06)                                     *
 * Responsavel da Vers�o: Equipe MDD                                           *
 * Descri��o: Declara��o da classe CTile                                       *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef _CTile_h
#define _CTile_h

#include "../Globals.h"
#include "CImage.h"


class CTile
{
	private:
		CImage* Tile;		// A imagen
		SDL_Rect SR_Region,	// Regi�o, onde esta
				 SR_Rect;	// Usado para recorte de tiles maiores
		bool bVisible;		// Est� visivel ao usuario
		bool bWalkeable;    // Esse tile � andavel?
		int iFrames;		// Quantos frames de anim��o, 0 se nenhum
		int iFrameCount;	// Contador de frames

	public:
		CTile(char* filename, SDL_Rect SR_Dest, bool walkeable);
		CTile(char*  filename, SDL_Rect SR_Dest, bool walkeable, int frames);

		void Draw(SDL_Surface* SS_p_Dest);
		SDL_Rect Region();
		bool Visible();
		void GotoFrame(int frame);

		~CTile();

};


#endif // _CTile_h
