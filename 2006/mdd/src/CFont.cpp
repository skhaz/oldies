
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
 * Vers�o deste documento: 0.04 (12/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Implementa��o da Classe CFont (Fonte do Texto)                   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CFont.h"



CFont::CFont(const char *spFilename, int iSize)
{
    TTF_p_Font = TTF_OpenFont(spFilename, iSize);
}

TTF_Font* CFont::GetFont()
{
    return TTF_p_Font;
}

CFont::~CFont()
{
    TTF_CloseFont(TTF_p_Font);
}
