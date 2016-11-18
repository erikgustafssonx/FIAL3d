/*
*This file is part of fial3d.
*Copyright (C) 2004  Erik Gustafsson
*
*This program is free software; you can redistribute it and/or
*modify it under the terms of the GNU General Public License
*as published by the Free Software Foundation; either version 2
*of the License, or (at your option) any later version.
*
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with this program; if not, write to the Free Software
*Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef _FIAL3D_H_
#define _FIAL3D_H_

/* determine plattform */
#ifndef WIN32
#define UNIX
#endif

#include <stdlib.h>
#include <string.h>

#define board_w 4
#define board_h 4
#define board_d 4

#define player_maxname 40

char board[board_w][board_h][board_d];

struct player_struct player[2];


struct player_struct
{
        char name[player_maxname+1]; /* +1 is for the ending zero*/
        char sign;
};

struct gamestate_struct
{
	int gamewon; /*stores information needed when someone wins the game*/	
	int winnerid; 
	int gaveupwinning;
	
	int currentplayer; /*stores the id number of the current player*/

	int lastx; /*stores information about the last turn made*/
	int lasty;
	int lastz;	
};

struct gamestate_struct gamestate;

/* functions */
void gameloop();
void gameinit();
void showboard(int,int,int); /* x , y, z */
int testline(int,int,int,int,int,int,char); /* x , y , z , dx ,dy, dz, sign */
void clearboard();
int winnertest();
int doinput();
void dooutput();
void draw_display();
void clear_display(char); /* value*/ 
void waitkey();
void clearscreen();
int readint();
void readline(char[],int); /* buffer[] , maxlen */
void readplayernames();
void showtux();
void winnermessage();
int testaroundpoint(int, int, int); /* sx , sy , sz */
void playergivesup();


#endif /* _FIAL3D_H_ */
