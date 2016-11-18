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

#include <stdio.h>

#define display_w 79
#define display_h 10

char display[display_w][display_h];

void waitkey()
{
	puts("Press enter to continue.");
	while(getchar()!='\n');
	{
	}
	while(getchar()!='\n');
	{
	}
}

void clearscreen()
{
#ifdef WIN32
	system("cls");
#else	
	system("clear");
#endif
}

int readint()
{
	/*
	 * this input must be done this way by securety reasons;
	 * so noone crashes the program by entering non numerical characters.
	 */
	char buffer[81];
	scanf("%80s",buffer);
	if(strcmp(buffer,"quit")==0)
	{
		playergivesup();
	}
	return atoi(buffer);
}

void draw_display()
{
	int x,y;
	clearscreen();
	for(y=0;y<=display_h-1;y++)
	{
		for(x=0;x<=display_w-1;x++)
		{
			putchar(display[x][y]);
		}
		printf("\n");
	}
}

void clear_display(char value)
{
	int x;
	int y;
	for(y=0;y<=display_h-1;y++)
	{
		for(x=0;x<=display_w-1;x++)
		{
			display[x][y]=value;
		}
	}
}

void showboard(int draw_x, int draw_y, int layer_z)
{
	int x;
	int y;
	for(y=0;y<=board_h-1;y++)
		for(x=0;x<=board_w-1;x++)
			display[draw_x+x][draw_y+y]=board[x][y][layer_z];
	for(x=0;x<=board_w-1;x++)
		display[draw_x+x][draw_y-1]='0'+x+1;
	for(y=0;y<=board_h-1;y++)
		display[draw_x-1][draw_y+y]='0'+y+1;

	display[draw_x+1][draw_y+board_h+1]='z';
	display[draw_x+2][draw_y+board_h+1]='=';
	display[draw_x+3][draw_y+board_h+1]='0'+layer_z+1;

	display[draw_x+board_w][draw_y-1]='x';
	display[draw_x-1][draw_y+board_h]='y';
}

void dooutput()
{
	clear_display(' ');
	showboard(5,3,0);
	showboard(25,3,1);
	showboard(45,3,2);
	showboard(65,3,3);
	draw_display();
	printf("\n\n%s plays as %c. %s plays as %c.\n",player[0].name, player[0].sign, player[1].name, player[1].sign);
	if(gamestate.lastx+gamestate.lasty+gamestate.lastz!=0) /*checks that its not the first turn*/
		printf("Last turn was played on [%d,%d,%d] by %s.",gamestate.lastx,gamestate.lasty,gamestate.lastz,player[!gamestate.currentplayer].name);
	printf("\n\n");
	if(gamestate.gamewon!=0)
		return; /*dont print the gamestate.last part if the game is already won*/	
	if(player[gamestate.currentplayer].name[strlen(player[gamestate.currentplayer].name)-1]!='s')
		printf("It is %ss turn:\n",player[gamestate.currentplayer].name);
	else
		printf("It is %s turn:\n",player[gamestate.currentplayer].name);
}

int doinput()
{
	int x, y, z;
	printf("x:");
	x=readint();
	if((x<1) || (x>board_w))
	{
		printf("x cordinate out of range, try again.\n");
		waitkey();
		return(-1);
	}
	printf("y:");
	y=readint();
	if((y<1) || (y>board_h))
	{
		printf("y cordinate out of range, try again.\n");
		waitkey();
		return(-1);
	}
	printf("z:");
	z=readint();
	if((z<1) || (z>board_d))
	{
		printf("z cordinate out of range, try again.\n");
		waitkey();
		return(-1);
	}
	if(board[x-1][y-1][z-1]!=player[!gamestate.currentplayer].sign && board[x-1][y-1][z-1]!=player[gamestate.currentplayer].sign)
	{
		board[x-1][y-1][z-1]=player[gamestate.currentplayer].sign;
		gamestate.lastx=x;
		gamestate.lasty=y;
		gamestate.lastz=z;
		return(0);
	}
	else
	{
		printf("location %d,%d,%d already in use, try again.\n",x,y,z);
		waitkey();
		return(-1);
	}
}

void readline(char buffer[], int maxlen)
{
int i;
i=0;
	while(i<maxlen)	
	{
		buffer[i]=getchar();
		if(buffer[i]=='\n')
			goto done;
		i++;
	}
done:
	buffer[i]=0;
}

void readplayernames()
{
	int i;
	clearscreen();
	puts("                      Welcome to fial3d 0.01, a game coded by eXXin.");
	printf("================================================================================");
	printf("Copyright (C) 2004 by Erik Gustafsson\nThis program is free software; you can redistribute it and/or\nmodify it under the terms of the GNU General Public License\nas published by the Free Software Foundation; either version\nof the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program; if not, write to the Free Software\nFoundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\n"); 
	printf("================================================================================");
	puts("Homepage: http://fial3d.sf.net");
	printf("================================================================================");
	puts("Contact info:");
	puts("Mail: exxin@linuxmail.org    Jabber: exxin@rootshell.tty0.org    ICQ: 115801971");
	puts("================================================================================");
	puts("Press enter to contiune.");
	while(getchar()!='\n');
		;
	showtux();
	for(i=0;i<=1;i++)
	{
		printf("Enter the name of player %d:",i+1);
		readline(player[i].name,player_maxname);
	}
}

void winnermessage()
{
	if(gamestate.gaveupwinning)
		printf("%s gave up.\n",player[!gamestate.winnerid].name);
	printf("%s has won the game!\n",player[gamestate.winnerid].name);
	waitkey();
}

void showtux()
{
puts("                 .88888888:.\n                88888888888888.\n               8888888888888888\n              88'  `88'   `88888\n              88 XX 88 XX  88888\n              88_XX_::_XX_:88888\n              88:::,::,:::::8888\n              88`:::::::::'`8888      FIAL3D is best runned on GNU/Linux\n             .88  `::::'    8:88.\n            8888            `8:888. \n          .8888'             `888888.\n         .8888:..  .::.  ...:'8888888:.\n        .8888.'     :'     `'::`88:88888   \n      .88:88        .:           888:8888:\n     888888.       ::           88:888888\n    `.::.888.      ::          .88888888\n   .::::::.888.    ::         :::`8888'.:.\n  ::::::::::.888   '         .::::::::::::\n  ::::::::::::.8    '      .:8::::::::::::.\n :::::::::::::::88:.__..:88888:::::::::::'\n  `'.:::::::::::88888888888.88:::::::::'\n        `':::_:' -- '' -'-' `':_::::'`\n");
}
