
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *        2006 - Projeto MDD - Mundo dos Darg�es - Um MMORPG Open-Source       *
 *                                                        by <<Striker>>       *
 *                                                                             *
 * Site: www.pmdd.gnn.com.br                                                   *
 * Forum: forum.pmdd.gnn.com.br                                                *
 * Email: brunoloirao@gmail.com                                                *
 * IRC: Brasnet #MDD                                                           *
 * Vers�o da Engine: 0.0.2b                                                    *
 *                                                                             *
 * Vers�o deste documento: 0.02 (12/03/06)                                     *
 * Respons�vel da Vers�o: Equipe MDD                                           *
 * Descri��o: Acesso aos Cabe�alhos da biblioteca padr�o                       *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _Libraries_h
#define _Libraries_h



// Bibliotecas C++
#include <iostream>
#include <cstdlib>
#include <fstream>

// Bibliotecas C
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_JPEG
	#include <jpeglib.h>
#endif

#ifdef WIN32
	#include <io.h>
#endif
#ifdef LINUX
	#include <sys/io.h>
#endif

#include <getopt.h>



#ifdef __cplusplus
}	// extern "C"
#endif

#endif // _Libraries_h
