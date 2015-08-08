
/******************************************************************************/

/*********************************MySnake.eXe**********************************/

/**********************Game For My sisters  Anu & Anju*************************/

/*********----------By Jithin.p [G.P.T.C Thirurangadi]-----------**************/

/******************************************************************************/

#include<conio.h>
#include<math.h>
#include<process.h>
#include<stdio.h>
#include<stdlib.h>

#include<vision07.h>

#define MWW 26
#define MWH 26

#define MAXL 100
#define CLC  15
#define SNKC 6

/*************------------------Global Variabls-------------------*************/

short Left=OFF;
short Right=ON;
short Up=OFF;
short Down=OFF;

short PrLeft=OFF;
short PrRight=ON;
short PrUp=OFF;
short PrDown=OFF;

long int Points=0;
short NoFood=FALSE;

int Len=2;
int TDLY=275;

/*************------------------------END-------------------------*************/

void eli(int x,int y,int s)
 {
  setfillstyle(s,2);
  fillellipse(x,y,25,25);
 }

void welcomePage()
 {
  int i,c;
  float f;
  setcolor(12);
  for(i=0;i<400;i++)
   {
    f=(i*(PI/180));
    c=(-1)*(int)((cos(f))*200);
    c=c+250;
    putpixel(i,c,14);
    delay(10);
    eli(i,c,1);
   }
  settextstyle(7,0,7);
  setcolor(4);
  outtextxy(400,150,"Snake.!");
  settextstyle(7,0,3);
  setcolor(15);
  outtextxy(300,300,"Press Spase To Continue...!");
  setcolor(9);
  outtextxy(300,350,"Controls");
  outtextxy(300,385,"Esc");
  outtextxy(375,400,"<- ->");
  getch();
  cleardevice();
  setbkcolor(0);
  setcolor(CLC);
 }
struct storePr
 {
  int x1;
  int y1;
 };
storePr *stp=new storePr;

void strucp(storePr *St1,storePr *St2)
 {
  St1->x1=St2->x1;
  St1->y1=St2->y1;
 }
void storResL(int X1,int Y1)
 {
  int i;
  (stp+Len-1)->x1=X1;
  (stp+Len-1)->y1=Y1;

  for(i=0;i<Len-1;i++)
   {
    strucp(&stp[i],&stp[i+1]);
   }

  (stp+Len-1)->x1=X1;
  (stp+Len-1)->y1=Y1;
 }
int ifkbhit()
 {
  int result;
  result=getBiosKey();
  if(result==UP_ARROW)
   {
    return(8);
   }
  else if(result==DOWN_ARROW)
   {
    return(2);
   }
  else if(result==LEFT_ARROW)
   {
    return(4);
   }
  else if(result==RIGHT_ARROW)
   {
    return(6);
   }
  else if(result==ESC)
   {
    delete stp;
    closegraph();
    exit(0);
   }
  else
   {
    return(0);
   }
  return(0);
 }
void makeFood()
 {
  int X1,Y1;
  randomize();
  setcolor(CLC);
  X1=(rand()%29)*MWW;
  Y1=(rand()%21)*MWH;
  stp[Len-1].x1=X1;
  stp[Len-1].y1=Y1;
  if(SNKC==getpixel(X1+10,Y1+10))
   {
    rectangle(X1,Y1,X1+MWW,Y1+MWH);
    fillRectangle(X1+2,Y1+2,X1+MWW-2,Y1+MWH-2,SNKC,CLC);
    NoFood=TRUE;
   }
  rectangle(X1,Y1,X1+MWW,Y1+MWH);
  fillRectangle(X1+2,Y1+2,X1+MWW-2,Y1+MWH-2,10,CLC);
 }
void makeBlack(int X1,int Y1)
 {
  setcolor(CLC);
  rectangle(X1,Y1,X1+MWW,Y1+MWH);
  fillRectangle(X1+2,Y1+2,X1+MWW-2,Y1+MWH-2,getbkcolor(),CLC);
 }

int catchFoodAndcheckError(int X1,int Y1)
 {
  if(10==getpixel(X1+10,Y1+10))
   {
    NoFood=TRUE;
    TDLY-=5;
    if(TDLY<100)
     {
      TDLY+=25;
     }
    Points+=50;
    return(1);
   }
  else if(SNKC==getpixel(X1+10,Y1+10))
   {
    return(-1);
   }
  NoFood=FALSE;
  return(0);
 }

int checkResult(int X1,int Y1)
 {
  if((X1>590)||(X1<0)||(Y1>430)||(Y1<0)||(-1==catchFoodAndcheckError(X1,Y1)))
   {
    char msg[10];
    viewPort(0,0,getmaxx(),getmaxy(),1);
    cleardevice();
    setcolor(4);
    settextstyle(1,0,SNKC);
    outtextxy(320-.5*(textwidth("Game Over..!")),125,"Game Over..!");
    settextstyle(3,0,4);
    setcolor(9);
    outtextxy(320-.5*(textwidth("Total Points")),200,"Total Points");
    sprintf(msg,"%ld",Points);
    setcolor(10);
    outtextxy(320-.5*(textwidth(msg)),250,msg);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n \t\t\t\t\t      By\n");
    printf("\n\t\t\t\t\tdreamBlitzer\n");
    printf("\n\t\t\t\t\t\tG.P.T.C Thirurangadi");
    rectangle(20,20,620,460);
    delete stp;
    while(ESC!=getBiosKey());
    closegraph();
    exit(0);
   }
  return(0);
 }

int startSnake(int X1,int Y1)
 {
  checkResult(X1,Y1);
  if(NoFood)
   {
    Len++;
    makeFood();
   }
  setcolor(9);
  while(!kbhit())
   {
    rectangle(X1,Y1,X1+MWW,Y1+MWH);
    fillRectangle(X1+2,Y1+2,X1+MWW-2,Y1+MWH-2,SNKC,CLC);
    storResL(X1,Y1);
    delay(TDLY);
    if(10!=getpixel(stp[0].x1+10,stp[0].y1+10))
     {
      makeBlack(stp[0].x1,stp[0].y1);
     }
    if(Right)
     {
      X1+=MWW;
      catchFoodAndcheckError(X1,Y1);
      startSnake(X1,Y1);
     }
    if(Left)
     {
      X1-=MWW;
      catchFoodAndcheckError(X1,Y1);
      startSnake(X1,Y1);
     }
    if(Up)
     {
      Y1-=MWH;
      catchFoodAndcheckError(X1,Y1);
      startSnake(X1,Y1);
     }
    if(Down)
     {
      Y1+=MWH;
      catchFoodAndcheckError(X1,Y1);
      startSnake(X1,Y1);
     }
   };

  switch (ifkbhit())
   {
    case 8 :
     if(!PrDown)
      {
       Up=ON;
       Down=OFF;
       Left=OFF;
       Right=OFF;
       PrUp=ON;
       PrDown=OFF;
       PrLeft=OFF;
       PrRight=OFF;
       startSnake(X1,Y1);
      }
     break;
    case 2:
     if(!PrUp)
      {
       Up=OFF;
       Down=ON;
       Left=OFF;
       Right=OFF;
       PrDown=ON;
       PrUp=OFF;
       PrLeft=OFF;
       PrRight=OFF;
       startSnake(X1,Y1);
      }
     break;
    case 6:
     if(!PrLeft)
      {
       Up=OFF;
       Down=OFF;
       Left=OFF;
       Right=ON;
       PrRight=ON;
       PrUp=OFF;
       PrDown=OFF;
       PrLeft=OFF;
       startSnake(X1,Y1);
      }
     break;
    case 4:
     if(!PrRight)
      {
       Up=OFF;
       Down=OFF;
       Left=ON;
       Right=OFF;
       PrLeft=ON;
       PrUp=OFF;
       PrDown=OFF;
       PrRight=OFF;
       startSnake(X1,Y1);
      }
     break;
    default:
      break;
   }
  return(1);
 }
/***********************************************************************************/

int main()
 {
  int choice;
  screenMain();
  //welcomePage();
  rectangle(19,19,621,461);
  viewPort(20,20,620,460,0);
  createImplisitTable(16,16,1);
  makeFood();
  startSnake(0,0);
  return(0);
 }
/*******************************Thank You****************************************/
/********************************Sisters*****************************************/