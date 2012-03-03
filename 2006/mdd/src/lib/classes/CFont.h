
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
 * Vers�o deste documento: 0.03 (12/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Declara��o da classe CFont                                       *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef _CFont_h
#define _CFont_h

#include "../Globals.h"



class CFont
{
    private:
        TTF_Font* TTF_p_Font;

    public:
        CFont(const char* spFilename, int iSize);
        TTF_Font* CFont::GetFont();
		~CFont();
};

#endif // _CFont_h
