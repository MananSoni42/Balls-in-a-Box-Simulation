#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<math.h>
#include<stdlib.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>

int X=639,Y=479,n=1,get[8]={1,2,3,4,9,10,11,12};
float ewx=0.97,ewy=0.93,a=1.0,Vx=0,Vy=0,V=0;

class ball
{ public:
  int cf,m,r,col,ch;
  float ax[2],ay[2];
  float tx,ty,x,y,x0,y0,e;
  float vx,vy,vy0,vx0;
  ball()
  { tx=0; ty=0; cf=0; ch=0; }
}b[50];

void init()
{ clrscr();
  randomize();
  int i,c;
  B:
  cout<<"Enter Number of Particles: ";cin>>n;
  if (n>50)
  { goto B; }
  clrscr();
  A:
  cout<<"Enter 1. to manually enter values,  2. to give random values: ";cin>>c;
  clrscr();
 if (c==1)
 { for (i=0;i<n;i++)
   { gotoxy(42,1);
     cout<<"BLUE:1";
     gotoxy(42,2);
     cout<<"GREEN:2";
     gotoxy(42,3);
     cout<<"CYAN:3";
     gotoxy(42,4);
     cout<<"RED:4";
     gotoxy(42,5);
     cout<<"LIGHTBLUE:9";
     gotoxy(42,6);
     cout<<"LIGHTGREEN:10";
     gotoxy(42,7);
     cout<<"LIGHTCYAN:11";
     gotoxy(42,8);
     cout<<"LIGHTRED:12";
     gotoxy(1,1);
     cout<<"Enter Mass of particle "<<i+1<<": ";cin>>b[i].m;
     cout<<endl<<"Enter Radius of Particle "<<i+1<<": ";cin>>b[i].r;
     cout<<endl<<"Enter 'e' for Particle "<<i+1<<": ";cin>>b[i].e;
     cout<<endl<<"Enter colour of Particle "<<i+1<<": ";cin>>b[i].col;
     cout<<endl<<"Enter x co-ord of Particle "<<i+1<<": ";cin>>b[i].x0;
     cout<<endl<<"Enter y co-ord of Particle "<<i+1<<": ";cin>>b[i].y0;
     cout<<endl<<"Enter velocity (in x) of Particle "<<i+1<<": ";cin>>b[i].vx0;
     cout<<endl<<"Enter velocity (in y) of Particle "<<i+1<<": ";cin>>b[i].vy0;
     b[i].x=b[i].x0;
     b[i].y=b[i].y0;
     b[i].vx=b[i].vx0;
     b[i].vy=b[i].vy0;
     clrscr();
   }
 }
 if (c==2)
 { for (i=0;i<n;i++)
   { b[i].m=1+random(100);
     b[i].r=4+random(2);
     b[i].x0=b[i].r+random(X-b[i].r);
     b[i].y0=b[i].r+random(Y-b[i].r);
     b[i].vx0=-25+random(51);
     b[i].vy0=-25+random(51);
//     b[i].e=random(1000)%11;
//     b[i].e=b[i].e/10;
     b[i].e=1.0;
     b[i].col=random(8); b[i].col=get[b[i].col];
     b[i].x=b[i].x0; b[i].y=b[i].y0;
     b[i].vx=b[i].vx0; b[i].vy=b[i].vy0;
     delay(10);
   }
 }
   else if (c>2 || c<1)
   { goto A; }

  clrscr();
}

int collision(int p,int q)
{ float eb,vp1,vp2,vq1,vq2,vp,vq,up,uq,th,tgt,cp,cq;

  eb=b[p].e*b[q].e;

 if (eb==0)
 {
   b[p].vx0=((b[p].m*b[p].vx)+(b[q].m*b[q].vx))/(b[p].m+b[q].m);
   b[p].vy0=((b[p].m*b[p].vy)+(b[q].m*b[q].vy))/(b[p].m+b[q].m);
   b[q].vx0=((b[p].m*b[p].vx)+(b[q].m*b[q].vx))/(b[p].m+b[q].m);
   b[q].vy0=((b[p].m*b[p].vy)+(b[q].m*b[q].vy))/(b[p].m+b[q].m);
 }
 else
 {
  if (p==q)
  { return 0; }

  if (b[p].x==b[q].x && b[p].y>b[q].y)
  { th=(3.14159/2); }
  if (b[p].x==b[q].x && b[p].y<b[q].y)
  { th=(-3.14159/2); }
  if (b[p].x==b[q].x && b[p].y==b[q].y)
  { return 2; }
  else
  { tgt=(b[p].y-b[q].y)/(b[p].x-b[q].x);
    th=atan(tgt);
  }
  up=(b[p].vx*cos(th))+(b[p].vy*sin(th));
  uq=(b[q].vx*cos(th))+(b[q].vy*sin(th));

  cp=(b[p].vx*sin(th))+(b[p].vy*cos(th));
  cq=(b[q].vx*sin(th))+(b[q].vy*cos(th));

  vp1=(b[p].m-(eb*b[q].m))*up;
  vp2=(b[q].m*(1+eb))*uq;

  vq1=(b[q].m-(eb*b[p].m))*uq;
  vq2=(b[p].m*(1+eb))*up;

  vp=(vp1+vp2)/(b[p].m+b[q].m);
  vq=(vq1+vq2)/(b[q].m+b[p].m);

  if ( ((vp-vq)/(uq-up))<eb+0.01 && ((vp-vq)/(uq-up))>eb-0.01)
  { b[p].vx0=vp*cos(th)+cp*sin(th);
    b[p].vy0=vp*sin(th)+cp*cos(th);
    b[q].vx0=vq*cos(th)+cq*sin(th);
    b[q].vy0=vq*sin(th)+cq*cos(th);
  }

  else
  { return 1; }
 }
  return 0;
}

void main()
{ clrscr();

  init();

  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
  X=getmaxx(),Y=getmaxy();

  int i,j,key,check=0;

//  setbkcolor(DARKGRAY);
  double t,t1=0.1;

while(t<=1000)
 { gotoxy(3,3);
   cout<<t;
   Vx=0; Vy=0; V=0;
   for (i=0;i<n;i++)
   { Vx=Vx+b[i].vx;
     Vy=Vy+b[i].vy;

     if (t==0 || t==t1)
     { b[i].ax[t]=b[i].x;
       b[i].ay[t]=b[i].y;
     }
     if (t>t1)
     { b[i].ax[0]=b[i].ax[1];
       b[i].ay[0]=b[i].ay[1];
       b[i].ax[1]=b[i].x;
       b[i].ay[1]=b[i].y;
     }
     if (b[i].x>=(X-b[i].r) && b[i].tx>1)
     { b[i].tx=0;
       b[i].vx0=(-1)*b[i].vx*ewx;
       b[i].x0=X-b[i].r; b[i].vx=0;
     }

    if (b[i].x<=b[i].r && b[i].tx>1)
    { b[i].tx=0;
      b[i].vx0=(-1)*b[i].vx*ewx;
      b[i].x0=b[i].r; b[i].vx=0;
    }

    if ( b[i].y<=b[i].r && b[i].ty>1)
    { b[i].vy0=(-1)*b[i].vy*ewy;
      b[i].ty=0;
      b[i].y0=b[i].r; b[i].vy=0;
    }

    if ( b[i].y>=(Y-b[i].r) && b[i].ty>1)
    { b[i].vy0=(-1)*b[i].vy*ewy;
      b[i].ty=0;
      b[i].y0=Y-b[i].r; b[i].vy=0;
    }

    b[i].x=b[i].x0 + (b[i].vx0*b[i].tx);
    b[i].y=b[i].y0 +  (b[i].vy0*b[i].ty) + (a*b[i].ty*b[i].ty/2);

    b[i].vx=b[i].vx0;
    b[i].vy=b[i].vy0+(a*b[i].ty);

    for (j=0;j<n;j++)
    { if ( ((b[i].x-b[j].x)*(b[i].x-b[j].x))+((b[i].y-b[j].y)*(b[i].y-b[j].y))<=(b[i].r+b[j].r)*(b[i].r+b[j].r) && b[i].tx>1 && b[i].ty>1 && i!=j && b[i].ch==0 && b[j].ch==0)
      { check=0; b[i].ch=1; b[j].ch=1;
	check=collision(i,j);
	if (check==1)
	{ /*setbkcolor(RED);*/ }
	if (check==0)
	{ //setbkcolor(DARKGRAY);
	  if (b[i].e*b[j].e)
	  {
	    b[i].x0=((b[i].m*b[i].x)+(b[j].m*b[j].x))/(b[i].m+b[j].m);
	    b[i].y0=((b[i].m*b[i].y)+(b[j].m*b[j].y))/(b[i].m+b[j].m);
	    b[j].x0=((b[i].m*b[i].x)+(b[j].m*b[j].x))/(b[i].m+b[j].m);
	    b[j].y0=((b[i].m*b[i].y)+(b[j].m*b[j].y))/(b[i].m+b[j].m);

	    b[i].tx=0; b[i].ty=0;
	    b[j].tx=0; b[j].ty=0;
	  }
	  else
	  { b[i].x0=b[i].x; b[i].y0=b[i].y;
	    b[j].x0=b[j].x; b[j].y0=b[j].y;
	    b[i].tx=0; b[i].ty=0;
	    b[j].tx=0; b[j].ty=0;
	  }
	}
      }
    }
    for (j=0;j<n;j++)
    { if ( ((b[i].x-b[j].x)*(b[i].x-b[j].x))+((b[i].y-b[j].y)*(b[i].y-b[j].y))>=(b[i].r+b[j].r+1)*(b[i].r+b[j].r+1) )
      { b[i].ch=0;
	b[j].ch=0;
      }
    }
   if (t==0)
   { setcolor(WHITE);
     rectangle(0,0,X,Y);
     rectangle(1,1,X-1,Y-1);
     rectangle(2,2,X-2,Y-2);
   }

  if (t>t1)
  {  setcolor(8);
    circle(b[i].ax[0],b[i].ay[0],b[i].r);
    setfillstyle(SOLID_FILL,8);
    floodfill(b[i].ax[0],b[i].ay[0],8);
  }
    setcolor(b[i].col);
    circle(b[i].x,b[i].y,b[i].r);
    setfillstyle(SOLID_FILL,b[i].col);
    floodfill(b[i].x,b[i].y,b[i].col);

    delay(4);
//    cleardevice();

    t+=t1; b[i].tx+=t1; b[i].ty+=t1;
  }
  gotoxy(15,2);
  Vx=Vx/n;
  Vy=Vy/n;
  V=
  sqrt((Vx*Vx)+(Vy*Vy));
  cout<<V;
 }
  A:
  getch();
}


