
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
 * Descrição: Implementação da Classe CImage (Imagens do Jogo)                 *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CImage.h"



CImage::CImage(const char *spFile, bool transparent)
{
	Set_Image(spFile);
	SR_Rect.x = 0;
	SR_Rect.y = 0;
	SR_Rect.w = SS_p_Image->w;
	SR_Rect.h = SS_p_Image->h;

	Set_DisplayFormat();

	if (transparent)
		Set_Transparence();
}

CImage::CImage(const char *spFile, int iX, int iY, bool transparent)
{
	Set_Image(spFile);
	SR_Rect.x = iX;
	SR_Rect.y = iY;
	SR_Rect.w = SS_p_Image->w;
	SR_Rect.h = SS_p_Image->h;

	Set_DisplayFormat();

	if (transparent)
        Set_Transparence();
}


CImage::CImage(const char *spFile, int iX, int iY, int iW, int iH, bool transparent)
{
	Set_Image(spFile);
	SR_Rect.x = iX;
	SR_Rect.y = iY;
	SR_Rect.w = iW;
	SR_Rect.h = iH;

	Set_DisplayFormat();

    if (transparent)
        Set_Transparence();
}


void CImage::Set_Image(const char *spFile)
{
	// Sistema de tratamento de erro apenas temporario!
	if((SS_p_Image = IMG_Load(spFile)) == NULL)
	{
		std::cerr << "Erro ao abrir o arquivo: " << spFile << std::endl;
		exit(-1);
	}
}

void CImage::Set_Image(SDL_Surface *SS_p_Image)
{
	SS_p_Image = SS_p_Image;
}


void CImage::Set_DisplayFormat()
{
    SS_p_Image = SDL_DisplayFormat(SS_p_Image);
}

void CImage::Draw(SDL_Surface *SS_p_Dest)
{
	SDL_BlitSurface(SS_p_Image, NULL, SS_p_Dest, &SR_Rect);
}

void CImage::Draw(SDL_Surface *SS_p_Dest, SDL_Rect *local)
{
	SDL_BlitSurface(SS_p_Image, &SR_Rect, SS_p_Dest, local);
}

void CImage::Set_Transparence()
{
   SDL_SetColorKey(SS_p_Image, (SDL_SRCCOLORKEY | SDL_RLEACCEL | SDL_HWACCEL), g_uiColorKey);
}

SDL_Surface* CImage::GetSubImage(int iX, int iY, int iW, int iH)
{
	SDL_Rect SR_Cut = { iX, iY, iW, iH };

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		SDL_Surface* SS_p_SubIMG = SDL_CreateRGBSurface(SDL_SWSURFACE, iW, iH,
														32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	#else
		SDL_Surface* SS_p_SubIMG = SDL_CreateRGBSurface(SDL_SWSURFACE, iW, iH,
														32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	#endif

	SDL_BlitSurface(SS_p_Image, &SR_Cut, SS_p_SubIMG, NULL);

	return SS_p_SubIMG;
}

void CImage::DrawSubImage(SDL_Surface *SS_p_Dest, SDL_Rect *SR_Source, SDL_Rect *SR_Dest)
{
	SDL_BlitSurface(SS_p_Image, SR_Source, SS_p_Dest, SR_Dest);
}

CImage::~CImage()
{
	SDL_FreeSurface(SS_p_Image);
}
