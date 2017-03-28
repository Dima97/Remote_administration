#include "Header.h"
void RebootPC()
{
	WinExec("shutdown -r -t 0", SW_HIDE);
	exit(0);
}
void ShutDownPC()
{
	WinExec("shutdown -s -t 0", SW_HIDE);
	exit(0);
}
void ExitSystemePC()
{
	WinExec("shutdown -l ", SW_HIDE);
	exit(0);
}
void OpenCD_ROM()
{
	mciSendString(_T("Set cdaudio door open wait"), NULL, 0, NULL);
}
void ExitFunction()
{
	exit(0);
}
//void ExecuteFile()
//{
//}