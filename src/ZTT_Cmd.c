#include <stdio.h>
#include <pthread.h>

#include "ZTT_Cmd.h"
#include "ZTT_Comm.h"


#define ZTT_CMD_ARG_LEN (64)
#define ZTT_CMD_ARG_NUM (8)
#define ZTT_CMD_ARGS_LEN (1024)

extern ZTT_CMD_ST _ZTT_CMD_TABLE_START[];
extern ZTT_CMD_ST _ZTT_CMD_TABLE_END[];


void ZTT_CmdParse(char *cmdline,int len, int *argc, char *argv[ZTT_CMD_ARG_NUM])
{
	//printf("cmdline:%s\n",cmdline);
}

/*************************************************
Function     : ZTT_CmdHandle
Description  : 解析处理收入命令行
Input        : 
Output       : 
Return       :  ZTT_SUCCESS
*************************************************/
int ZTT_CmdHandle(void)
{
	ssize_t inputLen = 0;
	ssize_t line_len = ZTT_CMD_ARGS_LEN;
	char  *cmdBuff=NULL;
	const char *prompt = "ZTT>";
	int argc = 0;
	char *argv[ZTT_CMD_ARG_NUM] = {0};
	while(ZTT_TRUE)
	{
		printf("ZTT>");
		inputLen = getline(&cmdBuff,&line_len , stdin);
		if(1>=inputLen)
		{
			printf("\n");
			continue;
		}
		
		ZTT_CmdParse(cmdBuff,inputLen,&argc,argv);
		
		ZTT_CMD_ST *init_ptr = _ZTT_CMD_TABLE_START;
	    for (init_ptr=_ZTT_CMD_TABLE_START; init_ptr < _ZTT_CMD_TABLE_END; init_ptr++) 
		{
			if(0 == strncmp(cmdBuff,init_ptr->cmd_name,strlen(init_ptr->cmd_name)))
			{
				init_ptr->cmd_func(argc, argv);
				break;
			}
	        
	    }
		if(init_ptr == _ZTT_CMD_TABLE_END )
		{
			printf("Unknown ZZT cmd:\n");
			system(cmdBuff);
		}
		
		cmdBuff = NULL;
		
		usleep(1000);
		
	}
	return ZTT_SUCCESS;
}

/*************************************************
Function     :
Description  :
Input        :
Output       :
Return       : 
*************************************************/
int ZTT_CmdThreadRun()
{
	pthread_t currentp = 0;
	printf("create a cmdline \n");
	pthread_create(&currentp,NULL,ZTT_CmdHandle,NULL);
	return ZTT_SUCCESS;
}

/*************************************************
Function     :
Description  :
Input        :
Output       :
Return       : 
*************************************************/
int ZTT_CmdHelp(int argc, char *argv[])
{
	ZTT_CMD_ST *init_ptr = _ZTT_CMD_TABLE_START;
    for (init_ptr = _ZTT_CMD_TABLE_START; init_ptr < _ZTT_CMD_TABLE_END; init_ptr++) 
	{
        printf("%s\n", init_ptr->cmd_name);
    }
	return ZTT_SUCCESS;
}

ZTT_CMD_REG(help,ZTT_CmdHelp);

