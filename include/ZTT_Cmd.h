#ifndef __ZTT_CMD_H__
#define __ZTT_CMD_H__
typedef int (*CMD_FUNC)(int argc, char *argv[]);
typedef struct ZTT_CMD_ST_
{
	char *cmd_name;
	CMD_FUNC cmd_func; 
}ZTT_CMD_ST;

#define ZTT_CMD_REG(cmd,func)\
	ZTT_CMD_ST ztt_cmd_##cmd __attribute__((__section__(".ZTT_CMD_TABLE"))) ={#cmd,func} 


int ZTT_CmdThreadRun(void);

#endif

