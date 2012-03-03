
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
 * Descrição: Implementação das funções da classe CMap                         *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/Cmap.h"



CMap::CMap(void)
{
	iControlTile = 0; // Zera o contador de tiles
}


void CMap::Create_Map(const std::string& spFile)
{
	SDL_Rect SR_Map;
	int l_iCount = 0;
	int l_iNum = 0;
	int iTotalTiles = 0;

	char *spBuf = NULL;
	char *spIndex = NULL;
	char *delims = "<=>\n"; // Esses serão os carecteres que serão iliminados
	char sBuffer[STD_BUF];
	char *spBuffer = new char[STD_BUF];
	char *spResult = new char[STD_BUF];

	FILE *FilePointer = NULL;
	if((FilePointer = fopen(spFile.c_str(), "r")) == NULL)
	{
		std::cerr << "Impossivel abrir arquivo: " << spFile << std::endl;
		exit(-1);
	}


	bzero((char *) sBuffer, STD_BUF);
	while((fgets(sBuffer, STD_BUF, FilePointer)) != NULL)
	{
		// spIndex vai apontar o endereço de sBuffer
		spIndex = sBuffer;

		// Evita espaços e tabs desnecessarios no inicio das linhas
		while(*spIndex == ' ' || *spIndex == '\t')
            spIndex++;

		// Se a linha não comecar com '#', 'nava-linha' ou não for nula, ela será processada
		if((*spIndex != '#') && (*spIndex != 0x0a) && (spIndex != NULL))
		{

			spBuf = strtok(spIndex, delims);

			while(spBuf != NULL)
			{

				if((strncmp(spBuf, WIDTH, WIDTH_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);
					iWSize = atoi(spResult);
				}

				else if((strncmp(spBuf, HEIGHT, HEIGHT_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);
					iHSize = atoi(spResult);
				}

				else if((strncmp(spBuf, WNTILES, WNTILES_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);
					iWTiles = atoi(spResult);
				}

				else if((strncmp(spBuf, HNTILES, HNTILES_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);
					iHTiles = atoi(spResult);
				}

				else if((strncmp(spBuf, WSTILE, WSTILE_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);
					SR_Tile.w = atoi(spResult);
				}

				else if((strncmp(spBuf, HSTILE, HSTILE_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);
					SR_Tile.h = atoi(spResult);
				}

				else if((strncmp(spBuf, TILE, TILE_LEN)) == 0)
				{
					spResult = strtok(NULL, delims);

					Tiles[iControlTile] = new CImage(spResult, true);
					iControlTile++;
				}

				if (*spBuf == '[')
				{

					if(ipTiles == NULL)
					{
						l_iCount = 0;
						iTotalTiles = iWTiles * iHTiles;
						ipTiles = new int[iTotalTiles];

						for(register int i = 0; i <= iTotalTiles; i++)
							*(ipTiles + i) = 0;
					}

					while (*spBuf)
					{
						while (*spBuf >= '0' && *spBuf <= '9')
						{

							l_iNum = (l_iNum * 10) + (*spBuf - '0');
							spBuf++;

							if (*spBuf == ' ' || *spBuf == '\t')
							{
								*(ipTiles + l_iCount) = l_iNum;
								l_iCount++;
								l_iNum = 0;

								break;
							}
						}

						spBuf++;

						while (*spBuf == ' ' || *spBuf == '\t')
							spBuf++;

						if (*spBuf == ']')
							break;
					}
				}


			spBuf = strtok(NULL, delims);
			} // Fim de while(spBuf != NULL)

		} // Fim de if((*spIndex != '#') && (*spIndex != 0x0a) && (spIndex != NULL))

	// Limpa o buffer (sBuffer)
	bzero((char *) sBuffer, STD_BUF);
	} // Fim de while((fgets(sBuffer, STD_BUF, FilePointer)) != NULL)
	fclose(FilePointer); // Fecha o arquivo
	delete(spBuffer);	 // Esvazia o buffer
	delete(spResult);	 // Esvazia o buffer


	/*
	 * Aloca superficie para o mapa
	 * atraves das informações retiradas
	 * do aequivo .map
	 */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		SS_p_Map = SDL_CreateRGBSurface((SDL_HWSURFACE | SDL_HWACCEL | SDL_RLEACCEL),
										iWSize, iHSize, g_uiBPPWindow, 0xff000000, 0x00ff0000, 0x0000ff00, 0x00000000);
	#else
		SS_p_Map = SDL_CreateRGBSurface((SDL_HWSURFACE | SDL_HWACCEL | SDL_RLEACCEL),
										iWSize, iHSize, g_uiBPPWindow, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000);
	#endif

	SDL_FillRect(SS_p_Map, NULL , 0); // Limpa superficie alocada

	SDL_Rect SR_Point;
	SDL_Rect SR_Start;

	SR_Start.x = (iHSize - SR_Tile.w)/2;
	SR_Start.y = 0;
	l_iCount = 0;

	for(int iZ = 1; iZ <= iHTiles; iZ++)
	{
		for(int iK = 1; iK <= iWTiles; iK++)
		{

			SR_Point.x = (iZ - iK) * (32)     + SR_Start.x;
			SR_Point.y = (iZ + iK) * (32 / 2) + SR_Start.y;

			Tiles[ipTiles[l_iCount]]->Draw(SS_p_Map, &SR_Point);
			l_iCount++;
		}
	}


} // Fim de Create_Map(const char* spFile)


void CMap::SetCam(SDL_Rect SR_Dest)
{
	SR_Cam = SR_Dest;
}


void CMap::Draw(SDL_Surface* SS_p_Dest)
{
	SDL_BlitSurface(SS_p_Map, NULL, SS_p_Dest, &SR_Cam);

	/**
	 * @todo Percorrer o sistema de tiles, e desenha somente as visiveis
	 */
}


CMap::~CMap()
{
	 // Desaloca matriz de tiles
	delete(ipTiles);

	// Desaloca todos os tiles
	for (int iCount = 0; iCount <= MAX_TILES; iCount++)
		delete(Tiles[iCount]);

	// Desaloca superficie do mapa
	if(SS_p_Map)
        SDL_FreeSurface(SS_p_Map);
}
