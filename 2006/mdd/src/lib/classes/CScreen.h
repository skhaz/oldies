
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Drag�es - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Vers�o da Engine: 0.0.1C                                                    *
 *                                                                             *
 * Vers�o deste documento: 0.04 (12/03/06)                                     *
 * Resp�nsavel da Vers�o: Equipe MDD                                           *
 * Descri��o: Defini��o da Classe da Tela do Jogo                              *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#ifndef _CScreen_h
#define _CScreen_h

#include "../Globals.h"


class CScreen
{
	private:
		SDL_Surface* SS_p_Screen;
		Uint32 uiWidth,
			   uiHeight,
			   uiBPP,
			   uiFlags;

	public:
		CScreen(Uint32 W, Uint32 H, Uint32 BPP, Uint32 Flags);
		CScreen(Uint32 W, Uint32 H, Uint32 BPP, Uint32 Flags, const char* CC_p_Title);
		CScreen(Uint32 W, Uint32 H, Uint32 BPP, Uint32 Flags, const char* CC_p_Title, const char* CC_p_Icon);

		SDL_Surface* GetScreen();
		void SetVideoMode();
		Uint32 GetFlags();
		void Flip();
		void Clear();
		void ToggleFullScreen();
		int GetWidth();
		int GetHeight();
		int GetDepth();
		void Debug();
		int Save(void);
		~CScreen();

};


#endif // _CScreen_h
