/******************************
	ANSI colors foreground
******************************/
#define COLOR(x)	"\033[;" #x "m"
#define BLACK		COLOR(30)		// 黑
#define RED			COLOR(31)		// 红
#define GREEN		COLOR(32)		// 绿
#define YELLOW		COLOR(33)		// 黄
#define BLUE		COLOR(34)		// 蓝
#define MAGENTA		COLOR(35)		// 紫
#define CYAN		COLOR(36)		// 深绿
#define WHITE		COLOR(37)		// 白

/******************
	ANSI 控制码
******************/
#define GRAY		"\033[0m"		// 关闭所有属性
#define HILIGHT		"\033[1m"		// 设置高亮度
#define UNDERLINE	"\033[4m" 		// 下划线
#define BLINK		"\033[5m"		// 闪烁
#define SELECT		"\033[7m"		// 反显
#define DIS			"\033[8m"		// 消隐
#define UP(n)		"\033[nA"		// 光标上移n行
#define DOWN(n)		"\03[nB"		// 光标下移n行
#define RIGHT(n)	"\033[nC"		// 光标右移n行
#define LEFT(n)		"\033[nD"		// 光标左移n行
#define SETC		"\033[y;xH"		// 设置光标位置
#define CLEAR		"\033[2J"		// 清屏
#define KILL		"\033[K"		// 清除从光标到行尾的内容
#define SAVE		"\033[s"		// 保存光标位置
#define RESET		"\033[u"		// 恢复光标位置
#define CURSERNO	"\033[?25l"		// 隐藏光标
#define CURSERYES	"\33[?25h"		// 显示光标

/***************************
PS1='${debian_chroot:+($debian_chroot)}
\[\033[01;32m\]
\u@\h
\[\033[00m\]
:
\[\033[01;34m\]
\w
\[\033[00m\]
\$ '
***************************/
