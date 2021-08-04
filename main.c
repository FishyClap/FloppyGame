#include<stdio.h>
#include<conio.h>
#include<windows.h>
// Define global variables
int high,width; // The border
int bird_x,bird_y; // The bird coordinates
int bar_y; // Baffle coordinates
int bar_xTop,bar_xDown; // Upper and lower coordinates of the baffle opening
int score; // score

void HideCursor() // Hide the cursor
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y) // Move the cursor to (x,y) location
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle,pos);
}
void startup() // Data initialization
{
 high=18; // Initialization boundary
 width=26;

 bird_x=high/2; // Initializes the bird coordinates
 bird_y=width/2;

 bar_y=width; // Baffle coordinates

 bar_xTop=high/2; // Baffle opening
 bar_xDown=bar_xTop+4;

 score=0; // score

 HideCursor(); // Hide the cursor
}
void show() // display
{
 int i,j;
 gotoxy(0,0);
 for(i=0;i<=high+1;i++)
 {
 for(j=0;j<=width;j++)
 {
  if((i==bird_x)&&(j==bird_y))// Output the bird @
  printf("@");
  else if(i==high+1) // Output lower boundary
   printf("_");
  else if(j==width) // Output right boundary
   printf("|");
  else if((j==bar_y)&&((i<=bar_xTop)||(i>=bar_xDown))) // Output damper
   printf("|");
  else printf(" ");
 }
 printf("\n");
 }
 printf(" Score: %d\n",score);
}
void updateWithoutInput() // Updates unrelated to user input
{
 if(bird_y==bar_y-1)
 {
 if((bird_x>bar_xTop)&&(bird_x<bar_xDown)) // Birds score points by opening the baffle
 score++;
 else
 {
  printf(" The bird death \n"); // The bird didn't get through. The bird died
  exit(0);
 }
 }

 if(bar_y>0)
 bar_y--;
 else
 {
 bar_y=width;
 bar_xTop=rand()%(high-4);
 bar_xDown=bar_xTop+4;
 }
 if(bird_x<high+1)
 bird_x++;
 else
 {
 printf(" The bird death \n");
 exit(0);
 }

 Sleep(200);
}
void updateWithInpute() // Updates related to user input
{
 char input;

 if(kbhit())
 {
 input=getch();
 if((input==' ')&&(bird_x>0)&&(bird_x<=high) ) // Bird jumps up
  bird_x=bird_x-2;
 }
}
int main()
{
 startup(); // Data initialization
 while(1)
 {
 show(); // display
 updateWithoutInput(); // Updates unrelated to user input
 updateWithInpute(); // Updates related to user input
 }
}
