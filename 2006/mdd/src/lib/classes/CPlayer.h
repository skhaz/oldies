
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *         2006 - Projeto MDD - Mundo dos Drgões - Um MMORPG Opensource        *
 *                                                       by <<Striker>>        *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * eMail: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Versão da Engine: 0.0.1C                                                    *
 *                                                                             *
 * Versão deste documento: 0.04 (01/03/06)                                     *
 * Responsavel da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CPlayer (herdado pelas Classes, Virtual) *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#ifndef _CPlayer_h
#define _CPlayer_h

#include "../Globals.h"
#include "CImage.h"

class CPlayer
{
    private:
        Uint8   ui8Streght,
                ui8Dextrerity,
                ui8Speed,
                ui8Constitution,
                ui8Wisdow,
                ui8Luck,
                ui8Attack,
                ui8Deffence,
                ui8AttackSpeed,
                ui8MagicAttack,
                ui8RechargeTax,
                ui8ElementalDamage,
                ui8Weight;

        Uint16  ui16XP,
                ui16HP,
                ui16MP;

        CImage *Tiles[72];

        eSide PlayerDirection;
        int iControlTile;
        SDL_Rect SR_RectPlayer,
				 SR_PosPlayer;

    public:
        CPlayer(const char *path);
        SDL_Rect GetRect(void);
        void Direction(eSide lado);
        eSide GetDirection(void);
        void WalkPlayer(void);
        void DrawPlayer(SDL_Surface *destino);
        ~CPlayer();
};

#endif // _CPlayer_h
