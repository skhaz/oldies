
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Dragões - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * eMail: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Versão da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Versão deste documento: 0.05 (12/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CScreen (Tela do Jogo)                   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "lib/classes/CScreen.h"


CScreen::CScreen(Uint32 W, Uint32 H, Uint32 BPP, Uint32 Flags)
{
	uiWidth  = W;
	uiHeight = H;
	uiBPP 	 = BPP;
	uiFlags	 = Flags;

	GetFlags();
	SetVideoMode();
	Clear();
}

CScreen::CScreen(Uint32 W, Uint32 H, Uint32 BPP, Uint32 Flags, const char* CC_p_Title)
{
	uiWidth  = W;
	uiHeight = H;
	uiBPP 	 = BPP;
	uiFlags	 = Flags;

	SDL_WM_SetCaption(CC_p_Title, 0);

	GetFlags();
	SetVideoMode();
	Clear();
}

CScreen::CScreen(Uint32 W, Uint32 H, Uint32 BPP, Uint32 Flags, const char* CC_p_Title, const char* CC_p_Icon)
{
	uiWidth  = W;
	uiHeight = H;
	uiBPP 	 = BPP;
	uiFlags	 = Flags;

	SDL_WM_SetCaption(CC_p_Title, 0);
	SDL_WM_SetIcon(IMG_Load(CC_p_Icon), NULL);

	GetFlags();
	SetVideoMode();
	Clear();
}

void CScreen::SetVideoMode()
{
	SS_p_Screen = SDL_SetVideoMode(uiWidth, uiHeight, uiBPP, uiFlags);
}

SDL_Surface* CScreen::GetScreen()
{
	return SS_p_Screen;
}

void CScreen::Flip()
{
	SDL_Flip(SS_p_Screen);
}

void CScreen::Clear()
{
	SDL_FillRect(SS_p_Screen, NULL , 0);
}

void CScreen::ToggleFullScreen()
{
//	uiFlags ^= SDL_FULLSCREEN;
//	SetVideoMode();
}

Uint32 CScreen::GetFlags()
{
	const SDL_VideoInfo* SV_p_Info = SDL_GetVideoInfo();

	if (SV_p_Info->blit_hw_CC && SV_p_Info->blit_fill)
	uiFlags |= SDL_HWSURFACE;

	if ((uiFlags & SDL_HWSURFACE) == SDL_HWSURFACE)
	{
		if (SV_p_Info->video_mem*1024 > (uiWidth*uiHeight*uiBPP/8))
			uiFlags |= (SDL_DOUBLEBUF | SDL_HWACCEL);
		else
			uiFlags &= ~SDL_HWSURFACE;
	}

	return uiFlags;
}


int CScreen::GetWidth()
{
	return SS_p_Screen->w;
}

int CScreen::GetHeight()
{
	return SS_p_Screen->h;
}

int CScreen::GetDepth()
{
	return SS_p_Screen->format->BitsPerPixel;
}


void CScreen::Debug()
{
	char VideoDriverName[SMALL_BUF];
    const SDL_VideoInfo *SV_Info = SDL_GetVideoInfo();

	std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl
			  << "       MDD - Debug do Video       " << std::endl
			  << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl << std::endl;

	if (SDL_VideoDriverName(VideoDriverName, SMALL_BUF))
		std::cout << "Nome do driver de vídeo: " << VideoDriverName << std::endl;
	else
		std::cout << "Nome do driver de vídeo: desconhecido" << std::endl;

	std::cout << "Resolução atual: "
			  << uiWidth << "x" << uiHeight << "x" << uiBPP << std::endl << std::endl;

	std::cout << "Configuração Atual: " << std::endl << std::endl
			  << "Tela Cheia: " << (((SS_p_Screen->flags & SDL_FULLSCREEN) == SDL_FULLSCREEN) ? "sim" : "não") << std::endl
			  << "Buffer Duplo: " << (((SS_p_Screen->flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF) ? "sim" : "não") << std::endl
			  << "Surperfície no Hardware: " << (((SS_p_Screen->flags & SDL_HWSURFACE)== SDL_HWSURFACE) ? "sim" : "não") << std::endl
			  << "Aceleração por Hardware: " << (((SS_p_Screen->flags & SDL_HWACCEL)== SDL_HWACCEL) ? "sim" : "não") << std::endl << std::endl;

    std::cout << "\'Manipulador de Janelas\' presente: "
			  << ((SV_Info->wm_available) ? "sim" : "não") << std::endl;
    std::cout << "\'Hardware Surfaces\' Possíveis de criar: "
			  << ((SV_Info->hw_available) ? "sim" : "não") << std::endl;
    std::cout << "\'Blits\' Hardware para Hardware Acelerado: "
			  << ((SV_Info->blit_hw) ? "sim" : "não") << std::endl;
    std::cout << "\'ColorKey Blits\' Hardware para Hardware Acelerado: "
			  << ((SV_Info->blit_hw_CC) ? "sim" : "não") << std::endl;
    std::cout << "\'Alpha Blit\' Hardware para Hardware Acelerado: "
			  << ((SV_Info->blit_hw_A) ? "sim" : "não") << std::endl;
    std::cout << "\'Blits\' Software para Hardware Acelerado: "
			  << ((SV_Info->blit_sw) ? "sim" : "não") << std::endl;
    std::cout << "\'ColorKey Blits\' Software para Hardware Acelerado: "
			  << ((SV_Info->blit_sw_CC) ? "sim" : "não") << std::endl;
    std::cout << "\'Alpha Blits\' Software para Hardware Acelerado: "
			  << ((SV_Info->blit_sw_A) ? "sim" : "não") << std::endl;
    std::cout << "\'Color Fills\' Acelerado: "
			  << ((SV_Info->blit_fill) ? "sim" : "não") << std::endl;
    std::cout << std::endl << "Total de Memória de Vídeo livre presente: "
			  << SV_Info->video_mem << "KB" << std::endl << std::endl;


	std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl
			  << "       MDD - Fim do debug do Video       " << std::endl
			  << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
}



int CScreen::Save(void)
{
	static int iIndex = 0;
	char sFileName[STD_BUF];

	char *sFileExt =
	#ifdef HAVE_JPEG
		"jpg";
	#else
		"bmp";
	#endif

	do
	{
		iIndex++;
		snprintf(sFileName, STD_BUF, "screenshot/screenshot_%04d.%s", iIndex, sFileExt);
	} while(!access(sFileName, 0));


#ifdef HAVE_JPEG
	struct jpeg_compress_struct info;
	struct jpeg_error_mgr jerr;
	FILE* FP_ptr_OutFile;
	JSAMPROW iRow_ptr[1];
	int iRow_Stride;
	int iDeleteBuffer = 0;
	unsigned char* ucImageBuffer = NULL;
	SDL_Surface* SS_p_nSurface;

	info.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&info);

    if ((FP_ptr_OutFile = fopen(sFileName, "wb")) == NULL)
	{
		std::cout << "Impossível abrir o arquivo de destino: " << sFileName << std::endl;
		return -1;
    }

	jpeg_stdio_dest(&info, FP_ptr_OutFile);

	info.image_width = SS_p_Screen->w;
	info.image_height = SS_p_Screen->h;
	info.input_components = 3;
	info.in_color_space = JCS_RGB;


	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		SS_p_nSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, SS_p_Screen->w, SS_p_Screen->h,
											   24, 0xff000000, 0x00ff0000, 0x0000ff00, 0x00000000);
	#else
		SS_p_nSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, SS_p_Screen->w, SS_p_Screen->h,
											   24, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000);
	#endif

	if(SS_p_nSurface == NULL)
	{
		std::cout << "Erro ao alocar superfície para \'screenshot\'" << std::endl;
		return -1;
	}

	SDL_BlitSurface(SS_p_Screen, NULL, SS_p_nSurface, NULL);
	SS_p_Screen = SS_p_nSurface;
	iDeleteBuffer = 1;

	if(SDL_MUSTLOCK(SS_p_Screen))
	SDL_LockSurface(SS_p_Screen);

	ucImageBuffer = (unsigned char *)SS_p_Screen->pixels;

	jpeg_set_defaults(&info);

	jpeg_set_quality(&info, JPEG_QUALITY_DEFAULT, TRUE);
	jpeg_start_compress(&info, TRUE);

	iRow_Stride = SS_p_Screen->pitch;

	while (info.next_scanline < info.image_height)
	{
		iRow_ptr[0] = &ucImageBuffer[info.next_scanline * iRow_Stride];
		(void) jpeg_write_scanlines(&info, iRow_ptr, 1);
    }

	jpeg_finish_compress(&info);
	fclose(FP_ptr_OutFile);

	jpeg_destroy_compress(&info);

	if(SDL_MUSTLOCK(SS_p_Screen))
	SDL_UnlockSurface(SS_p_Screen);

	if(iDeleteBuffer)
	SDL_FreeSurface(SS_p_Screen);

	return 0;
#else // Caso contrario não tenha a bibliote JPEG no sistema salva como BMP

	SDL_SaveBMP(SS_p_Screen, sFileName);
	return 0;
#endif // Fim de HAVE_JPEG
}

CScreen::~CScreen()
{
	SDL_FreeSurface(SS_p_Screen);
}
