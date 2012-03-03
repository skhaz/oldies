
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
 * Vers�o deste documento: 0.01 (21/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Declara��o da Classe CMusic                                      *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../Globals.h"

#ifndef _CMusic_h
#define _CMusic_h




class CMusic {

	private:
		Mix_Music* MM_p_Music;

	public:
		CMusic();
		CMusic(const char* MusicFile);
		CMusic(Mix_Music* music);

		void Play();
		void Pause();
		void Stop();
		void Rewind();
		void Volume(int iVol);

		void FadeIn(int iDelay);
		void FadeOut(int iDelay);

		~CMusic();
};

#endif // _CMusic_h
