#include <bits/stdc++.h>
#include <windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)

void ShowCursor(bool visible) {
  CONSOLE_CURSOR_INFO cursor_info = {20, visible};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void SetConsoleWindowSize(SHORT width, SHORT height) {
  HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SMALL_RECT wrt = {0, 0, width - 1, height - 1};
  SetConsoleWindowInfo(hStdOutput, TRUE, &wrt);
  COORD coord = {width, height};
  SetConsoleScreenBufferSize(hStdOutput, coord);
}

HWND h;
DWORD WINAPI CLOSE2(LPVOID lpParamter)
{
	while(1)
	{
		if(KEY_DOWN(VK_MENU))ShowWindow(h,0);
		else ShowWindow(h,1);
	}
}

int main() {
  Sleep(10);
  h=GetForegroundWindow();
  HANDLE h3=CreateThread(0,0,CLOSE2,0,0,0);
  SetWindowPos(h,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
  system("color 97");
  ShowCursor(false);
  SetConsoleWindowSize(27, 6);
  SetConsoleTitle("Countdown");
  while (true) {
    time_t res = 1700267400 - time(0);
    puts("©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´");
    puts("©¦Time before NOIP 2023 ©¦");
    puts("©À©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©È");
    printf("©¦ %3d day(s) %2d:%2d:%2d  ©¦\n", res / 86400, res % 86400 / 3600, res % 3600 / 60, res % 60);
    puts("©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼");
    Sleep(996); system("cls");
  }
  return 0;
}

