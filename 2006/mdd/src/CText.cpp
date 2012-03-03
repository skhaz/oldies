
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
 * Versão deste documento: 0.05 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CText - Textos do Jogo (ainda não pronto)*
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CText.h"



CText::CText(SDL_Color cor, SDL_Rect local)
{
    SC_TextColor = cor;
    SR_TextPosition = local;
}

void CText::Draw(char *texto, TTF_Font *fonte,SDL_Surface *destino)
{
    SDL_Surface *SS_p_Text;
    SS_p_Text = TTF_RenderText_Blended(fonte,(const char *)texto,SC_TextColor);
	SR_Rect.x = SR_Rect.y = 0;
	SR_Rect.h = SS_p_Text->h;
	SR_Rect.w = SS_p_Text->w;
    SDL_BlitSurface(SS_p_Text,&(this)->SR_Rect,destino,&(this)->SR_TextPosition);
    SDL_FreeSurface(SS_p_Text);
}

CText::~CText()
{   ;   }
