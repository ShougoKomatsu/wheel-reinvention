#include "stdafx.h"
#include "Perser.h"

#define COMMAND_UNDEFINED (0)
#define COMMAND_COMMON (0)
#define COMMAND_MOUSE (1000)

#define COMMAND_DELAY (COMMAND_COMMON + 1)
#define COMMAND_BREAK (COMMAND_COMMON + 2)
#define COMMAND_KEY_DOWN_UP (COMMAND_COMMON +3)
#define COMMAND_KEY_DOWN (COMMAND_COMMON +4)
#define COMMAND_KEY_UP (COMMAND_COMMON +5)
#define COMMAND_REPEAT (COMMAND_COMMON +6)
#define COMMAND_REPEAT_END (COMMAND_COMMON +7)
#define COMMAND_NOTING (COMMAND_COMMON +8)
#define COMMAND_DECRARE (COMMAND_COMMON + 9)
int OperateCommand(int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine);
