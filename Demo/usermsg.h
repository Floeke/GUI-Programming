#pragma once


#ifndef USERMSG_H
#define USERMSG_H
#include <WinUser.h>

#define UPDATE_NAME WM_USER
#define UPDATE_REIHE (WM_USER+1)
#define UPDATE_WERT (WM_USER+2)
#define UPDATE_ALL (WM_USER+3)
#define CLOSE_ALL (WM_USER+4)



#endif // !USERMSG_H

#define FLAG_NAME 0x01
#define FLAG_FARBE 0x02
#define FLAG_WERT 0x04

extern void update_name();
extern void update_reihe(int zeile, int name, int farbe);
extern void update_wert(int zeile, int spalte);
extern void update_all(int name, int farbe, int wert);
extern void close_all();


