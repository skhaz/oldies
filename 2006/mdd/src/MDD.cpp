
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
 * Versão deste documento: 0.08 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Modulo Principal do MDD                                          *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/Globals.h"	// Cabeçalhos do SDL, SDL_Imagem, SDL_TTF
#include "lib/CoreGame.h"	// Cabeçalho das Funções Principais do Jogo


unsigned int g_uiWWindow 	= 800, 				// Largura da Janela
			 g_uiHWindow 	= 600, 				// Altura da Janela
			 g_uiBPPWindow 	= 16,				// Profundida de cores
			 g_uiFlags 		= SDL_FULLSCREEN,	// Flags usadas para iniciar a SDL
			 g_uiColorKey;						// A cor que será usada para trasparencia

bool g_bHaveAudio 	   =  true;	// Booleano para o audio
int  g_iMixerFrequency = 44100,	// Frequencia do audio
	 g_iMixerChannels  =     2;	// Numero de canais



int main(int argc, char *argv[])
{
	int iResult;
	const char *OptString = "frx:y:d:q:n:ucvh";
	const struct option Option[] =	{
			{ "fullscreen", no_argument,       0, 'f' },
			{ "noframe",    no_argument,       0, 'r' },
			{ "width",      required_argument, 0, 'x' },
			{ "height",     required_argument, 0, 'y' },
			{ "depht",      required_argument, 0, 'd' },
			{ "frequency",  required_argument, 0, 'q' },
			{ "channels",   required_argument, 0, 'n' },
			{ "noaudio",    no_argument,       0, 'u' },
			{ "credits",	no_argument,	   0, 'c' },
			{ "version",	no_argument,	   0, 'v' },
			{ "help",       no_argument,       0, 'h' }
	};

	while (optind < argc)
	{
		if((iResult = getopt_long(argc, argv, OptString, Option, NULL)) == -1)
			break;

		switch (iResult)
		{
			case 'f':
				g_uiFlags ^= SDL_FULLSCREEN;
				break;
			case 'r':
				g_uiFlags ^= SDL_NOFRAME;
				break;
			case 'x':
				g_uiWWindow = atoi(optarg);
				break;
			case 'y':
				g_uiHWindow = atoi(optarg);
				break;
			case 'd':
				g_uiBPPWindow = atoi(optarg);
				break;
			case 'q':
				g_iMixerFrequency = atoi(optarg);
				break;
			case 'n':
				g_iMixerChannels = atoi(optarg);
				break;
			case 'u':
				g_bHaveAudio = false;
				break;
			case 'c':
				std::cout << "2006 - Projeto Mundo dos Dragões - <<Striker>>" << std::endl;
				break;
			case 'v':
				std::cout << "MDD Versão Atual: " << g_spAPPVersion << std::endl;
				break;
			case 'h':
			default:
				std::cout << "Ajuda ainda não implementada" << std::endl;
				break;
		}
	}


	try
	{
		InitSDL(g_spAPPName, g_spAPPIcon); // Inicia a biblioteca SDL
		InitGame();		// Inicia o jogo
		InitGui(); 		// Inicia a interface grafica a biblioteca GuiChan

		MainLoop();		// Laço principal do jogo

		ShowCredits();	// Mostra tela de creditos
		HaltGui();		// Finaliza e deleta a interface grafica
		ExitGame();		// Finaliza o jogo
	}

	catch (gcn::Exception err) // Tratamento de 'eception' da guichan
	{
		std::cerr << err.getMessage() << std::endl;
	}

	catch (std::exception err) // tratamento de 'exception' da biblioteca padrão
	{
		std::cerr << err.what() << std::endl;
	}

	catch (...) // Talvez o problema seja com a SDL :)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	return 0;
} // Fim de int main(int argc, char *argv[])




/*
 * Que venham os Dragões!
 *               by SKHAZ
 */
