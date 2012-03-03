
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
 * Versão deste documento: 0.04 (23/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CInput - Entrada do Teclado               *
 * Colaboração: David Ferreira e Silveira Neto                                 *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "lib/classes/CInput.h"



CInput::CInput()
{   ;    }


void CInput::UpdateInput()
{
    static SDL_Event SE_Event;
    SDL_PollEvent(&SE_Event);
    InputType = SE_Event.type;
}

void CInput::Flush()
{
	//fflush(stdin);
}

Uint8* CInput::Set_Keys()
{
    return SDL_GetKeyState(NULL);
}

CInput::~CInput()
{       ;       }
