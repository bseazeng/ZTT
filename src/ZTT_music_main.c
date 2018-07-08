#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <SDL.h>
#include <SDL_mixer.h>


char songlist[50][50];
Mix_Music *music = NULL;
int sum ,playing;
int quit;
int Sdl_init()
{
	if( SDL_Init(SDL_INIT_AUDIO)<0)
	{
		fprintf(stderr,"Couldn't Initialize SDL: %s\n",SDL_GetError());
			return 0;
	}
	
//	int audio_rate = 22050;
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
//	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;
//	int audio_buffers = 1024;
	int audio_volume = MIX_MAX_VOLUME;
	char channeltype[][10] = {"","mono","stereo","surround"};
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels,audio_buffers)<0){
		fprintf(stderr,"Couldn't Open Audio: %s/n",SDL_GetError());
		return 0;
	}
	Mix_QuerySpec(&audio_rate,&audio_format,&audio_channels);
	Mix_VolumeMusic(audio_volume);
	Mix_SetMusicCMD(getenv("MUSIC_CMD"));
	fprintf(stdout,"Open Audio at %d Hz,%d bit,%s (%s),%d bytes buffer\n",audio_rate,audio_format& 0xFF ,channeltype[audio_channels],(audio_format&0x1000)?"BE":"LE",audio_buffers);	
	return 1;
}
void PlayMusic(int track)
{
	if(track<0 || track >=sum)
	{
		fprintf(stderr,"Input Error\n");
		return ;
	}
	if(Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(1000);
		SDL_Delay(1000);
	}
	if(music != NULL)
		Mix_FreeMusic(music);
	
	music = NULL;
	music = Mix_LoadMUS(songlist[track]);
	if(music == NULL)
	{
		fprintf(stderr,"Couldn't load %s: %s\n",songlist[track],SDL_GetError());
		return ;
	}
	if(Mix_FadeInMusic(music,-1,2000) == -1)
	{
		fprintf(stderr,"Couldn't Play %s: %s\n",songlist[track],SDL_GetError());
		return ;
	}
	fprintf(stdout,"Now Playing  %s\n",songlist[track]);
	playing = track;
}
void PlayNext()
{
	PlayMusic((playing+1)%sum);
}
void PlayPrevious()
{
	PlayMusic((playing-1+sum)%sum);
}
void SetVolume(int vol)
{	
	if(vol < 0 || vol > MIX_MAX_VOLUME)
	{
		fprintf(stderr,"Volume Value Error.(0 - %d)\n", MIX_MAX_VOLUME); 
		return ;
	}
	Mix_VolumeMusic(vol);
}
void PauseMusic()
{
	if(Mix_PlayingMusic())
		Mix_PauseMusic();
}
void ResumeMusic()
{
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else if(!Mix_PlayingMusic())
		PlayMusic(playing);
}
void StopMusic()
{
	if(Mix_PlayingMusic())
		Mix_HaltMusic();
}
void ListMusic()
{
	int i;
	fprintf(stdout,"***********SONGLIST*************\n");
	for(i=0;i<sum;i++)
		fprintf(stdout,"%d: %s/n",i+1,songlist[i]);
	fprintf(stdout,"********************************\n");
}
void PrintCliInfo()
{
	fprintf(stdout,"*************HELP***************\n");
	fprintf(stdout,"      p(暂停)    c(继续)\n");
	fprintf(stdout,"      f(上一首)  n(下一首)\n");
	fprintf(stdout,"      l(列表）   t#(播放某首)\n");
	fprintf(stdout,"      s(停止)    v#(音量0~%d)\n",MIX_MAX_VOLUME);
	fprintf(stdout,"      h(帮助)    d#(删除某首))\n");
	fprintf(stdout,"      q(退出)\n");
	fprintf(stdout,"********************************\n");
}
void PrintHelpInfo()
{
	fprintf(stdout,"用法：easymp3 [选项]... [文件]...\n");
	fprintf(stdout,"[选项]\n");
	fprintf(stdout,"--help/t打印帮助信息并退出\n");
}
void Control()
{
	PlayMusic(playing);
	char cmd[20];
	int i;
	while(!quit)
	{
		fprintf(stdout,"Enter :");
		fscanf(stdin,"%s",cmd);
		switch(*cmd){
			case 'q':
				Mix_HaltMusic();
				quit = 1;
				break;
			case 'n':
				PlayNext();
				break;
			case 'p':
				PauseMusic();
				break;
			case 'c':
				ResumeMusic();
				break;
			case 's':
				StopMusic();
				break;
			case 'f':
				PlayPrevious();
				break;
			case 'h':
				PrintCliInfo();
				break;
			case 'd':
				for(i=atoi(cmd+1);i<sum;i++)
					strcpy(songlist[i-1],songlist[i]);
				sum--;
				break;
			case 't':
				PlayMusic(atoi(cmd+1)-1);
				break;
			case 'l':
				ListMusic();
				break;
			case 'v':
				Mix_VolumeMusic(atoi(cmd+1));
				break;	
			default:
				break;
		}
	}
}
void FreeSDL()
{
	if(Mix_PlayingMusic())
		Mix_HaltMusic();	
	if( music != NULL)
	{
		Mix_FreeMusic(music);
		music = NULL;
	}
	Mix_CloseAudio();
	SDL_Quit();
}
int main(int argc, char *argv[])
{
	quit = 0;
	int i;
	for(i=1; i<argc &&  *argv[i] == '-'; i++ )
	{
		if(!strcmp(argv[i],"--help"))
		{
			PrintHelpInfo();	
			return 0;
		}
	}
	if(i>=argc)
	{
		PrintHelpInfo();
		return 0;
	}
	if(!Sdl_init()){
		return 0;
	}
	for(sum=0;i<argc;i++,sum++)
		strcpy(songlist[sum],argv[i]);
	playing = 0;
	PrintCliInfo();
	Control();
	FreeSDL();
	return 0;
}
