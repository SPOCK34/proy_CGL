//#include <gl/gl.h>     // The GL Header File
//#include <windows.h>	//Solo para Windows
//#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
//#include <stdlib.h>		// Descomentar para Linux
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>		// Solo para Windows

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#define PI 3.1416
#include "cmodel/CModel.h"



GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };					// Color background
GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };					// Object Color main 
GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };				// Specular color
GLfloat mat_shininess[] = { 100.0 };

GLfloat mat_diffuse7[] = { 0.2, 0.2, 0.0, 1.0 };
GLfloat mat_diffuse8[] = { 0.0, 0.0, 0.1, 1.0 };
GLfloat mat_diffuse9[] = { 0.0, 0.0, 0.8, 1.0 };

GLfloat  rad, resol = 2;
GLfloat Vertice1z, Vertice1x, Vertice1y, Vertice2z, Vertice2x, Vertice2y, Vertice3z, Vertice3x, Vertice3y, Vertice4z, Vertice4x, Vertice4y;
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito

GLfloat ancho, largo, alto;
//NEW// Keyframes
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;
float hombroizqrot = 0.0;

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazoDer;
	float movBrazoDerInc;
	float hombroIzqrotInc;
	float hombroizqrot;


	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=5;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 1.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};
GLfloat  mat_diffuseY[] = { 1, 1, 0.4, 1.0 };
CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture agua;
CTexture mosaico;
CTexture pez;
CTexture t_esferaf;

CTexture tree;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

float pez_der = 0.0;
float pez_izq = 0.0;
float pos_pez = 0.0;
float rota = 0.0;
//Figuras de 3D Studio
CModel kit;
CModel llanta;
CModel astro;
CModel orca;


//Animación del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;

int timer = 0;


GLfloat LightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 			// Ambient Light Values negro
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values blanco
GLfloat LightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };


void ciudad ()
{

		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		
		glPushMatrix(); //Camino3  lateral derecho
			glTranslatef(47,0.0,-19);
			glRotatef(90, 0, 1, 0);
			//glScalef(40,0.1,7);
			glScalef(45,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino4  fondo derecho
			glTranslatef(21.75,0.0,-38);
			//glScalef(40,0.1,7);
			glScalef(43.5,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		
		glPushMatrix(); //Camino5  fondo izquierdo
			glTranslatef(-21.75,0.0,-38);
			//glScalef(40,0.1,7);
			glScalef(43.5,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino6 lateral izquierdo
			glTranslatef(-47,0.0,-19);
			glRotatef(90, 0, 1, 0);
			//glScalef(40,0.1,7);
			glScalef(45,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		/* glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
*/

		
}



void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0 ,2.0 ,1 ,text2.GLindex);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, 0);
			glPushMatrix();//Cabeza
				glTranslatef(0, 1.0, 0);
				fig7.esfera(0.75, 15, 15, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
			glTranslatef(1.25, 0.65, 0);
			glRotatef(-hombroizqrot, 0, 1, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
				glRotatef(-45, 0, 1, 0); 
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
			glTranslatef(-1.25, 0.65, 0);
			glRotatef(hombroizqrot,0,1,0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45, 0, 1, 0); 
				glRotatef(movBrazoDer, 0, 0, 1);
				glRotatef(25, 1, 0, 0); 
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glColor3f(0, 0, 1);
			glTranslatef(0, -1.5, 0);
			fig7.prisma(1, 2, 1, 0);

			glPushMatrix(); //Pie Derecho -->
				glTranslatef(0.75, -0.5, 0);
				glRotatef(-15, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


			glPushMatrix(); //Pie Izquierdo -->
				glTranslatef(-0.75, -0.5, 0);
				glRotatef(-5, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodIzq, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
    //glColor4f(1.0f, 1.0f, 1.0f, 0.5); 
    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	//text2.LoadBMP("hulkcara.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();


	mosaico.LoadTGA("mosaico.tga");
	mosaico.BuildGLTexture();
	mosaico.ReleaseImage();

	agua.LoadTGA("agua.tga");
	agua.BuildGLTexture();
	agua.ReleaseImage();

	//esfera
	t_esferaf.LoadTGA("esferaf.tga");
	t_esferaf.BuildGLTexture();
	t_esferaf.ReleaseImage();

	tree.LoadTGA("Tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	kit._3dsLoad("kitt.3ds");	
	//kit.VertexNormals();
	
	llanta._3dsLoad("k_rueda.3ds");

	astro._3dsLoad("astronaut1.3ds");
	orca._3dsLoad("ORCA.3ds");

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
		KeyFrame[i].giroBrazo =0;
		KeyFrame[i].giroBrazoInc = 0;

	}

	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;

	KeyFrame[1].posX = 0;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;
	KeyFrame[1].rotRodIzq = 60;
	KeyFrame[1].giroMonito = -90.0;
	KeyFrame[1].movBrazoDer = 40;

	KeyFrame[2].posX = 0;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = -3.5;
	KeyFrame[2].rotRodIzq = -20.0;
	KeyFrame[2].giroMonito = 0;
	KeyFrame[2].movBrazoDer = 0;

	KeyFrame[3].posX = 0;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = -3.5;
	KeyFrame[3].rotRodIzq = 40.0;
	KeyFrame[3].giroMonito = 45;
	KeyFrame[3].movBrazoDer = 90;

	KeyFrame[4].posX = 0;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = -3.5;
	KeyFrame[4].rotRodIzq = -40.0;
	KeyFrame[4].giroMonito = -45;
	KeyFrame[4].movBrazoDer = -90;

	//--*/



	//NEW//////////////////NEW//////////////////NEW//////////////////
	
}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void piramide(GLuint textura)
{
	GLfloat vertice[5][3] = {
		{ 0.0*ancho,0.5*largo,0.0*alto },
		{ -0.5*ancho,-0.5*largo,-0.5*alto },
		{ -0.5*ancho,-0.5*largo,0.5*alto },
		{ 0.5*ancho,-0.5*largo,0.5*alto },
		{ 0.5*ancho,-0.5*largo,-0.5*alto },
	};
	//BASE
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);
	//glColor3f(0.275, 0.510, 0.706);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glEnd();

	//CARA UNA
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0.482 , 0.408 , 0.933 );
	glTexCoord2f(0.4f, 0.2f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.2f, 0.7f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 0.2f); glVertex3fv(vertice[0]);
	glEnd();
	//CARA DER
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0.737, 0.561, 0.561);
	glTexCoord2f(0.3f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.8f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.55f, 0.8f); glVertex3fv(vertice[0]);
	glEnd();
	//CARA IZQ
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0.412, 0.412 , 0.412);
	glTexCoord2f(0.0f, 0.4f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.5f, 0.4f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.25f, 1.0f); glVertex3fv(vertice[0]);
	glEnd();
	//CARA ATRAS
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0.184, 0.310, 0.310);
	glTexCoord2f(0.4f, 0.2f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.2f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.7f, 0.8f); glVertex3fv(vertice[0]);
	glEnd();

}

void tablero()
{
	


	
	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0,1,0);
	glVertex3f(0,0,0.0);
	 glVertex3f(-0.5,0,0.866);
	 glVertex3f(0.5,0,0.866);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, 0.0);
	glVertex3f(0.5, 0, -0.866);
	glVertex3f(-0.5, 0, -0.866);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, 0.0);
	glVertex3f(0.5, 0, 0.866);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, 0.0);
	glVertex3f(-0.5, 0, 0.866);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, 0.0);
	glVertex3f(1, 0, 0);
	glVertex3f(0.5, 0, -0.866);
	
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, 0.0);
	glVertex3f(-0.5, 0, -0.866);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(1.5, 0, 0.866);
	glVertex3f(1, 0, 0);
	glVertex3f(0.5, 0, 0.866);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(-1.5, 0, 0.866);
	glVertex3f(-1, 0, 0);
	glVertex3f(-0.5, 0, 0.866);
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(-1.5, 0, -0.866);
	glVertex3f(-1, 0, 0);
	glVertex3f(-0.5, 0, -0.866);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(1.5, 0, -0.866);
	glVertex3f(1, 0, 0);
	glVertex3f(0.5, 0, -0.866);
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, 1.732);
	glVertex3f(0.5, 0, 0.866);
	glVertex3f(-0.5, 0, 0.866);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse9);
	glNormal3f(0, 1, 0);
	glColor3f(0.184, 0.310, 0.310);
	glVertex3f(0, 0, -1.732);
	glVertex3f(-0.5, 0, -0.866);
	glVertex3f(0.5, 0, -0.866);
	glEnd();

}
void prisma2(GLuint text, GLuint text2)  //Funcion creacion prisma
{

	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
	};


	glBindTexture(GL_TEXTURE_2D, text2);   // choose the texture to use.
										   //glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
							//glColor3f(0.0,0.0,1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
							//glColor3f(0.0,0.0,1.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
							//glColor3f(0.0,1.0,0.0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
						  //glColor3f(1.0,1.0,1.0);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
						  //glColor3f(0.4,0.2,0.6);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	glBegin(GL_POLYGON);  //Top
						  //glColor3f(0.8,0.2,0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(pez_der + 1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(pez_der + 1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(pez_izq, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(pez_izq, 0.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void esfera(GLuint text) {
	float incRad = PI / resol;
	float phi = 0, teta = 0;
	glBindTexture(GL_TEXTURE_2D, text);
	for (teta = 0; teta<PI; teta += incRad) {
		for (phi = 0; phi<2 * PI; phi += incRad) {
			//VERTICE 1
			Vertice1z = (rad)*((float)sin(teta))*((float)cos(phi));
			Vertice1x = (rad)*((float)sin(teta))*((float)sin(phi));
			Vertice1y = (rad)*((float)cos(teta));
			//VERTICE 2
			Vertice2z = (rad)*((float)sin(teta + incRad))*((float)cos(phi));
			Vertice2x = (rad)*((float)sin(teta + incRad))*((float)sin(phi));
			Vertice2y = (rad)*((float)cos(teta + incRad));
			//VERTICE 3
			Vertice3z = (rad)*((float)sin(teta + incRad))*((float)cos(phi + incRad));
			Vertice3x = (rad)*((float)sin(teta + incRad))*((float)sin(phi + incRad));
			Vertice3y = (rad)*((float)cos(teta + incRad));
			//VERTICE 4
			Vertice4z = (rad)*((float)sin(teta))*((float)cos(phi + incRad));
			Vertice4x = (rad)*((float)sin(teta))*((float)sin(phi + incRad));
			Vertice4y = (rad)*((float)cos(teta));
			glBegin(GL_TRIANGLES);
			//TRIANGULO 1
			//glColor3f(0.412, 0.412, 0.412);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(Vertice1x, Vertice1y, Vertice1z);
			glTexCoord2f(0.5, 1.0);
			glVertex3f(Vertice2x, Vertice2y, Vertice2z);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(Vertice3x, Vertice3y, Vertice3z);
			//TRIANGULO2
			//glColor3f(0.184, 0.310, 0.310);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(Vertice1x, Vertice1y, Vertice1z);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(Vertice3x, Vertice3y, Vertice3z);
			glTexCoord2f(0.5, 1.0);
			glVertex3f(Vertice4x, Vertice4y, Vertice4z);
			glEnd();
		}
	}

}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	
	glPushMatrix();

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					//glScalef(0.5, 0.5, 0.5);
					//monito();
					glCallList(ciudad_display_list);
					glTranslated(0,3,2);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);
					monito();

					

				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();

			glPushMatrix();
				glRotatef(90, 0, 1, 0);
				glScalef(0.3, 0.3, 0.3);

				glTranslatef(movKitX, 4, movKitZ);
				glRotatef(rotKit, 0, 1, 0);

				kit.GLrender(NULL,_SHADED,1.0); //Dibujamos la carroceria
				//llanta.GLrender(NULL,_SHADED,1.0);

				//Colocar aquí las llantas
				glPushMatrix(); //llanta frontal der
					glTranslatef(-6,-1,7.5);
					glRotatef(-rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

				glPushMatrix(); //llanta frontal izq
					glTranslatef(6,-1,7.5);	
					glRotatef(180,0,1,0);
					glRotatef(rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();
				
				glPushMatrix(); //llanta trasera der
					glTranslatef(-6,-1,-9.5);	
					glRotatef(-rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

				glPushMatrix(); //llanta trasera izq
					glTranslatef(6,-1,-9.5);	
					glRotatef(180,0,1,0);
					glRotatef(rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

			glPopMatrix();
			

			glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text3.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//orca
			glPushMatrix();
			glTranslatef(0.0, -1.0, 9.5);
			glTranslatef(pos_pez, 0.0f, 0.0f);
			glRotatef(90 + rota, 0.0, 1.0, 0.0);
			orca.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
			glPopMatrix();


			glPushMatrix();
			glTranslatef(0.0, -1.0, -9.5);
			glTranslatef(pos_pez, 0.0f, 0.0f);
			glRotatef(90 + rota, 0.0, 1.0, 0.0);
			orca.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
			glPopMatrix();

			glPushMatrix(); //pecera/alberca
			glTranslatef(0.0, -2.5, 0);
			//glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(131, 5.0, 117.5);
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			prisma2(agua.GLindex, mosaico.GLindex);
			glDisable(GL_BLEND);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			//astronauta 
			glPushMatrix();
			glTranslated(0, 4, -8);
			glScalef(0.03, 0.03, 0.03);
			glTranslated(0, pos_pez, pos_pez + 0.4);
			astro.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
			glPopMatrix();
			 //tablero

			glPushMatrix();
			glTranslated(4, 1, -8);
			glScalef(2, 1, 2);
			tablero();
			glPopMatrix();
			

			//canica

			glPushMatrix();
			glTranslated(0, 1, -8);
			glScalef(1.5, 1.5, 1.5);
			esfera(t_esferaf.GLindex);
			glPopMatrix();
			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); 

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Practica 11");
			pintaTexto(-11,10.5,-14,(void *)font,"Animacion por Keyframes");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	//-------ballena
	pez_der += 0.001;//agua mueves textura
	pez_izq += 0.001;//agua 
					 //pos_pez mueve el plano del pez
	pos_pez += 0.01;
	if (pos_pez >= 45)
		rota = -180.0;
	if (pos_pez <= -45)
		rota = 0.0;
	if (rota == -180.0)
		pos_pez -= 0.05;
	if (rota == 0.0)
		pos_pez += 0.05;



	//-----------------------------------
	fig3.text_izq-= 0.01;
	fig3.text_der-= 0.01;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del coche
	if(g_fanimacion)
	{
		if(g_avanza)
		{
			movKitZ +=1.0;
			rotTires -= 10;
			if(movKitZ>130)
				g_avanza = false;
		}
		else
		{

			movKitZ -=1.0;
			rotTires += 10;
			if(movKitZ<0)
				g_avanza = true;
		}
	}

	if(circuito)
	{
		if(recorrido1)
		{
			movKitZ ++;
			if(movKitZ>155)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if(recorrido2)
		{
			rotKit = 90;
			movKitX++;
			if(movKitX > 125)
			{
				recorrido2 = false;
				recorrido3 = true;
				
			}
		}
		if(recorrido3)
		{
			rotKit = 180;
			movKitZ --;
			if(movKitZ<-155)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if(recorrido4)
		{
			rotKit = 270;
			movKitX --;
			if(movKitX<0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if(recorrido5)
		{
			rotKit = 0;
			movKitZ ++;
			if(movKitZ>0)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}
	}


	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;		//100 frames
				KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;		//100 frames
				KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;		//100 frames
				KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;		//100 frames
				KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;		//100 frames
				KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;		//100 frames
				KeyFrame[playIndex].hombroIzqrotInc = (KeyFrame[playIndex + 1].hombroizqrot - KeyFrame[playIndex].hombroizqrot) / i_max_steps;

			}
		}
		else
		{	//Draw information
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			giroMonito += KeyFrame[playIndex].giroMonitoInc;
			movBrazoDer += KeyFrame[playIndex].movBrazoDerInc;
			hombroizqrot += KeyFrame[playIndex].hombroIzqrotInc;
			i_curr_steps++;
		}

	}

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'z':  //braxos
			hombroizqrot++;
			break;
		case 'Z':
			hombroizqrot--;
			
			break;

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'O':		//  
		case 'o':
				g_fanimacion^= true; //Activamos/desactivamos la animacíon
				circuito = false;
			break;

		case 'i':		//  
		case 'I':
				circuito^= true; //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;

		case 'k':		//
		case 'K':
			if (FrameIndex<MAX_FRAMES)
			{
				printf("frameindex %d\n", FrameIndex);

				KeyFrame[FrameIndex].posX = posX;
				KeyFrame[FrameIndex].posY = posY;
				KeyFrame[FrameIndex].posZ = posZ;

				KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
				KeyFrame[FrameIndex].giroMonito = giroMonito;
				KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;
				KeyFrame[FrameIndex].hombroizqrot = hombroizqrot;
				FrameIndex++;
			}
			
			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				posX = KeyFrame[0].posX;
				posY = KeyFrame[0].posY;
				posZ = KeyFrame[0].posZ;
				rotRodIzq = KeyFrame[0].rotRodIzq;
				giroMonito = KeyFrame[0].giroMonito;
				movBrazoDer = KeyFrame[0].movBrazoDer;
				hombroizqrot = KeyFrame[0].hombroizqrot;
				//First Interpolation
				KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;		//100 frames
				KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;		//100 frames
				KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;		//100 frames
				KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;		//100 frames
				KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;		//100 frames
				KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;		//100 frames
				KeyFrame[playIndex].hombroIzqrotInc = (KeyFrame[playIndex + 1].hombroizqrot - KeyFrame[playIndex].hombroizqrot) / i_max_steps;

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			//printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			//printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			//printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			//printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			//printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			//printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			//printf("%f \n", giroMonito);
			break;

		case 'P':						
			giroMonito--;
			//printf("%f \n", giroMonito);
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 11"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}
