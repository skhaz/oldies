
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
 * Responsavel da Vers�o: Equipe MDD                                           *
 * Descri��o: Declara��o da classe CMap                                        *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CMap_h
#define _CMap_h

#include "../Globals.h"
#include "CImage.h"

#define MAX_TILES 64 // Quantidade Limitada por enquanto


class CMap
{
	private:
		SDL_Surface* SS_p_Map; 	// O mapa
		SDL_Rect 	 SR_Cam;	// A 'camera'
		CImage *Tiles[64]; 		// Os Tiles
		SDL_Rect SR_Tile;	  	// As medidas do Tile
		int* ipTiles;			// Vetor de Tiles
		int iHSize,				// Tamanho total do mapa
			iWSize,				// informa��es do arquivo .map
			iWTiles,			// Numero de tiles na hor.
			iHTiles,			// Numero de tiles na vert.
			iControlTile;		// Contador de tiles carregados

	public:
        CMap();										// Construtor
		void Create_Map(const std::string& spFile);	// Gera um mapa apartir de um arquivo(vide "data/jungle.map")
        void SetCam(SDL_Rect SR_Dest);				// Posiciona a 'Camera'
		void Draw(SDL_Surface* SS_p_Dest);			// Desenha apenas a parte visivel do mapa
        ~CMap();									// Descontrutor

};

#endif // _CMap_h
