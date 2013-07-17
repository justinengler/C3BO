/**
* Cartesian Coordinate Capacitive Bruteforce Overlay
*                  C3BO
*
*	Copyright 2013 Justin Engler
*
*/
#include "simpletools.h"
#include <propeller.h>        // Propeller-specific functions

#define LED1 16
#define LED2 17
#define LED3 18
#define LED4 19
#define LED5 20
#define LED6 21
#define LED7 22
#define LED8 23

#define LISTSIZE 20
#define PREDELAY 100
#define DOWNDELAY 1000

int buttonlist[LISTSIZE];

void startup();
void processcmd(char*, char*, char*);
void mainloop();

void setbutton(int, int);
void pushbutton(int,int,int);
void buttondown(int);
void buttonup(int);


void startup(){

  pause(500);

  printf("C3BO - %d %d\n",LED1,LED8);
  //printf("Enter your name:\n");
  
  //char str[11];
  //scanf("%10s",str);

  //printf("Your name is %s\n",str);  

  

  //printf("EXITING STARTUP\n");
  
  setbutton(1,LED1);
  setbutton(2,LED2);
  setbutton(3,LED3);
  setbutton(4,LED4);
  setbutton(5,LED5);
  setbutton(6,LED6);

  for (int i=1;i<=6;i++)
  {
    buttonup(i);
  }


/*
  while (1){  
  for (int i=16;i<24;i++){
    printf("Now: %d\n",i);
    high(i);
    pause(500);
    low(i);
  }
    printf("\n\n\n\n");  
  }
*/
  return;
}

void pushbutton(int buttonid, int predelay, int downdelay){

  pause(predelay);
  buttondown(buttonid);
  pause(downdelay);
  buttonup(buttonid);
  
}

void buttonup(int buttonid){
  low(buttonlist[buttonid]);
}

void buttondown(int buttonid){
  high(buttonlist[buttonid]);
}

void setbutton(int buttonid, int pinnumber){
  if (buttonid < LISTSIZE)
  {
    buttonlist[buttonid]=pinnumber;
  }
  else
  {
    printf("ERROR: buttonid >=LISTSIZE(%d)",LISTSIZE);
  }

}

void readbutton(int buttonid){
  printf("%d\n",buttonlist[buttonid]);
}



//void processcmd(char* cmd, char* arg, char* arg2){
void processcmd(char* cmd, int arg, int arg2){
  if (! strncmp(cmd, "PU", 2)) //push a button (down and up)
  {
    pushbutton(arg, PREDELAY, DOWNDELAY);
  }
  else if (! strncmp(cmd, "BD", 2)) //Button down
  {
    buttondown(arg);
  }
  else if (! strncmp(cmd, "BU", 2)) //Button up
  {
    buttonup(arg);
  }
  else if (! strncmp(cmd, "SB", 2)) //Set Button (assign mnemonic to pin)
  {
    setbutton(arg,arg2);
  }
  else if (! strncmp(cmd, "RB", 2)) //Read button (return pin for mnemonic)
  {    
    readbutton(arg);  
  }

  //printf("EXITING processcmd\n");
  return;
}

void mainloop(){
  //printf("ENTERING MAINLOOP\n");
  char cmd[3];
  //char arg[3];
  //char arg2[3];

  int arg;
  int arg2;
  printf(">");
  
  int retval=0;  

  retval=scanf("%2s %2d %2d",cmd,&arg,&arg2);
  //printf("%d\n",retval);

  processcmd(cmd,arg,arg2);
  //printf("EXITING MAINLOOP\n");

}

int main(){
  //printf("START");

  startup();

  printf("STARTUP EXITED, STARTING MAINLOOP\n");
  while (1)
    mainloop();
  

  return 0;
}
