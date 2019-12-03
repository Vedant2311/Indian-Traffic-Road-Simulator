#include <string>
	#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
	#include <math.h>     // Needed for sin, cos
	#include <fstream>
	#include <iostream>
    #include <stdlib.h>
	#include "parser.h"


	#define PI 3.14159265f
	
	int n=0; 		//total vehicles
	int Total_Time;
	int runningTime;
	int vehicles_on_road;
	int PosX[100][500]; //t=100 and total vehicles on road are max = 500
	int PosY[100][500];
	int carInd[100][500];
	int road_length;
	int road_width;
	int road_zebra_width;
	int road_signal_position;
	int signal[100];
	bool tilted[100][500];
	int tilt_pos[500];
	int is_rickshaw[500];
	int start_end[100][500];
	int j=0;
	std::string Vehicle_Length[50];
	std::string Vehicle_Width[50]; 
	
	// Global variables
	char title[] = "Indian Road Traffic Simulation";  // Windowed mode's title
	int windowWidth  = 640;     // Windowed mode's width
	int windowHeight = 640;     // Windowed mode's height
	int windowPosX   = 50;      // Windowed mode's top-left corner x
	int windowPosY   = 50;      // Windowed mode's top-left corner y
	
	float colorx[500];
	float colory[500];
	float colorz[500];

	GLfloat ballRadius = 0.05f;   // Radius of the bouncing ball
	GLfloat ballX1 = 0.72f;         // Ball's center (x, y) position
	GLfloat ballY1 = 0.8f;

	GLfloat ballX2 = 0.88f;         // Ball's center (x, y) position
	GLfloat ballY2 = 0.8f;
	int refreshMillis = 200;      // Refresh period in milliseconds

	// Projection clipping area
	GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

	float Xset(int a)
	{
		float b;
		b = (float)(2.2*a/road_length)-1.0;
		return b;
	}

	float Yset(int a)
	{
		float b;
		b = (float)(1.35*a/road_width)-0.65;
		//std::cout<<a<<" b   b b b b b "<<b<<std::endl;
		return b;
	}

	void initGL() {
	   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
	}
	 
	
	/* Callback handler for window re-paint event */
	void display() {
	   glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
	   glMatrixMode(GL_PROJECTION);    // To operate on the model-view matrix
	   glLoadIdentity();              // Reset model-view matrix
	 
	// std::cout<<"hi"<<std::endl;
	
	//road upper

	if(signal[j] == 0)
	{
		//std::cout<<Xset(road_signal_position)<<" x pos signal "<<std::endl;
	//signal 1
	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_LINES);
	    glColor3f(0.9f,0.9f,1.0f);
	      glVertex2f(Xset(road_signal_position), 1.0f);       // line
	      glVertex2f(Xset(road_signal_position), -1.0f);   
	    glEnd();
	
	//signal 2
		//std::cout<<(road_signal_position)<<" "<<Xset(road_zebra_width)<<" x pos signal "<<std::endl;

	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_LINES);
	    glColor3f(0.9f,0.9f,1.0f);
	      glVertex2f(Xset(road_signal_position + road_zebra_width), 1.0f);       // line
	      glVertex2f(Xset(road_signal_position + road_zebra_width), -1.0f);   
	    glEnd();
	}
	//grass upper
	glBegin(GL_QUADS);
	
		glColor3f(0.0f,1.0f,0.0f);  //green
		glVertex2f(-3.0f, 0.7f);
		glVertex2f(3.0f, 0.7f);
		glVertex2f(-3.0f, 3.8f);
		glVertex2f(3.0f, 3.8f);		
		glEnd();
	//grass lower
	glBegin(GL_QUADS);
	
		glColor3f(0.0f,1.0f,0.0f);  //green
		glVertex2f(-3.0f, -0.7f);
		glVertex2f(3.0f, -0.7f);
		glVertex2f(-3.0f, -3.8f);
		glVertex2f(3.0f, -3.8f);		
		glEnd();

	//road upper
	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	 glBegin(GL_QUADS);
	    glColor3f(1.0f,1.0f,1.0f);
	      glVertex2f(-3.0f, 0.7f);       // line
	      glVertex2f(-3.0f, 0.8f); 
	      glVertex2f(3.0f, 0.8f);   
	      glVertex2f(3.0f, 0.7f);   

	    glEnd();

	//road lower
	glTranslatef(0.0f, 0.0f, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_QUADS);
	    glColor3f(1.0f,1.0f,1.0f);
	      glVertex2f(-3.0f, -0.7f);       // line
	      glVertex2f(-3.0f, -0.8f);
	      glVertex2f(3.0f, -0.8f);   
	      glVertex2f(3.0f, -0.7f);   
	    glEnd();

	//black box
	glTranslatef(0.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
		glColor3f(0.0f,0.0f,0.0f);  //green
		glVertex2f(.65f, .73f);
		glVertex2f(.95f, .73f);
		glVertex2f(.95f, .87f);
		glVertex2f(.65f, .87f);		
		glEnd();

		//red light
	  glTranslatef(ballX1, ballY1, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_TRIANGLE_FAN);
	      if(signal[j] == 0) 
	      	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	      else glColor3f(0.5f, 0.0f, 0.0f); //green 
	      glVertex2f(0.0f, 0.0f);       // Center of circle
	      int numSegments = 100;
	      GLfloat angle;
	      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
	         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
	         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	      }
	   glEnd();
	   	//green light
	   glTranslatef(-ballX1,-ballY1, 0.0f); 
	     glTranslatef(ballX2, ballY2, 0.0f);  // Translate to (xPos, yPos)
	    glBegin(GL_TRIANGLE_FAN);
	      if(signal[j] == 1) 
	      	glColor3f(0.0f, 1.0f, 0.0f);  // Green
	      else glColor3f(0.0f, 0.5f, 0.0f); //Red 
	      glVertex2f(0.0f, 0.0f);       // Center of circle
	      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
	         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
	         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	      }
	   glEnd();

	   glTranslatef(-ballX2,-ballY2, 0.0f);
if(j<=runningTime){
		for(int i=1; i<n+1; i++)
		{
			//std::cout<<";;;;;;;;;;;dsfergfvrs;;;;;;;;;;;;;;;;;;;;;"<<n+1<<std::endl;
			//std::cout<<"road_length "<<road_length<<endl;
			float l,b;
			if(PosX[j][i]>=0)
			{	l = (float)atoi(Vehicle_Length[carInd[j][i]].c_str())*2/road_length;

			//std::cout<<atoi(Vehicle_Length[carInd[j][i]].c_str())*10<<" l==  "<<l<<std::endl;

				b = (float)atoi(Vehicle_Width[carInd[j][i]].c_str())*(1.35)/road_width;
			//std::cout<<b<<std::endl;
			if(tilted[j][i]==false)
			{	//std::cout<<"yo 1 \n";
				glTranslatef(Xset(PosX[j][i]),-Yset(PosY[j][i]),0.0f);
			 	// std::cout<<(PosX[j][i])<<" "<<Xset(PosX[j][i])<<std::endl;
			 	// std::cout<<(PosY[j][i])<<" "<<-Yset(PosY[j][i])<<std::endl;
			 	// std::cout<<"i "<<i<<" j "<<j<<std::endl;
				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,0.0f);      
			  	glVertex2f(-(0.9)*l, 0.0f);
			  	glVertex2f(-(0.9)*l,(0.9)*b);
			  	glVertex2f(0.0f,(0.9)*b);
				glEnd();

			glTranslatef(-Xset(PosX[j][i]),Yset(PosY[j][i]),0.0f);
			}
			else if(is_rickshaw[i]==0){	 
			if(tilt_pos[i]==0)
			{
				//std::cout<<"yo 2 i "<<i<<"j "<<j<<endl;
				tilt_pos[i] = 1;
				
				if(start_end[j][i]==1){
				//std::cout<<"5 \n";
				glTranslatef(Xset(PosX[j-1][i]),-Yset(PosY[j-1][i]),0.0f);
				//position 1 and overtake above  ______|
				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,0.0f);      
			  	glVertex2f(-(0.9)*l*2/3, 0.0f);
			  	glVertex2f(-(0.9)*l*2/3,(0.9)*b);
			  	glVertex2f(0.0f,(0.9)*b);
				glEnd();

				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,(0.9)*b);      
			  	glVertex2f(-(0.9)*b, (0.9)*b);
			  	glVertex2f(-(0.9)*b,(0.9)*b+(0.9)*l/3);
			  	glVertex2f(0.0f,(0.9)*b+(0.9)*l/3);
				glEnd();

			glTranslatef(-Xset(PosX[j-1][i]),Yset(PosY[j-1][i]),0.0f);}
				
				
				else{

				//std::cout<<"3 \n";
				glTranslatef(Xset(PosX[j-1][i]),-Yset(PosY[j-1][i]),0.0f);
				//position 1 and overtake below  ********|
				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,0.0f);      
			  	glVertex2f(-(0.9)*l*2/3, 0.0f);
			  	glVertex2f(-(0.9)*l*2/3,(0.9)*b);
			  	glVertex2f(0.0f,(0.9)*b);
				glEnd();

				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,0.0f);      
			  	glVertex2f(0.0f, -(0.9)*l*2/3);
			  	glVertex2f(-(0.9)*b,-(0.9)*l*2/3);
			  	glVertex2f(-(0.9)*b,0.0f);
				glEnd();	

			glTranslatef(-Xset(PosX[j-1][i]),Yset(PosY[j-1][i]),0.0f);}
				

			}
		
			else if(tilt_pos[i]==1)
			{
				tilt_pos[i] = 0;
				//cout<<"yo3 "<<i<<endl;
				if(start_end[j][i]==1){
				//position 2 and overtake above |********
				glTranslatef(Xset(PosX[j][i]),-Yset(PosY[j][i]),0.0f);
				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,-(0.9)*b-(0.9)*l/3);      
			  	glVertex2f((0.9)*b, -((0.9)*b+(0.9)*l/3));
			  	glVertex2f((0.9)*b,-(0.9)*b);
			  	glVertex2f(0.0f,-(0.9)*b);
				glEnd();

				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,0.0f);      
			  	glVertex2f((0.9)*l*2/3,0.0f);
			  	glVertex2f((0.9)*l*2/3,-(0.9)*b);
			  	glVertex2f(0.0f,-(0.9)*b);
				glEnd();

			glTranslatef(-Xset(PosX[j][i]),Yset(PosY[j][i]),0.0f); }
				
				else{
				//	cout<<"yo4 \n";
				//position 2 and overtake below |________
				glTranslatef(Xset(PosX[j][i]),-Yset(PosY[j][i]),0.0f);
				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,+(0.9)*b+(0.9)*l/3);      
			  	glVertex2f((0.9)*b, ((0.9)*b+(0.9)*l/3));
			  	glVertex2f((0.9)*b,(0.9)*b);
			  	glVertex2f(0.0f,(0.9)*b);
				glEnd();

				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f(0.0f,0.0f);      
			  	glVertex2f((0.9)*l*2/3,0.0f);
			  	glVertex2f((0.9)*l*2/3,(0.9)*b);
			  	glVertex2f(0.0f,(0.9)*b);
				glEnd();

			glTranslatef(-Xset(PosX[j][i]),Yset(PosY[j][i]),0.0f); 
				}
				

			}
		}
		 else 
			 {
			// cout<<"yo5 \n";
				glTranslatef(Xset(PosX[j][i]),-Yset(PosY[j][i]),0.0f);
				glBegin(GL_QUADS);
				glColor3f(colorx[atoi(Vehicle_Length[carInd[j][i]].c_str())], colory[atoi(Vehicle_Length[carInd[j][i]].c_str())],colorz[atoi(Vehicle_Length[carInd[j][i]].c_str())]);
			  	glVertex2f((0.9)*l/2,0.0f);      
			  	glVertex2f(0.0f, (0.9)*b);
			  	glVertex2f(-(0.9)*l,0.0f);
			  	glVertex2f(0.0f,-(0.9)*b);
				glEnd();

			glTranslatef(-Xset(PosX[j][i]),Yset(PosY[j][i]),0.0f);	 
			}
		}
	}
}
	   glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
	 
	   if(j<=runningTime)
	   	j++;
	// std::cout<<(PosX[j][i])<<" "<<Xset(PosX[j][i])<<std::endl;
	// 		 	// std::cout<<(PosY[j][i])<<" "<<-Yset(PosY[j][i])<<std::endl;
	// 		 	  std::cout<<j<<" this is j "<<endl;
	
	}
	/* Call back when the windows is re-sized */
	void reshape(GLsizei width, GLsizei height) {
	   // Compute aspect ratio of the new window
	   if (height == 0) height = 1;                // To prevent divide by 0
	   GLfloat aspect = (GLfloat)width / (GLfloat)height;
	 
	   // Set the viewport to cover the new window
	   glViewport(0, 0, width, height);
	 
	   // Set the aspect ratio of the clipping area to match the viewport
	   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	   glLoadIdentity();             // Reset the projection matrix
	   if (width >= height) {
	      clipAreaXLeft   = -1.0 * aspect;
	      clipAreaXRight  = 1.0 * aspect;
	      clipAreaYBottom = -1.0;
	      clipAreaYTop    = 1.0;
	   } else {
	      clipAreaXLeft   = -1.0;
	      clipAreaXRight  = 1.0;
	      clipAreaYBottom = -1.0 / aspect;
	      clipAreaYTop    = 1.0 / aspect;
	   }
	   gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	   }
	 
	 
	/* Called back when the timer expired */
	void Timer(int value) {
	   glutPostRedisplay();    // Post a paint request to activate display()
	   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
	}
	 
	/* Main function: GLUT runs as a console application starting at main() */
	int main(int argc, char** argv) {	

		srand (time(NULL));
		

		for(int i=0; i<100; i++)
		{
			for(int j=0; j<500; j++)
				tilted[i][j]=false;
			tilt_pos[i]=0;
		}
	   simulation(n, Total_Time, vehicles_on_road, PosX, PosY, carInd, Vehicle_Length, Vehicle_Width,runningTime, road_length, road_width, road_zebra_width, road_signal_position,signal,tilted,start_end, is_rickshaw);
		//start_end = 1 for start (overtake below) ; start_end = 0 for end (overtake above) 
	   //std::cout<<"road_length "<<road_length<<endl;
	   //std::cout<<"road_width "<<road_width<<endl;


	   for(int i=0; i<500; i++)
	   {
	   	colorz[i]=(rand()%100)/100.0f;
	   	colory[i]=(rand()%100)/100.0f;
	   	colorx[i]=(rand()%100)/100.0f;
	   }
	   glutInit(&argc, argv);            // Initialize GLUT
	   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
	   glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
	   glutCreateWindow(title);      // Create window with given title
	   glutDisplayFunc(display);     // Register callback handler for window re-paint
	   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	   glutTimerFunc(0, Timer, 0);   // First timer call immediately
	   initGL();                     // Our own OpenGL initialization
	   glutMainLoop();               // Enter event-processing loop
	   return 0;
	}