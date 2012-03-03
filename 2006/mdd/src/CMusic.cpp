
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
 * Versão deste documento: 0.01 (21/03/06)                                     *
 * Responsável da Versão: Equipe MDD                                           *
 * Descrição: Implementação da Classe CMusic                                   *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lib/classes/CMusic.h"

CMusic::CMusic()
{	;	}

CMusic::CMusic(const char* spFile)
{
	MM_p_Music = Mix_LoadMUS(spFile);
}

CMusic::CMusic(Mix_Music* music)
{
	MM_p_Music = music;
}

void CMusic::Play()
{
	Mix_PlayMusic(MM_p_Music, 0);
}

void CMusic::Pause()
{
	Mix_PauseMusic();
}

void CMusic::Stop()
{
	if(Mix_PausedMusic())
	Mix_ResumeMusic();
}

void CMusic::Rewind()
{
	Mix_RewindMusic();
}

void CMusic::Volume(int iVol)
{
	Mix_VolumeMusic(iVol);
}

void CMusic::FadeIn(int iDelay)
{
	Mix_FadeInMusic(MM_p_Music, 0, iDelay);
}

void CMusic::FadeOut(int iDelay)
{
	Mix_FadeOutMusic(iDelay);
}

CMusic::~CMusic()
{
	Mix_FreeMusic(MM_p_Music);
}
