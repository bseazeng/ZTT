#include <stdio.h>
#include <stdlib.h>

#include "ZTT_Cmd.h"

int main(int argc, char *argv[])
{
	ZTT_CmdThreadRun();
	while(1)
	{
		sleep(1);
	}
}
