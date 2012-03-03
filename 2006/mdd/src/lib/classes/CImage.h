
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
 * Versão deste documento: 0.04 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Declaração da Classe CImage (Imagens do Jogo)                    *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CImage_h
#define _CImage_h

#include "../Globals.h"



class CImage
{
    protected:
        SDL_Surface* SS_p_Image;
        SDL_Rect     SR_Rect;

    public:
		CImage(const char *spFile, bool transparent = false);
		CImage(const char *spFile, int iX, int iY, bool transparent = false);
		CImage(const char *spFile, int iX, int iY, int iW, int iH, bool transparent = false);

		void Set_Image(const char *spFile);
		void Set_Image(SDL_Surface *SS_p_Image);
		void Set_DisplayFormat();
		void Draw(SDL_Surface *SS_p_Dest);
		void Draw(SDL_Surface *SS_p_Dest, SDL_Rect *local);
		void Set_Transparence();
		SDL_Surface* GetSubImage(int iX, int iY, int iW, int iH);
		void DrawSubImage(SDL_Surface *SS_p_Dest, SDL_Rect *SR_Source, SDL_Rect *SR_Dest);
		~CImage();
};

#endif // _CImage_h
