#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float angle = 0;
float scale = 1;
float tx = 0;
float flame = 1;
int frame = 0;

const float PI = 3.14159;

// Firework data
int fx[3] = {-300, 0, 300};
int age[3] = {0, 15, 30};

// Bresenham Line Algorithm
void line(int x1,int y1,int x2,int y2)
{
    int dx=abs(x2-x1), dy=abs(y2-y1);
    int sx=(x1<x2)?1:-1;
    int sy=(y1<y2)?1:-1;
    int err=dx-dy;

    glBegin(GL_POINTS);

    while(1)
    {
        glVertex2i(x1,y1);

        if(x1==x2 && y1==y2) break;

        int e=2*err;

        if(e>-dy) { err-=dy; x1+=sx; }
        if(e<dx) { err+=dx; y1+=sy; }
    }

    glEnd();
}

// Bresenham Circle Algorithm
void circle(int xc,int yc,int r)
{
    int x=0,y=r,d=3-2*r;

    glBegin(GL_POINTS);

    while(x<=y)
    {
        glVertex2i(xc+x,yc+y);
        glVertex2i(xc-x,yc+y);
        glVertex2i(xc+x,yc-y);
        glVertex2i(xc-x,yc-y);
        glVertex2i(xc+y,yc+x);
        glVertex2i(xc-y,yc+x);
        glVertex2i(xc+y,yc-x);
        glVertex2i(xc-y,yc-x);

        if(d<0) d+=4*x+6;
        else { d+=4*(x-y)+10; y--; }

        x++;
    }

    glEnd();
}

// Rectangle
void rect(float x1,float y1,float x2,float y2,
          float r,float g,float b)
{
    glColor3f(r,g,b);

    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
}

// Triangle
void triangle(float x1,float y1,float x2,float y2,
              float x3,float y3,float r,float g,float b)
{
    glColor3f(r,g,b);

    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

// Diya
void diya(int x,int y)
{
    glColor3f(0.9,0.3,0.05);

    glBegin(GL_POLYGON);
    glVertex2i(x-35,y);
    glVertex2i(x+35,y);
    glVertex2i(x+20,y-25);
    glVertex2i(x-20,y-25);
    glEnd();

    glPushMatrix();
    glTranslatef(x,y+15,0);
    glScalef(1,flame,1);

    triangle(0,25,-12,-10,12,-10,
             1,0.7,0.05);

    glPopMatrix();

    glColor3f(1,1,0.2);
    circle(x,y+15,5);
}

// House
void house()
{
    rect(-220,-150,220,80,0.85,0.5,0.25);

    triangle(-260,80,0,250,260,80,
             0.6,0.1,0.08);

    rect(-40,-150,40,0,0.3,0.12,0.05);

    rect(-190,-10,-110,50,1,0.8,0.1);
    rect(110,-10,190,50,1,0.8,0.1);

    glColor3f(0.2,0.1,0.05);
    line(-150,-10,-150,50);
    line(-190,20,-110,20);
    line(150,-10,150,50);
    line(110,20,190,20);
}

// Tree
void tree()
{
    rect(-430,-150,-390,70,0.4,0.2,0.05);

    glColor3f(0.05,0.6,0.1);
    circle(-410,110,65);
    circle(-455,80,45);
    circle(-365,80,45);
}

// Rangoli
void rangoli()
{
    glColor3f(1,0.2,0.5);
    circle(0,0,80);

    glColor3f(0.1,1,0.5);
    circle(0,0,55);

    glColor3f(1,0.8,0.1);
    circle(0,0,25);

    for(int i=0;i<8;i++)
    {
        float a=i*45*PI/180;

        triangle(0,0,
                 80*cos(a),80*sin(a),
                 80*cos(a+0.3),80*sin(a+0.3),
                 1,0.2,0.5);
    }
}

// Animated firecrackers
void crackers()
{
    for(int i=0;i<3;i++)
    {
        int y = -80 + age[i]*9;

        // Rocket moving upward
        if(age[i] < 30)
        {
            glColor3f(1,0.5,0.1);
            circle(fx[i],y,5);

            glColor3f(1,0.8,0.1);
            line(fx[i],y-5,fx[i],y-25);
        }
        else
        {
            // Explosion particles
            int radius = (age[i]-30)*4;

            float colors[3][3] = {
                {1,0.2,0.1},
                {0.2,1,0.3},
                {0.2,0.5,1}
            };

            glColor3f(colors[i][0],
                      colors[i][1],
                      colors[i][2]);

            for(int j=0;j<16;j++)
            {
                float a=j*22.5*PI/180;

                int x2=fx[i]+radius*cos(a);
                int y2=190+radius*sin(a);

                line(fx[i],190,x2,y2);
                circle(x2,y2,3);
            }

            glColor3f(1,1,0);
            circle(fx[i],190,5);
        }

        if(age[i] > 48)
            age[i]=0;
    }
}

// Stars
void stars()
{
    glColor3f(1,1,1);

    line(-400,300,-380,300);
    line(-390,290,-390,310);

    line(100,320,120,320);
    line(110,310,110,330);

    line(350,300,370,300);
    line(360,290,360,310);

    circle(-200,350,3);
    circle(200,280,3);
}

// Lights
void lights()
{
    for(int x=-200;x<=200;x+=50)
    {
        glColor3f(1,0.8,0.1);
        circle(x,90,6);
    }
}

// Display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky
    rect(-500,-100,500,500,0.02,0.04,0.2);

    // Ground
    rect(-500,-500,500,-100,0.3,0.15,0.08);

    stars();

    // Moon
    glColor3f(1,1,0.8);
    circle(400,270,45);

    // Fireworks and rockets
    crackers();

    // Scenery
    tree();
    house();
    lights();

    // Diyas
    diya(-300,-50);
    diya(300,-50);
    diya(-180,-160);
    diya(180,-160);

    // Rangoli transformations
    glPushMatrix();

    glTranslatef(tx,-280,0);
    glRotatef(angle,0,0,1);
    glScalef(scale,scale,1);

    rangoli();

    glPopMatrix();

    glFlush();
}

// Automatic animation
void update(int value)
{
    frame++;

    angle += 2;
    if(angle>=360)
        angle=0;

    tx += 0.5;
    if(tx>10)
        tx=-10;

    scale += 0.002;
    if(scale>1.15)
        scale=0.85;

    flame = 0.8 + 0.2*sin(frame*0.2);

    for(int i=0;i<3;i++)
        age[i]++;

    glutPostRedisplay();
    glutTimerFunc(40,update,0);
}

// Initialization
void init()
{
    glClearColor(0,0,0,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-500,500,-500,500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPointSize(3);
}

// Main
int main(int argc,char **argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(1000,700);
    glutInitWindowPosition(100,50);

    glutCreateWindow("Live Diwali Celebration");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(40,update,0);

    glutMainLoop();

    return 0;
}
