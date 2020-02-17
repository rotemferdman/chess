#include "music.h"
#include <fstream>
#include <Windows.h>
#include "MMSystem.h"
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

/*
music_threding:
the function playing a music within the chess game
no input, no output
*/
void music_thread()
{
		char audiofile_char[50] = "music.wav"; //adding the name of the file
		std::fstream fp;
		fp.open(audiofile_char, std::ios::in);
		std::string audiofile_str = audiofile_char;
		while (true) //while the game is playing the music continiueing
		{
			PlaySound(audiofile_str.c_str(), NULL, SND_SYNC);
		}

}
