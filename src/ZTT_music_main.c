#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "ZTT_list.h"

static int gi_music_max_number = 1;
typedef struct ZTT_MUSIC_LIST_ST_
{
	char *music_name;
	int   music_id;
	struct ZTT_list_head node;
}ZTT_MUSIC_LIST_ST;

char * ZTT_MusicGetCWD(void)
{
	static char buf[80] = {0};   
    getcwd(buf,sizeof(buf));   
    printf("current working directory: %s\n", buf);  
    return buf;
}

void ZZT_MusicGetFiles(char *path, struct ZTT_list_head *head)
{
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	
	dir = opendir(path);
	while(NULL != (ptr = readdir(dir)))
	{
		printf("d_name:%s\n", ptr->d_name);
		int name_len = strlen(ptr->d_name);
		if( 0 == strncmp(ptr->d_name,"..",name_len ) || 0 == strncmp(ptr->d_name,".",name_len ) )
		{
			continue;
		}
		ZTT_MUSIC_LIST_ST *new_node = (ZTT_MUSIC_LIST_ST *)malloc(sizeof(ZTT_MUSIC_LIST_ST));
		new_node->music_name = (char *)malloc(name_len + 1);
		memcpy(new_node->music_name,ptr->d_name,name_len);
		new_node->music_name[name_len] = '\0';
		new_node->music_id = gi_music_max_number++;
		ZTT_LIST_HEAD_INIT(&(new_node->node));
		ZTT_list_add(&(new_node->node),head);
	}
	closedir(dir);
}


void ZZT_MusicFreeFiles(struct ZTT_list_head *head)
{
	ZTT_ListHead_ST *lst_tmp = NULL;
	ZTT_ListHead_ST *lst_node = NULL;
	ZTT_MUSIC_LIST_ST *music_node = NULL;
	
	ZTT_list_for_each_safe(lst_tmp,lst_node,head)
	{
		music_node = ZTT_list_entry(lst_tmp,ZTT_MUSIC_LIST_ST,node);
		if(NULL != music_node)
		{
			printf("free:%s\n",music_node->music_name);
			free(music_node->music_name);
			music_node->music_name = NULL;
			music_node->music_id = -1;
			ZTT_list_del(&music_node->node);
			free(music_node);
			music_node = NULL;
            gi_music_max_number--;
		}
	}
}
void ZZT_MusicDeleteOne(struct ZTT_list_head *head, int music_id)
{
	ZTT_ListHead_ST *lst_tmp = NULL;
	ZTT_ListHead_ST *lst_node = NULL;
	ZTT_MUSIC_LIST_ST *music_node = NULL;
	
	ZTT_list_for_each_safe(lst_tmp,lst_node,head)
	{
		music_node = ZTT_list_entry(lst_tmp,ZTT_MUSIC_LIST_ST,node);
		if(NULL != music_node)
		{
            if(music_id == music_node->music_id)
            {
                printf("free:%s\n",music_node->music_name);
                free(music_node->music_name);
                music_node->music_name = NULL;
                music_node->music_id = -1;
                ZTT_list_del(&music_node->node);
                free(music_node);
                music_node = NULL;
            }			
		}
	}
}


char songlist[50][50];
Mix_Music *music = NULL;
int gi_music_playing_id;
int quit;
int ZTT_MusicInit()
{
	if( SDL_Init(SDL_INIT_AUDIO)<0)
	{
		fprintf(stderr,"Couldn't Initialize SDL: %s\n",SDL_GetError());
			return 0;
	}
	
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
//	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;
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
void PlayMusic(int music_id, ZTT_ListHead_ST *head)
{
	if(music_id<0 || music_id >=gi_music_max_number )
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
    ZTT_ListHead_ST *lst_tmp = NULL;
	ZTT_ListHead_ST *lst_node = NULL;
	ZTT_MUSIC_LIST_ST *music_node = NULL;
	ZTT_list_for_each_safe(lst_tmp,lst_node,head)
    {
        music_node = ZTT_list_entry(lst_tmp,ZTT_MUSIC_LIST_ST,node);
        if(NULL != music_node )
        {
            if(music_id == music_node->music_id )
                break;
        }
    }
    if(NULL == music_node )
    {
        printf("music_node is null\n");
        return;
    }
    char music_name[80]={0};
    sprintf(music_name,"music/%s",music_node->music_name);
	music = Mix_LoadMUS(music_name);
	if(music == NULL)
	{
		fprintf(stderr,"Couldn't load %s: %s\n",music_node->music_name,SDL_GetError());
		return ;
	}
	if(Mix_FadeInMusic(music,-1,2000) == -1)
	{
		fprintf(stderr,"Couldn't Play %s: %s\n",music_node->music_name,SDL_GetError());
		return ;
	}
	fprintf(stdout,"Now Playing  %s\n",music_node->music_name);
	gi_music_playing_id = music_id;
}
void PlayNext(ZTT_ListHead_ST *head)
{
	gi_music_playing_id=(gi_music_playing_id+1)%gi_music_max_number;
	PlayMusic(gi_music_playing_id, head);
}
void PlayPrevious(ZTT_ListHead_ST *head)
{
	gi_music_playing_id=(gi_music_playing_id-1+gi_music_max_number)%gi_music_max_number;
	PlayMusic(gi_music_playing_id,head);
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
void Regi_music_max_numbereMusic(ZTT_ListHead_ST *head)
{
	if(Mix_PausedMusic())
	{
		//Mix_Regi_music_max_numbereMusic();
		printf("111111111");
	}
		
	else if(!Mix_PlayingMusic())
		PlayMusic(gi_music_playing_id, head);
}
void StopMusic()
{
	if(Mix_PlayingMusic())
		Mix_HaltMusic();
}
void ListMusic(ZTT_ListHead_ST *head)
{
	int i;
	fprintf(stdout,"***********SONGLIST*************\n");
    ZTT_ListHead_ST *lst_tmp = NULL;
	ZTT_ListHead_ST *lst_node = NULL;
	ZTT_MUSIC_LIST_ST *music_node = NULL;
	
	ZTT_list_for_each_safe(lst_tmp,lst_node,head)
    {
            music_node = ZTT_list_entry(lst_tmp,ZTT_MUSIC_LIST_ST, node);
            if(NULL != music_node)
            {
                    printf("%d: %s\n",music_node->music_id, music_node->music_name);
            }
    }
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
void PrintHelpInfo(char *args)
{
	fprintf(stdout,"用法：%s\n",args);
}
void Control(ZTT_ListHead_ST *head)
{
	PlayMusic(gi_music_playing_id,head);
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
				PlayNext(head);
				break;
			case 'p':
				PauseMusic();
				break;
			case 'c':
				Regi_music_max_numbereMusic(head);
				break;
			case 's':
				StopMusic();
				break;
			case 'f':
				PlayPrevious(head);
				break;
			case 'h':
				PrintCliInfo();
				break;
			case 'd':				
				break;
			case 't':
				PlayMusic(atoi(cmd+1)-1,head);
				break;
			case 'l':
				ListMusic(head);
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
    
    char filename[64]={0};
	ZTT_ListHead_ST stMusics;
	
	char *path = ZTT_MusicGetCWD();
	sprintf(filename,"%s/music",path);
	ZTT_LIST_HEAD_INIT(&stMusics);
	ZZT_MusicGetFiles(filename,&stMusics);
    
	if(!ZTT_MusicInit())
    {
		return 0;
	}
	gi_music_playing_id = 1;
	PrintCliInfo();
	Control(&stMusics);
	FreeSDL();
	return 0;
}
