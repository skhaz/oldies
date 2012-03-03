
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
 * Versão deste documento: 0.05 (21/03/06)                                     *
 * Responsavel da Versão: Equipe MDD                                           *
 * Colaboração: David Ferreira e Silveira Neto                                 *
 * Descrição: Declaração da classe CMap                                        *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CInput_h
#define _CInput_h

#include "../Globals.h"



class CInput
{
    private:
        bool bF1,		// Bool do F1
			 bF5,		// Bool do F5
			 bF6,		// Bool do F6
			 bLeft,		// Bool do Left
			 bRight,	// Bool do Right
			 bUp,		// Bool do Up
			 bDown;		// Bool do Down

    public:
        Uint8 InputType;   // Armazena Tipo de Entrada (KeyUP, KeyDown)

        CInput();	// Construtor (apenas aponta p_uiTecla para Null)
        bool Get_Key(eSide Lado);
        void Flush(); // Limpa o buffer do teclado
        Uint8* Set_Keys();
        void UpdateInput();	// Pega a Tecla do Buffer e aponta para p_uiTecla
        bool IsInput(SDLKey tecla);	// Verifica se a tecla foi precionada
        ~CInput();	// Destrutor do Input
};


#endif // _CInput_h
