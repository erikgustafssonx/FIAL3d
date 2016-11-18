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

#include "fial3d.h"

void gameinit()
{
	readplayernames();
	player[0].sign='X';
	player[1].sign='O';
	gamestate.winnerid=0;
	gamestate.gamewon=0;
	gamestate.gaveupwinning=0;
	gamestate.lastx=0;
	gamestate.lasty=0;
	gamestate.lastz=0;
	clearboard();
	atexit(winnermessage);
}

void gameloop()
{
	while(1)
	{
		for(gamestate.currentplayer=0;gamestate.currentplayer<=1;gamestate.currentplayer++)
		{
			retry:
			dooutput();
			if(gamestate.gamewon!=0)
			{
				return;
			}
			if(doinput() != 0) goto retry;
			winnertest();
		}
	}
}

int winnertest()
{
	if(testaroundpoint(gamestate.lastx-1,gamestate.lasty-1,gamestate.lastz-1))
	{
		gamestate.winnerid=gamestate.currentplayer;
		gamestate.gamewon=1;
		return(0);
	}
	return(-1);
}

int testaroundpoint(int sx, int sy, int sz)
{
	/*this function tests if there is 4 in a line around the point specified by sx,sy,sz.*/
	int dx;
	int dy;
	int dz;
	
	int tsx; /*temporary sx, sy, sz*/
	int tsy; 
	int tsz;
	
	for(dy=-1;dy<=1;dy++)
	{
		for(dx=-1;dx<=1;dx++)
		{
			for(dz=-1;dz<=1;dz++)
			{
				if(!(dx==0 && dy==0 && dz==0))
				{
					tsx=sx;
					tsy=sy;
					tsz=sz;
					while(board[tsx-dx][tsy-dy][tsz-dz]==player[gamestate.currentplayer].sign)
					{
						if(tsx-dx<0 || tsy-dy<0 || tsz-dz<0 || tsx-dx>board_w-1 || tsy-dy>board_h-1 || tsz-dz>board_d-1)
							break;
						tsx-=dx;
						tsy-=dy;
						tsz-=dz;

					}
					if(testline(tsx,tsy,tsz,dx,dy,dz,player[gamestate.currentplayer].sign)==0)
					{
						return(1);
					}
				}
			}
		}
	}
	return(0);
}

int testline(int startx,int starty,int startz,int dx,int dy,int dz,char sign)
{
	int x,y,z,i;	
	if(dx==0 && dy==0 && dz==0)
		return(-1);
	x=startx;
	y=starty;
	z=startz;
	for(i=0;i<=3;i++)
	{
		if(x<0 || x>board_w-1 || y<0 || y>board_h-1 || z<0 || z>board_d-1)
			return(-1);	
		if(board[x][y][z]!=sign)
			return(-1);
		x=x+dx;
		y=y+dy;
		z=z+dz;
	}	
	return(0);
}

void clearboard()
{
	int x;
	int y;
	int z;
	for(y=0;y<=board_h-1;y++)
	{
		for(x=0;x<=board_w-1;x++)
		{
			for(z=0;z<=board_d-1;z++)
			{
				board[x][y][z]='+';
			}
		}
	}
}


void playergivesup()
{
	gamestate.winnerid=!gamestate.currentplayer;
	gamestate.gaveupwinning=1;
	gamestate.gamewon=1;
	exit(0);
}
