
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
 * Vers�o deste documento: 0.02 (01/03/06)                                     *
 * Responsavel da Vers�o: Equipe MDD                                           *
 * Descri��o: Defini��o da Classe dos Textos                                   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#ifndef _CText_h
#define _CText_h

#include "../Globals.h"


class CText
{
    protected:
        SDL_Color   SC_TextColor;       // Cor do Texto
        SDL_Rect    SR_TextPosition;    // Posi��o na Tela
        SDL_Rect    SR_Rect;            // Ret�ngulo da Imagem
    public:
        CText(SDL_Color cor, SDL_Rect local);
        void Draw(char *texto, TTF_Font *fonte, SDL_Surface *destino);
        ~CText();
};

#endif // _CText_h
