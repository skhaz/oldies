
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *       2006 - Projeto MDD - Mundo dos Dragões - Um MMORPG Open-Source        *
 *                                                       by <<Striker>>        *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Versão da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Versão deste documento: 0.09 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação das Funções Principais do Jogo (núcleo)            *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/CoreGame.h"



// Declarações das Classes
CScreen	*g_Screen = NULL;	// GLOBAL DE MODULO (Por Enquanto)

CPlayer	*g_Player  = NULL;	// Jogador Teste
CInput	*g_Input   = NULL;	// Input do Jogo
CFPS	*g_FPS	   = NULL;	// FPS do Jogo
CMap    *g_Map	   = NULL;	// Mapa do Jogo
CMouse	*g_Mouse   = NULL;	// O mouse
CMusic  *g_Music   = NULL;	// A musica do jogo
CImage	*g_MiniMap = NULL;	// A imagem usada no Minimapa
CImage  *g_Equippage = NULL; // Imagen do painel dos equipamentos

CLoadScreen* g_LoadScreen = NULL; // Tela de Loading

// Declarações das classes usadas pela GUI
// nota: Apenas temporario
gcn::SDLInput* g_gcnInput = NULL;
gcn::SDLGraphics* g_gcnGraphics = NULL;
gcn::SDLImageLoader* g_gcnImageLoader = NULL;
gcn::Gui* g_gcnGui = NULL;
gcn::Container* g_gcnTop = NULL;
gcn::Container* g_gcnWinTop = NULL;

gcn::ImageFont* g_gcnFont 		= NULL;
gcn::Window* g_gcnWindow 		= NULL;
gcn::Label* g_gcnLabelFPS		= NULL;
gcn::Image* g_gcnLifeBarImage	= NULL;
gcn::Image* g_gcnManaBarImage	= NULL;
gcn::Icon* g_gcnLifeBarIcon		= NULL;
gcn::Icon* g_gcnManaBarIcon		= NULL;

gcn::TextField* g_gcnConsoleField = NULL;
gcn::Window*  g_gcnConsoleWin = NULL;


void InitSDL(const char *title, const char* icon)    // Inicializa a Janela e Variáveis do SDL
{
	// Usado para centralizar a janela, quando não fullscreen
	if((g_uiFlags & SDL_FULLSCREEN) != SDL_FULLSCREEN)
		putenv("SDL_VIDEO_CENTERED=1");


    if(SDL_Init(SDL_INIT_VIDEO | (g_bHaveAudio ? SDL_INIT_AUDIO : 0)) < 0)
    {
        fprintf(stderr, "Erro ao inicializar a SDL: %s\n", SDL_GetError());
        return;
    } // Fim do if(SDL_Init(SDL_INIT_VIDEO | (g_bHaveAudio ? SDL_INIT_AUDIO : 0)) < 0)
    atexit(SDL_Quit);

    if(TTF_Init() < 0)
	{
		fprintf(stderr, "Erro ao inicializar o TTF: %s\n", SDL_GetError());
		return;
	} // Fim do if(TTF_Init())
	atexit(TTF_Quit);

	if(g_bHaveAudio)
	{
		if(Mix_OpenAudio(g_iMixerFrequency, AUDIO_S16, g_iMixerChannels, 4096) < 0)
		{
			fprintf(stderr, "Erro ao iniciar o Mixer: %s\n", SDL_GetError());
			g_bHaveAudio = false;

			SDL_QuitSubSystem(SDL_INIT_AUDIO);
		} // Fim do Mix_OpenAudio
		atexit(Mix_CloseAudio);
	} // Fim de if(bHaveAudio)

    g_Screen = new CScreen(g_uiWWindow, g_uiHWindow, g_uiBPPWindow, g_uiFlags, title, icon);
    if(g_Screen == NULL)
    {
		fprintf(stderr, "Erro ao inicializar o modo gráfico: %s\n", SDL_GetError());
        return;
    }   // Fim do if(screen == NULL)

	g_uiColorKey = SDL_MapRGB(g_Screen->GetScreen()->format, 0xff, 0x00, 0xff); // Rosa para o ColorKey


	#ifdef DEBUG
		g_Screen->Debug(); // Inicia o teste de Debug do video
	#endif
} // Fim do InitSDL(const char *title, const char* icon)


void InitGame()  // Inicaliza o Jogo
{
	g_LoadScreen = new CLoadScreen();
    CImage  *p_intro;	// Ponteiro da Image da Entrada
    p_intro  = new CImage("data/screens/intro.jpg", false);	//Cria o Objeto CImage
    p_intro->Draw(g_Screen->GetScreen());					// Desenha o Objeto Intro na Tela (g_Screen)
    g_Screen->Flip();	// Flipa a Screen

	fflush(stdin); // Esvazia o buffer do teclado
    bool bEnd = false;	// Bool de Saida (bEnd)
    SDL_Event SE_Event;
    while (!bEnd)
    {
        SDL_PollEvent(&SE_Event);
        if (SE_Event.type == SDL_KEYUP)
            bEnd = true;
    }

    delete(p_intro);	// Apaga Estaticamente o Objeto
    g_Screen->Clear();	// Limpa a Tela (g_Screen)
	ShowLoad();


	g_Map = new CMap();
    g_Map->Create_Map("data/maps/jungle.map"); // Gera o mapa apartir das informacoes de jungle.map
	ShowLoad();

    g_Player = new CPlayer("data/obj/char/aprendiz");
	ShowLoad();

	g_Mouse = new CMouse("data/mouse"); // Diretorio das imagens do cursor
	ShowLoad();

	g_Music = new CMusic("data/music/music_01.ogg");
	ShowLoad();

	g_FPS = new CFPS(FPS);
	ShowLoad();

} // Fim do InitGame()


void InitGui()
{
	g_gcnImageLoader = new gcn::SDLImageLoader(); // Inicia sistema de carregamentos de imagen
	gcn::Image::setImageLoader(g_gcnImageLoader);
	ShowLoad();

	g_gcnGraphics = new gcn::SDLGraphics(); // Inicia sistema grafico da Guichan
	g_gcnGraphics->setTarget(g_Screen->GetScreen()); // Aponta para o ponteiro da tela
	ShowLoad();

	g_gcnInput = new gcn::SDLInput();	// Inicia sistema de Input
	ShowLoad();

	g_gcnTop = new gcn::Container();
	g_gcnTop->setDimension(gcn::Rectangle(0, 0, g_uiWWindow, g_uiHWindow));
	ShowLoad();

	g_gcnGui = new gcn::Gui();
	g_gcnGui->setGraphics(g_gcnGraphics);
	g_gcnGui->setInput(g_gcnInput);
	g_gcnGui->setTop(g_gcnTop);
	ShowLoad();

	g_gcnWindow = new gcn::Window("Bem vindo ao MDD"); // Cria a janela, com titulo
	g_gcnWindow->setMovable(true); // Diz que é movivel :D
	g_gcnWindow->setBaseColor(gcn::Color(216, 208, 200)); // Especifica a cor da janela
	g_gcnWindow->setDimension(gcn::Rectangle(0, 0, 250, 100)); // Especifica o tamanho da janela
	ShowLoad();

	g_gcnWinTop = new gcn::Container();
	g_gcnWinTop->setDimension(gcn::Rectangle(0, 0, 300, 100));
	ShowLoad();

	g_gcnFont = new gcn::ImageFont("data/fonts/fixedfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`´*#=[]\"");
	gcn::Widget::setGlobalFont(g_gcnFont);
	ShowLoad();

	g_gcnLabelFPS = new gcn::Label("FPS: Initializing"); // Inicia o label com um texto inicial
	ShowLoad();

	g_MiniMap = new CImage("data/gui/MiniMap.png", 726, 526, true);
	ShowLoad();

	g_Equippage = new CImage("data/gui/Equippage.png", 480, 30, true);
	ShowLoad();

	g_gcnLifeBarImage = new gcn::Image("data/gui/LifeBar.png");
	g_gcnManaBarImage = new gcn::Image("data/gui/ManaBar.png");
	ShowLoad();

	g_gcnLifeBarIcon = new gcn::Icon(g_gcnLifeBarImage);
	g_gcnManaBarIcon = new gcn::Icon(g_gcnManaBarImage);
	ShowLoad();

	g_gcnConsoleField = new gcn::TextField("Caixa de texto do Console");
	g_gcnConsoleWin = new gcn::Window("Console");
	ShowLoad();

	g_gcnWinTop->add(g_gcnLifeBarIcon, 10, 10);
	g_gcnWinTop->add(g_gcnManaBarIcon, 10, 26);
	g_gcnWinTop->add(g_gcnLabelFPS, 10, 50);
	ShowLoad();

	g_gcnWinTop->setOpaque(false);
	g_gcnWindow->setContent(g_gcnWinTop);
	ShowLoad();

	g_gcnConsoleWin->setContent(g_gcnConsoleField);
	g_gcnConsoleWin->setMovable(true); // Diz que é movivel :D
	g_gcnConsoleWin->setBaseColor(gcn::Color(216, 208, 200)); // Especifica a cor da janela
	g_gcnConsoleWin->setDimension(gcn::Rectangle(0, 0, 250, 50)); // Especifica o tamanho da janela
	ShowLoad();

	g_gcnTop->add(g_gcnConsoleWin, 335, 550); // Adiciona o console
	g_gcnTop->add(g_gcnWindow, 20, 20); 	// Adiciona janela no Container
	g_gcnTop->setOpaque(false);				// Para que o container seja trasparente
	ShowLoad();
}

void ShowLoad()
{
	g_Screen->Clear();
	g_LoadScreen->Draw(g_Screen->GetScreen());
	g_Screen->Flip();
	SDL_Delay(50);
}

void MainLoop()	// Loop Principal do Jogo
{
	char sBuffer[SMALL_BUF];
	SDL_EnableUNICODE(1);
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    SDL_Event SE_Event;
    Uint8* p_ui8Tecla = NULL;
    bool bEnd = false,
		 bWeapowPainel = false;

	g_Music->Play();

	fflush(stdin); // Esvazia o buffer do teclado (paranoia?)
    while (!bEnd)
    {
        SDL_PollEvent(&SE_Event); // Pega o Evento
        p_ui8Tecla = SDL_GetKeyState(NULL);

        if (SE_Event.type == SDL_QUIT)
            bEnd = true;

        else
        {
            if (p_ui8Tecla[SDLK_LEFT]&&!p_ui8Tecla[SDLK_DOWN]&&!p_ui8Tecla[SDLK_UP]&&!p_ui8Tecla[SDLK_RIGHT])
                g_Player->Direction(LEFT);          // Apertado ESQUERDO
            else if (p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_UP]&&!p_ui8Tecla[SDLK_DOWN]&&!p_ui8Tecla[SDLK_LEFT])
                g_Player->Direction(RIGHT);         // Apertado DIREITA
            else if (p_ui8Tecla[SDLK_UP]&&!p_ui8Tecla[SDLK_LEFT]&&!p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_DOWN])
                g_Player->Direction(UP);            // Apertado CIMA
            else if (p_ui8Tecla[SDLK_DOWN]&&!p_ui8Tecla[SDLK_LEFT]&&!p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_UP])
                g_Player->Direction(DOWN);          // Apertado BAIXO
            else if (p_ui8Tecla[SDLK_DOWN]&&p_ui8Tecla[SDLK_LEFT]&&!p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_UP])
                g_Player->Direction(LEFTDOWN);      // Apertado BAIXO e ESQUERDA
            else if (p_ui8Tecla[SDLK_DOWN]&&!p_ui8Tecla[SDLK_LEFT]&&p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_UP])
                g_Player->Direction(RIGHTDOWN);     // Apertado BAIXO e DIREITA
            else if (p_ui8Tecla[SDLK_UP]&&p_ui8Tecla[SDLK_LEFT]&&!p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_DOWN])
                g_Player->Direction(LEFTUP);        // Apertado CIMA e ESQUERDA
            else if (p_ui8Tecla[SDLK_UP]&&!p_ui8Tecla[SDLK_LEFT]&&p_ui8Tecla[SDLK_RIGHT]&&!p_ui8Tecla[SDLK_DOWN])
                g_Player->Direction(RIGHTUP);       // Apertado CIMA e DIREITA
            else                                    // Nenhuma Seta Apertada
            {
                eSide eLado = g_Player->GetDirection();  // Qual Estado Parar ?
                if (eLado == LEFT)
                    g_Player->Direction(STOP_LEFT);      // Parar ESQUERDA
                else if (eLado == RIGHT)
                        g_Player->Direction(STOP_RIGHT); // Parar DIREITA
                else if (eLado == UP)
                        g_Player->Direction(STOP_UP);    // Parar CIMA
                else if (eLado == DOWN)
                        g_Player->Direction(STOP_DOWN);  // Parar BAIXO
                else if (eLado == LEFTDOWN)
                        g_Player->Direction(STOP_LEFTDOWN); // Para ESQUERDA BAIXO
                else if (eLado == LEFTUP)
                        g_Player->Direction(STOP_LEFTUP);   // Parar ESQUERDA ALTA
                else if (eLado == RIGHTDOWN)
                        g_Player->Direction(STOP_RIGHTDOWN);// Parar DIREITA BAIXO
                else if (eLado == RIGHTUP)
                        g_Player->Direction(STOP_RIGHTUP);  // Parar DIREITA ALTA
            } // Fim do else(Sem Teclas Pressionadas)

            if (p_ui8Tecla[KMOD_ALT] && p_ui8Tecla[SDLK_RETURN])
                g_Screen->ToggleFullScreen();	// Apertado ALT + ENTER -> Muda para fullscreen

			if (p_ui8Tecla[SDLK_F1])
				bWeapowPainel = !bWeapowPainel; // Apertado F1 -> Mostra o Painel de Armas

            if (p_ui8Tecla[SDLK_F2])
                g_Screen->Save();		// Apertado F2 -> Salva Tela

            if (p_ui8Tecla[SDLK_ESCAPE])
                bEnd = true;			// Apertado ESC -> Sai do Jogo

        } // Fim do else (Tipo de Entrada)
        g_Screen->Clear();					// Limpa a Tela (g_Screen)



		g_gcnInput->pushInput(SE_Event);	// Checa as entradas para a GUI
		g_gcnGui->logic();					// Processa toda a GUI

		g_Map->SetCam(g_Player->GetRect());	// Posiciona a 'Camera'
        DrawGame(g_Screen->GetScreen(), bWeapowPainel);	// Desenha a Tela


		g_gcnConsoleField->adjustSize(); // Ajusta a area de texto com o tamanho do texto
		snprintf(sBuffer, SMALL_BUF, "FPS: %2.2f", g_FPS->GetFPS());	// Formata string para ser apresentada
		g_gcnLabelFPS->setCaption(sBuffer);	// Atualiza texto do label
		g_gcnLabelFPS->adjustSize();		// Ajusta ao tamanho do texto



		g_Screen->Flip();	// Flipa a Tela (Copia o BackBuffer para o FrontBuffer)

		g_FPS->FPSProcess();   		// Atualiza o sistema de FPS
		SDL_Delay(g_FPS->Delay());	// Aguarda tempo nescessario para cumprir a  meta de FPS
    } // Fim do while(!bEnd)
} // Fim do MainLoop(void)


void DrawGame(SDL_Surface *SS_p_Dest, bool bShowWeapowPainel)
{
	g_Map->Draw(SS_p_Dest);	// Desenha o mapa
    g_Player->DrawPlayer(SS_p_Dest);	// Desenha o jogador
   	g_MiniMap->Draw(SS_p_Dest); // Desenha o minimapa

   	if(bShowWeapowPainel)
		g_Equippage->Draw(SS_p_Dest);

	g_gcnGui->draw();	// Desenha a GUI
	g_Mouse->Draw(SS_p_Dest);	// Desenha o Mouse
} // Fim do DrawGame()


void ShowCredits() // Mostra os Créditos
{
	CImage *p_Credit;
	p_Credit = new CImage("data/screens/credits.jpg", false);
	g_Screen->Clear();
	p_Credit->Draw(g_Screen->GetScreen());
	g_Screen->Flip();

	fflush(stdin);
    bool bEnd = false;
    SDL_Event SE_Event;
    while (!bEnd)
    {
        SDL_PollEvent(&SE_Event);
        if (SE_Event.type == SDL_KEYDOWN)
            bEnd = true;
    }

	delete(p_Credit);
} // Fim do ShowCredits()


void HaltGui()
{
	delete(g_gcnLabelFPS);		// Destruindo Texto
	delete(g_gcnFont);			// Destruindo Fonte
	delete(g_gcnTop);			// Destruindo Container
	delete(g_gcnGui);			// Destruindo Interface
	delete(g_gcnInput);			// Destruindo Entrada
	delete(g_gcnGraphics);		// Destruindo Graficos
	delete(g_gcnImageLoader);	// Destruindo Carregador de imagens
	delete(g_gcnLifeBarIcon);	// Destruindo o icone "Barra de Vida"
	delete(g_gcnManaBarIcon);	// Destruindo o icone "Barra de Magia"
	delete(g_gcnLifeBarImage);	// Destruindo o imagen "Barra de Vida"
	delete(g_gcnManaBarImage);	// Destruindo o imagen "Barra de Magia"
	delete(g_gcnConsoleField);	// Destruindo o console
	delete(g_gcnConsoleWin);	// Destruindo a janela do console
	delete(g_MiniMap);	  		// Destruindo o Minimapa
	delete(g_Equippage);  		// Destruindo o Painel
	delete(g_gcnWinTop);		// Destruindo Container da janela
	delete(g_gcnWindow);		// Destruindo Janela
} // Fim do HaltGui()


void ExitGame() // Saida do Jogo
{
	delete(g_FPS);        // Destruindo o FPS
	delete(g_Map);        // Destruindo o Mapa
	delete(g_Input);	  // Destruindo a Entrada
	delete(g_LoadScreen); // Destruindo a tela de loading
	delete(g_Mouse);	  // Destruindo o Mouse
	delete(g_Music);	  // Destruindo a Musica
	delete(g_Screen);     // Descarrega a Tela
} // Fim do ExitGame()
