

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
 * Versão deste documento: 0.03 (01/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CPlayer (Jogador)                        *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CPlayer.h"



CPlayer::CPlayer(const char *path)
{
	char str[STD_BUF];
	iControlTile = 0;
	for (int iFor = 1; iFor < 89; iFor++)
	{
		if ((iFor == 9) || (iFor == 19) || (iFor == 29)
		|| (iFor == 39) || (iFor == 49) || (iFor == 59)
        || (iFor == 69) || (iFor == 79))
            iFor++;
        else
        {
			snprintf(str, STD_BUF, "%s/img%d.png", path, iFor);
			Tiles[iControlTile] = new CImage(str, true);

			iControlTile++;
        }
    }
    ui8Streght = ui8Dextrerity = ui8Speed = ui8Constitution = ui8Wisdow = 0;
    ui8Luck = ui8Attack = ui8Deffence = ui8AttackSpeed = ui8MagicAttack = 0;
    ui8RechargeTax = ui8ElementalDamage = ui8Weight = 0;

    ui16XP = ui16HP = ui16MP = 0;
    SR_RectPlayer.x = 10;
    SR_RectPlayer.y = 10;
    SR_RectPlayer.w = SR_RectPlayer.h = 0;
    PlayerDirection = STOP_DOWN;
    iControlTile = iControlTile = 64 + (PlayerDirection - 8);

	SR_PosPlayer.x = g_uiWWindow/2 - 64;
	SR_PosPlayer.y = g_uiHWindow/2 - 64;
}

CPlayer::~CPlayer()
{
    for (int iFor=0;iFor < 64; iFor++)
        delete(Tiles[iFor]);
}

void CPlayer::Direction(eSide lado)
{
    if (lado != PlayerDirection) // Caso Mude de Diração, Posicionar Tile no Lugar Certo
    {
        PlayerDirection = lado;
        if (PlayerDirection < STOP_DOWN)
            iControlTile = (PlayerDirection*8);
        else             // 64 é o ultimo Tile  com a movimentação normal
            iControlTile = 64 + (PlayerDirection - 8);
    }
}

SDL_Rect CPlayer::GetRect(void)
{
    return SR_RectPlayer;
}

void CPlayer::DrawPlayer(SDL_Surface *destino)
{
    this->WalkPlayer();
    Tiles[iControlTile]->Draw(destino,&SR_PosPlayer);

    if (PlayerDirection < STOP_DOWN)
    {
        iControlTile++;
        if (iControlTile >= ((PlayerDirection+1)*8))
            iControlTile = (PlayerDirection*8);
    }
}

eSide CPlayer::GetDirection(void)
{
    return PlayerDirection;
}

void CPlayer::WalkPlayer(void)
{
    switch(PlayerDirection)
    {
        case DOWN:
            SR_RectPlayer.y -=5;
            break;
        case LEFT:
            SR_RectPlayer.x +=5;
            break;
        case UP:
            SR_RectPlayer.y +=5;
            break;
        case RIGHT:
            SR_RectPlayer.x -=5;
            break;
        case RIGHTUP:
            SR_RectPlayer.y +=5;
            SR_RectPlayer.x -=5;
            break;
        case RIGHTDOWN:
            SR_RectPlayer.x -=5;
            SR_RectPlayer.y -=5;
            break;
        case LEFTUP:
            SR_RectPlayer.x +=5;
            SR_RectPlayer.y +=5;
            break;
        case LEFTDOWN:
            SR_RectPlayer.x +=5;
            SR_RectPlayer.y -=5;
            break;
        case STOP_DOWN:
        case STOP_LEFTDOWN:
        case STOP_LEFT:
        case STOP_LEFTUP:
        case STOP_UP:
        case STOP_RIGHTDOWN:
        case STOP_RIGHT:
        case STOP_RIGHTUP:
        default:
            break;
    }
}
