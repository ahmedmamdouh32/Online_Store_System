#include"Console_color.h"
#include<iostream>

using namespace std;

void consoleColor(int foreGroundColor,int backGroundColor)
{
    int color = foreGroundColor+ 16*backGroundColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
