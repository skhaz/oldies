
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Dragões - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * IRC: Brasnet #MDD                                                           *
 * Email: brunoloirao@gmail.com                                                *
 * Versão da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Versão deste documento: 0.05 (12/03/06)                                     *
 * Respónsavel da Versão: Equipe MDD                                           *
 * Descrição: Repositório das Definições do Jogo                               *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _Definitions_h
#define _Definitions_h



// Tamanho padrão dos buffers
#define SMALL_BUF	  64
#define STD_BUF		 256
#define BIG_BUF		1024
#define HUGE_BUF	4096

// Macro de uso geral
#ifndef bzero
	#define bzero(p, s)	memset(p, 0, s)
#endif

#define MAX_BARS 16 // Numero maximo de barras usadas nas telas de loading

// Usado em CScreen, Algumas propriedades da libjpeg à serem ajustadas
#ifdef HAVE_JPEG
	#define RGB_PIXELSIZE 4

	#define JPEG_QUALITY_MIN	  0
	#define JPEG_QUALITY_MAX	100
	#define JPEG_QUALITY_DEFAULT 70
#endif


// Usados em CFPS
#define FPS		30	// Valor inicial/ideal (mais do que isso = badflicker)
#define FPS_MAX 60  // Valor maximo, acima disso aumenta o tempo de cada loop
#define FPS_MIN 10  // Valor minimo, menos que isso emite um aviso no log

// Usados em CMouse
#define MAX_MPOINTS		30

#define MOUSE_NORMAL	0x001 // Cursor normal
#define MOUSE_WAIT		0x002 // Ampulheta
#define MOSUE_CLICKED	0x004 // Clickado

// Use '#undef DEBUG' para desativar o debug
#define DEBUG

// Usados em CMap
#define WIDTH "WIDTH"
#define WIDTH_LEN strlen(WIDTH)

#define HEIGHT "HEIGHT"
#define HEIGHT_LEN strlen(HEIGHT)

#define WNTILES "WNTILES"
#define WNTILES_LEN strlen(WNTILES)

#define HNTILES "HNTILES"
#define HNTILES_LEN strlen(HNTILES)

#define WSTILE "WSTILE"
#define WSTILE_LEN strlen(WSTILE)

#define HSTILE "HSTILE"
#define HSTILE_LEN strlen(HSTILE)

#define TILE "TILE"
#define TILE_LEN strlen(TILE)


#endif // _Definitions_h
