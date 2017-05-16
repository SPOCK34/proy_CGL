//#include <gl/gl.h>     // The GL Header File
//#include <windows.h>	//Solo para Windows
//#include <GL/glut.h>   
#include <stdlib.h>		// Descomentar para Linux
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>		// Solo para Windows
#define PI 3.1416
#include <iostream>
#include <fstream>
using namespace std;

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"
GLfloat ancho = 0, largo = 0, alto = 0;
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display  Monito


									//NEW// Keyframes
float posX = 0, posY = 2.5, posZ = -3.5, rotMusIzq = 0, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;
float movBrazoIzq = 0.0;
float movBrazoIzq2 = 0.0;

float rotMusDer = 0, rotRodDer = 0;
float rota=0;
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
	float movBrazoIzq;
	float movBrazoIzqInc;
	float movBrazoIzq2;
	float movBrazoIzq2Inc;
	

	float rotMusIzq;
	float rotMusDer;
	float rotRodDer;

	float rotMusIzqInc;
	float rotMusDerInc;
	float rotRodDerInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

//var  tablero
GLdouble x_tab = 0, y_tab = 0, z_tab = 0;
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;




//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 18.0f, 0.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };
GLfloat mat_diffuse13[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse11[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat mat_diffuse10[] = { 0.0, 0.0, 0.0, 1.0 };//fondo  tablero
GLfloat mat_diffuse1[] = { 0.4, 0.2, 0.0, 1.0 };   //canicas1
GLfloat mat_diffuse2[] = { 0.0, 0.0, 0.6, 1.0 };   //canicas2
GLfloat mat_diffuse3[] = { 1.0, 0.0, 0.2, 1.0 }; //canica roj
GLfloat mat_diffuse4[] = { 1.0, 1.0, 0.0, 1.0 }; //canica  gelb

GLfloat mat_diffuse5[] = { 0.4, 0.0, 0.4, 1.0 }; //canica  violeta
GLfloat mat_diffuse6[] = { 1.0, 0.2, 0.0, 1.0 }; //canica  orange
GLfloat mat_diffuse7[] = { 0.0, 0.4, 0.0, 1.0 }; //canica  grun  2
GLfloat mat_diffuseLampara[] = { 0.4, 0.1, 0.0, 1.0 }; //luz lampara haup
GLfloat ambiente[] = { 1.0,1.0,1,0 ,1.0};

GLfloat mat_am_silla3[] = { 0.0215,0.1745,	0.0215 };
GLfloat mat_di_silla3[] = { 0.0215,	0.1745,	0.0215 };
GLfloat mat_espec_silla3[] = { 0.0215,	0.1745,	0.0215 };
GLfloat mat_shininess[] = { 0.6 };
CFiguras fig1;

CModel pez1;
CModel lampe1;
CModel robot;
CModel lampeHaup;

CTexture text1;
CTexture text2;
CTexture t_silla1;
CTexture t_silla2;
CTexture t_estante;
CTexture t_asiento;
CTexture t_asiento2;
CTexture tex_mesa, tex_mesa1, tex_mesa2;
CTexture t_dodeca;
//textura Spiele
CTexture t_octa;

CTexture t_piso;
CTexture t_pared1;
CTexture t_pared;
CTexture t_pared2;
CTexture t_pared3;
CTexture t_techo;
CTexture t_fachada;
CTexture t_puerta;
CTexture t_ventana;
CTexture t_poster1;
CTexture t_poster2;
CTexture t_poster3;

CTexture t_jenga1;
CTexture t_jenga2;
CTexture t_monopoly1;
CTexture t_monopoly2;
CTexture t_scrabble1;
CTexture t_scrabble2;


void cuboMesa(GLuint textura)
{
	GLfloat vertice[8][3] = {
		{ 0.5,-0.5,0.5 },//0
		{ 0.45,0.5,0.45 },//1
		{ -0.45,0.5,0.45 },//2
		{ -0.5,-0.5,0.5 },//3
		{ 0.5,-0.5,-0.5 },//4
		{ 0.45,0.5,-0.45 },//5
		{ -0.45,0.5,-0.45 },//6
		{ -0.5,-0.5,-0.5 },//7

	};

	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//hinter
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//Rechts
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//links
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//unter
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//oben
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//vorne
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glEnd();

}//// //mesa
void cubo2(GLuint textura)
{
	GLfloat vertice[8][3] = {
		{ 0.5,-0.5,0.5 },//0
		{ 0.5,0.5,0.5 },//1
		{ -0.5,0.5,0.5 },//2
		{ -0.5,-0.5,0.5 },//3
		{ 0.5,-0.5,-0.5 },//4
		{ 0.5,0.5,-0.5 },//5
		{ -0.5,0.5,-0.5 },//6
		{ -0.5,-0.5,-0.5 },//7

	};
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//hinter
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//Rechts
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//links
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//unter
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//oben
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_POLYGON);//vorne
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glEnd();

}
void dodecaedro(GLuint textura1)
{
	GLfloat vertice[20][3] = {
		{ 0.0,0.0,0.0 }, //coordenada vertice0
		{ -2.3,0.0,-1.5 },//Coordenada vertice1
		{ -1.5,0.0,-4.0 },//Coordenada vertice2
		{ 1.5,0.0,-4.0 },//Coordenada vertice3
		{ 2.3,0.0,-1.5 }, //coordenada vertice4

		{ 0.0,2.5,1.5 },//Coordenada vertice5
		{ -3.9,2.5,-1.15 },//Coordenada vertice6
		{ -2.5,2.5,-5.15 },//Coordenada vertice7
		{ 2.5,2.5,-5.15 }, //coordenada vertice8
		{ 3.9,2.5,-1.15 },//Coordenada vertice9
		{ -2.15,4.0,0.7 },//Coordenada vertice10
		{ -3.5,4.0,-3.15 },//Coordenada vertice11
		{ 0.0,4.0,-5.75 },//Coordenada vertice12
		{ 3.5,4.0,-3.15 }, //coordenada vertice13
		{ 2.15,4.0,0.7 },//Coordenada vertice14
		{ -1.5,6.5,0.0 },//Coordenada vertice15
		{ -2.3,6.5,-2.5 },//Coordenada vertice16
		{ 0.0,6.5,-4.0 },//Coordenada vertice17
		{ 2.3,6.6,-2.5 }, //coordenada vertice18
		{ 1.5,6.5,0.0 },//Coordenada vertice19

	};
	glBindTexture(GL_TEXTURE_2D, textura1);
	//	glEnable(GL_DEPTH_TEST);//--------------------------CAMBIO

	glBegin(GL_POLYGON);	//numero1
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.2656f, 0.24218f); glVertex3fv(vertice[0]);//punta
	glTexCoord2f(0.1640f, 0.3710f); glVertex3fv(vertice[1]);//iaba
	glTexCoord2f(0.1992f, 0.6093f); glVertex3fv(vertice[2]);//iarr
	glTexCoord2f(0.3203f, 0.6093f); glVertex3fv(vertice[3]);//darr
	glTexCoord2f(0.3632f, 0.3828f); glVertex3fv(vertice[4]);//daba
	glEnd();
	//glDisable(GL_DEPTH_TEST);//---------------------------------------CAMBIO

	glBegin(GL_POLYGON);	//numero2
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.1640f, 0.3710f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.2656f, 0.2382f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.2265f, 0.0117f); glVertex3fv(vertice[9]);
	glTexCoord2f(0.1054f, 0.0117f); glVertex3fv(vertice[14]);
	glTexCoord2f(0.0664f, 0.2304f); glVertex3fv(vertice[5]);
	glEnd();
	glBegin(GL_POLYGON);	//numero3
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.1015f, 0.7343f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.1992f, 0.6093f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.1640f, 0.3710f); glVertex3fv(vertice[8]);
	glTexCoord2f(0.0429f, 0.3710f); glVertex3fv(vertice[13]);
	glTexCoord2f(0.0f, 0.5976f); glVertex3fv(vertice[9]);
	glEnd();
	glBegin(GL_POLYGON);	//numero4
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.2617f, 0.9726f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.3554f, 0.8398f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.3203f, 0.6093f); glVertex3fv(vertice[12]);
	glTexCoord2f(0.2031f, 0.6093f); glVertex3fv(vertice[8]);
	glTexCoord2f(0.1640f, 0.8281f); glVertex3fv(vertice[3]);
	glEnd();
	glBegin(GL_POLYGON);	//numero5
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.4257f, 0.7460f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.5195f, 0.6093f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.4804f, 0.3867f); glVertex3fv(vertice[11]);
	glTexCoord2f(0.3632f, 0.3867f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.3203f, 0.6093f); glVertex3fv(vertice[2]);
	glEnd();
	glBegin(GL_POLYGON);	//numero6
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.3632f, 0.375f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.4609f, 0.2382f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.4218f, 0.0117f); glVertex3fv(vertice[10]);
	glTexCoord2f(0.3007f, 0.0117f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.2656f, 0.2382f); glVertex3fv(vertice[1]);
	glEnd();
	glBegin(GL_POLYGON);	//numero7
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.7382f, 0.7578f); glVertex3fv(vertice[15]);
	glTexCoord2f(0.8359f, 0.6289f); glVertex3fv(vertice[16]);
	glTexCoord2f(0.8007f, 0.3945f); glVertex3fv(vertice[17]);
	glTexCoord2f(0.6796f, 0.3945f); glVertex3fv(vertice[18]);
	glTexCoord2f(0.6404f, 0.6132f); glVertex3fv(vertice[19]);
	glEnd();
	glBegin(GL_POLYGON); //numero9
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.6406f, 0.6210f); glVertex3fv(vertice[10]);
	glTexCoord2f(0.5429f, 0.7578f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.5859f, 0.9804f); glVertex3fv(vertice[14]);
	glTexCoord2f(0.6992f, 0.9804f); glVertex3fv(vertice[19]);
	glTexCoord2f(0.7382f, 0.7617f); glVertex3fv(vertice[15]);
	glEnd();

	glBegin(GL_POLYGON);//numero8
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.5820f, 0.2460f); glVertex3fv(vertice[14]);
	glTexCoord2f(0.4882f, 0.3789f); glVertex3fv(vertice[9]);
	glTexCoord2f(0.5195f, 0.6132f); glVertex3fv(vertice[13]);
	glTexCoord2f(0.6406f, 0.6132f); glVertex3fv(vertice[18]);
	glTexCoord2f(0.6757f, 0.3867f); glVertex3fv(vertice[19]);
	glEnd();

	glBegin(GL_POLYGON);//12
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.7421f, 0.0195f); glVertex3fv(vertice[12]);
	glTexCoord2f(0.6445f, 0.1640f); glVertex3fv(vertice[17]);
	glTexCoord2f(0.6796f, 0.3945f); glVertex3fv(vertice[18]);
	glTexCoord2f(0.8007f, 0.3945f); glVertex3fv(vertice[13]);
	glTexCoord2f(0.8398f, 0.1679f); glVertex3fv(vertice[8]);
	glEnd();
	glBegin(GL_POLYGON);//numero11
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.9023f, 0.2578f); glVertex3fv(vertice[12]);
	glTexCoord2f(0.8007f, 0.3945f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.8398f, 0.6210f); glVertex3fv(vertice[11]);
	glTexCoord2f(0.9570f, 0.6210f); glVertex3fv(vertice[16]);
	glTexCoord2f(1.0f, 0.3906f); glVertex3fv(vertice[17]);
	glEnd();
	glBegin(GL_POLYGON);//numero10
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.8399f, 0.6289f); glVertex3fv(vertice[11]);
	glTexCoord2f(0.7382f, 0.7617f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.7812f, 0.9882f); glVertex3fv(vertice[10]);
	glTexCoord2f(0.8984f, 0.9882f); glVertex3fv(vertice[15]);
	glTexCoord2f(0.9335f, 0.7617f); glVertex3fv(vertice[16]);
	glEnd();
}
void juego_mesa(float ancho, float largo, float alto, GLuint textura_1, GLuint textura_2)
{
	GLfloat vertice[8][3] = {
		{ 0.5*largo ,-0.5*alto ,0.5*ancho },
		{ 0.5*largo ,0.5*alto ,0.5*ancho },
		{ -0.5*largo ,0.5*alto ,0.5*ancho },
		{ -0.5*largo ,-0.5*alto ,0.5*ancho },
		{ 0.5*largo ,-0.5*alto ,-0.5*ancho },
		{ 0.5*largo ,0.5*alto ,-0.5*ancho },
		{ -0.5*largo ,0.5*alto ,-0.5*ancho },
		{ -0.5*largo ,-0.5*alto,-0.5*ancho },
	};

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(.0f, 0.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_2);
	glBegin(GL_POLYGON);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_2);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_2);
	glBegin(GL_POLYGON);
	
	glTexCoord2f(0.0f, 0.0f);		glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_2);
	glBegin(GL_POLYGON);
	
	glTexCoord2f(0.0f, 0.0f);		glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[3]);
	glEnd();

}
//mesa part
void Mesa() {

	glPushMatrix();
		glTranslated(0,0,0);
		glPushMatrix();
			//mesa PART B
			
			glPushMatrix();
			glTranslatef(1.1, -0.2, -1.1);
				glPushMatrix();
					glScalef(2, 0.2, 2);
					glDisable(GL_LIGHTING);
					cubo2(tex_mesa1.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				//B1
			
				glPushMatrix();
					glTranslatef(-0.9, -2.1, 0);
					glPushMatrix();
						glScalef(0.2, 4, 2);
						glDisable(GL_LIGHTING);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
						glPopMatrix();
				glPopMatrix();

				//B2

				glPushMatrix();
					glTranslatef(0, -2.1, 0.9);
					glPushMatrix();
						glDisable(GL_LIGHTING);
						glScalef(2, 4, 0.2);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();
			
			glPopMatrix();

			//mesa PART C
			
			glPushMatrix();
			glTranslatef(1.1, -0.2, 1.1);
				glPushMatrix();
					glScalef(2, 0.2, 2);
					glDisable(GL_LIGHTING);
					cubo2(tex_mesa1.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				//C1

				glPushMatrix();
					glTranslatef(-0.9, -2.1, 0);
					glPushMatrix();
						glScalef(0.2, 4, 2);
						glDisable(GL_LIGHTING);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();

				//C2

				glPushMatrix();
					glTranslatef(0, -2.1, -0.9);
					glPushMatrix();
						glDisable(GL_LIGHTING);
						glScalef(2, 4, 0.2);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();

			//mesa PART D
			
			glPushMatrix();
				glTranslatef(-1.1, -0.2, 1.1);
				glPushMatrix();
					glScalef(2, 0.2, 2);
					glDisable(GL_LIGHTING);
					cubo2(tex_mesa1.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				//D1

				glPushMatrix();
					glTranslatef(0.9, -2.1, 0);
					glPushMatrix();
						glScalef(0.2, 4, 2);
						glDisable(GL_LIGHTING);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();

				//D2

				glPushMatrix();
					glTranslatef(0, -2.1, -0.9);
					glPushMatrix();
						glDisable(GL_LIGHTING);
						glScalef(2, 4, 0.2);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();


			//mesa PART E

			glPushMatrix();
				glTranslatef(-1.1, -0.2, -1.1);
				glPushMatrix();
					glScalef(2, 0.2, 2);
					glDisable(GL_LIGHTING);
					cubo2(tex_mesa1.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				//E1

				glPushMatrix();
					glTranslatef(0.9, -2.1, 0);
					glPushMatrix();
						glScalef(0.2, 4, 2);
						glDisable(GL_LIGHTING);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();

				//E2

				glPushMatrix();
					glTranslatef(0, -2.1, 0.9);
					glPushMatrix();
						glDisable(GL_LIGHTING);
						glScalef(2, 4, 0.2);
						cubo2(tex_mesa2.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();

			//PART A
			glPushMatrix();
				glPushMatrix();
					glScalef(6.0,0.2,6.0);
					glDisable(GL_LIGHTING);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					cuboMesa(tex_mesa.GLindex);
					glDisable(GL_BLEND);
					glEnable(GL_LIGHTING);
				glPopMatrix();
			glPopMatrix();
		
		glPopMatrix();
	glPopMatrix();

}
void cilindro() {
	float t = 360, rad = 9, a, b, x, z;
	float ang = 360 / t;
	h =1;

	for (float i = 0; i < t; i++)
	{
		x = rad*cos(i*ang);
		z = rad*sin(i*ang);
		a = rad*cos((i + 1)*ang);
		b = rad*sin((i + 1)*ang);
		GLfloat vertice[4][3] = {
			{ x,0,z },
			{ a,h,b },
			{ x,h,z },
			{ a,0,b },
		};
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse10);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse13);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
		glEnd();
	}
}
void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos)
{

	float R = 0;
	float r = 0;

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };

	int i, j;

	GLdouble angulop = 2 * 3.1415 / paralelos;
	GLdouble angulom = 2 * 3.1415 / meridianos;

	r = (radioM - radiom) / 2;
	R = radiom + r;

	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{

			v1[0] = R*cos(angulom*i) + r*cos(angulom*i)*cos(angulop*j);
			v1[2] = R*sin(angulom*i) + r*sin(angulom*i)*cos(angulop*j);
			v1[1] = r*sin(angulop*j);

			glNormal3f(v1[0], v1[1], v1[2]);

			v2[0] = R*cos(angulom*i) + r*cos(angulom*i)*cos(angulop*(j + 1));
			v2[2] = R*sin(angulom*i) + r*sin(angulom*i)*cos(angulop*(j + 1));
			v2[1] = r*sin(angulop*(j + 1));

			glNormal3f(v2[0], v2[1], v2[2]);

			v3[0] = R*cos(angulom*(i + 1)) + r*cos(angulom*(i + 1))*cos(angulop*(j + 1));
			v3[2] = R*sin(angulom*(i + 1)) + r*sin(angulom*(i + 1))*cos(angulop*(j + 1));
			v3[1] = r*sin(angulop*(j + 1));

			glNormal3f(v3[0], v3[1], v3[2]);

			v4[0] = R*cos(angulom*(i + 1)) + r*cos(angulom*(i + 1))*cos(angulop*j);
			v4[2] = R*sin(angulom*(i + 1)) + r*sin(angulom*(i + 1))*cos(angulop*j);
			v4[1] = r*sin(angulop*j);

			glNormal3f(v4[0], v4[1], v4[2]);

			glBegin(GL_POLYGON);
			glVertex3fv(v1);
			glVertex3fv(v2);
			glVertex3fv(v3);
			glVertex3fv(v4);
			glEnd();
		}
	}
}
void cilindro(float rad, float h) {
	float a, b, x, z;
	float t = 360;
	float ang = 360 / t;
	for (float i = 0; i < t; i++)
	{
		x = rad*cos(i*ang);
		z = rad*sin(i*ang);
		a = rad*cos((i + 1)*ang);
		b = rad*sin((i + 1)*ang);
		GLfloat vertice[4][3] = {
			{ x,0,z },
			{ a,h,b },
			{ x,h,z },
			{ a,0,b },
		};
		glBegin(GL_POLYGON);
		//glColor3f(0.275, 0.510, 0.706);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
		glEnd();
	}
}
void circulo(GLfloat x, GLfloat y, GLfloat r) {
	int dib;
	int itera = 30;
	float pi = 3.1416;
	GLfloat pipi = 2.0f * pi;

	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(0,0,1);
	glVertex2f(x, y);
	for (dib = 0; dib <= itera; dib++) {
		glVertex2f(
			x + (r*cos(dib*pipi / itera)),
			y + (r*sin(dib*pipi / itera))
		);
	}
	glEnd();
}
void esfera() {
	float Vertice1z, Vertice1x, Vertice1y, Vertice2z, Vertice2x, Vertice2y, Vertice3z, Vertice3x, Vertice3y, Vertice4z, Vertice4x, Vertice4y;
	float resol = 20,rad =0.37;
	float incRad = PI / resol;
	float phi = 0, teta = 0;
	
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
			
			glVertex3f(Vertice1x, Vertice1y, Vertice1z);
			
			glVertex3f(Vertice2x, Vertice2y, Vertice2z);
			
			glVertex3f(Vertice3x, Vertice3y, Vertice3z);
			//TRIANGULO2
			//glColor3f(0.184, 0.310, 0.310);
			
			glVertex3f(Vertice1x, Vertice1y, Vertice1z);
		
			glVertex3f(Vertice3x, Vertice3y, Vertice3z);
			
			glVertex3f(Vertice4x, Vertice4y, Vertice4z);
			glEnd();
		}
	}

}
void Tablero()
{

	double i, j,k=-0.9526, m = 0.9526;
	for (i = 0; i < 12; i++)
	{

		for (j = -0.55*i; j <= 0.55*i; j = j + 1.1)
		{
			glPointSize(50);
			glBegin(GL_LINE_LOOP);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse13);
			glNormal3f(0, 0, 1);  
			glVertex3f(j, k*i, 0);  
			glVertex3f(j + 0.55, (i + 1)*k, 0);
			glVertex3f(j - 0.55, (i + 1)*k, 0);
			glEnd();
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
			glTranslatef(0, 0, 0.1);
			circulo(j, k*i, 0.35);
			circulo(j + 0.55, (i + 1)*k, 0.35);
			circulo(j - 0.55, (i + 1)*k, 0.35);
			glPopMatrix();
			glBegin(GL_LINE_LOOP);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse13);
			glNormal3f(0, 0, 1);
			glVertex3f(j, (m*i) - 15.2416, 0);
			glVertex3f(j + 0.55, ((i + 1)*m) - 15.2416, 0);
			glVertex3f(j - 0.55, ((i + 1)*m) - 15.2416, 0);
			glEnd();
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
			glTranslatef(0, 0, 0.1);
			circulo(j, (m*i) - 15.2416, 0.35);
			circulo(j + 0.55, ((i + 1)*m) - 15.2416, 0.35);
			circulo(j - 0.55, ((i + 1)*m) - 15.2416, 0.35);
			glPopMatrix();
		}
	}
	//canicas
	k = -0.9526, m = 0.9526;
	for (i = 0; i < 3; i++)
	{
		for (j = -0.55*i; j <= 0.55*i; j = j + 1.1)
		{
			
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
			glTranslatef(j, k*i, 0);
			esfera();
			glPopMatrix();
			
			//links
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
			glTranslatef(j-5.5, k*(i+10), 0);
			esfera();
			glPopMatrix(); 
			//rechts
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
			glTranslatef(j + 5.5, k*(i + 10), 0);
			esfera();
			glPopMatrix();

			//spiegel
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
			glTranslatef(j, (m*i) - 15.2416, 0.0);
			esfera();
			glPopMatrix();

			//links
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse6);
			glTranslatef(j-5.5, (m*(i+10)) - 15.2416, 0.0);
			esfera();
			glPopMatrix();
			//rechts
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse7);
			glTranslatef(j+5.5, (m*(i+10)) - 15.2416, 0.0);
			esfera();
			glPopMatrix();
		}
	}

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse11);
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(0,0,0);
	glVertex3f(-6.6,-11.4312,0);
	glVertex3f(6.6,-11.4312,0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(0, -15.2416, 0);
	glVertex3f(-6.6, -3.8104, 0);
	glVertex3f(6.6, -3.8104, 0);
	glEnd();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse10);
	glTranslated(0,0,-0.1);
	circulo(0,-7.6208,8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -7.6208, -0.4);
	glRotated(90, 1, 0, 0);
	glScaled(1,0.3,1);
	cilindro();
	glPopMatrix();


	
	
}
void plano(GLuint textura1, float ancho, float alto, float largo) {

	GLfloat vertice[4][3] = {
		{ 0.5*ancho,0.0,-0.5*largo },
		{ 0.5*ancho,0.0,0.5*largo },
		{ -0.5*ancho,0.0,0.5*largo },
		{ -0.5*ancho,0.0,-0.5*largo }
	};

	glBindTexture(GL_TEXTURE_2D, textura1);
	//	glEnable(GL_DEPTH_TEST);//--------------------------CAMBIO

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[3]);
	glEnd();



}
void barra_madera(float ancho, float largo, float alto, GLuint textura_1)
{
	GLfloat vertice[8][3] = {
		{ 0 * largo ,0 * alto ,0 * ancho },
		{ 1 * largo ,0 * alto ,0 * ancho },
		{ 8 * largo ,15 * alto ,0 * ancho },
		{ 9 * largo ,15 * alto ,0 * ancho },
		{ 0 * largo ,0 * alto ,1 * ancho },
		{ 1 * largo ,0 * alto ,1 * ancho },
		{ 8 * largo ,15 * alto ,1 * ancho },
		{ 9 * largo ,15 * alto ,1 * ancho },
	};

	glBindTexture(GL_TEXTURE_2D, textura_1);   // choose the texture to use.
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 0.6f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[2]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[6]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.00f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(0.5f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[2]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[1]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[5]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[5]);
	glEnd();

}
void cubo(float ancho, float largo, float alto, GLuint textura_1)
{
	GLfloat vertice[8][3] = {
		{ 0.5*largo ,-0.5*alto ,0.5*ancho },
		{ 0.5*largo ,0.5*alto ,0.5*ancho },
		{ -0.5*largo ,0.5*alto ,0.5*ancho },
		{ -0.5*largo ,-0.5*alto ,0.5*ancho },
		{ 0.5*largo ,-0.5*alto ,-0.5*ancho },
		{ 0.5*largo ,0.5*alto ,-0.5*ancho },
		{ -0.5*largo ,0.5*alto ,-0.5*ancho },
		{ -0.5*largo ,-0.5*alto,-0.5*ancho },
	};

	glBindTexture(GL_TEXTURE_2D, textura_1);   // choose the texture to use.
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 0.6f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[7]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.00f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(0.5f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura_1);
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f);	glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f);	glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f);	glVertex3fv(vertice[3]);
	glEnd();

}
void cubo1(float ancho, float largo, float alto)
{
	GLfloat vertice[8][3] = {
		{ 0.5*ancho,-0.5*largo,0.5*alto },
		{ 0.5*ancho,0.5*largo,0.5*alto },
		{ -0.5*ancho,0.5*largo,0.5*alto },
		{ -0.5*ancho,-0.5*largo,0.5*alto },
		{ 0.5*ancho,-0.5*largo,-0.5*alto },
		{ 0.5*ancho,0.5*largo,-0.5*alto },
		{ -0.5*ancho,0.5*largo,-0.5*alto },
		{ -0.5*ancho,-0.5*largo,-0.5*alto },

	};

	glBegin(GL_POLYGON);
	//glColor3f(0.275, 0.510, 0.706);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.482, 0.408, 0.933);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.737, 0.5613, 0.561);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.412, 0.412, 0.412);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.184, 0.310, 0.310);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.000, 0.502, 0.502);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

}
void silla_1() {
	glPushMatrix();
		glTranslatef(0, 0, -3);
		glDisable(GL_LIGHTING);
		barra_madera(0.3, 0.3, 0.3, t_silla1.GLindex);
		glTranslatef(0, 0, -1.75);
		barra_madera(0.3, 0.3, 0.3, t_silla1.GLindex);
		glTranslatef(2.5, 0, 1.75);
		glRotatef(180, 0, 1, 0);
		glRotatef(20, 0, 0, 1);
		barra_madera(0.2, 0.2, 0.2, t_silla1.GLindex);
		glTranslatef(0, 0, 1.21);
		barra_madera(0.2, 0.2, 0.2, t_silla1.GLindex);
	glPopMatrix();
		glTranslatef(0.65, 1, -3.75);
		cubo(1.5, 0.09, 0.09, t_silla1.GLindex);
		glTranslatef(1.75, -0.2, 0);
		cubo(1.3, 0.09, 0.09, t_silla1.GLindex);
		glTranslatef(-0.15, 0.4, 0);
		cubo(1.3, 0.09, 0.09, t_silla1.GLindex);
		glTranslatef(-0.175, 1, 0);
		cubo(1.3, 0.09, 0.09, t_silla1.GLindex);
		glTranslatef(-0.8, 0, 0);
		cubo(1.3, 0.09, 0.09, t_silla1.GLindex);
		glTranslatef(0.1, 0.05, 0);
		plano(t_asiento.GLindex, 2, 1000, 1.5);
		glTranslatef(0, 2, 0.03);
		glTranslatef(0.635, -0.5, 0);
		glRotatef(60, 0, 0, 1);
		plano(t_asiento.GLindex, 1.25, 1000, 1.45);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void silla_2() {
	glPushMatrix();
		glDisable(GL_LIGHTING);
		cubo(1.5, 2, 0.2, t_estante.GLindex);
		glTranslatef(0.85, -1.2, 0.6);
		cubo(0.2, 0.2, 2.5, t_estante.GLindex);
		glTranslatef(-1.75, 0, 0);
		cubo(0.2, 0.2, 2.5, t_estante.GLindex);
		glTranslatef(0, 0, -1.18);
		cubo(0.2, 0.2, 2.5, t_estante.GLindex);
		glTranslatef(1.75, 0, 0);
		cubo(0.2, 0.2, 2.5, t_estante.GLindex);
		glTranslatef(-0.85, 1.31, 0.55);
		plano(t_asiento2.GLindex, 1.75, 2000, 1.25);
		glTranslatef(1.15, 1.5, 0.03);
		glRotatef(-10, 0, 0, 1);
		cubo(1.45, 0.2, 3.25, t_asiento2.GLindex);
		glEnable(GL_LIGHTING);
		
	glPopMatrix();
}

void silla3() {
	glPushMatrix();//respaldo
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_am_silla3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_di_silla3);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_espec_silla3);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslated(0, 0, 3);
	glPushMatrix();//asiento
	glTranslated(0, -1.25, 0.75);
	glPushMatrix();//cilidro
	glTranslated(0, -2, 0);
	cilindro(0.5, 2);
	glPopMatrix();//fincilindro
	glPushMatrix();//base
	glColor3f(1, 0, 0);
	glTranslated(0, -2, 0);
	glScaled(0.5, 0.3, 0.5);
	torus(2, 0.5, 50, 50);
	glPopMatrix();//finbase
	cubo1(2, 0.5, 2);
	glPopMatrix();//finasiento
	cubo1(2, 2, 0.5);
	glPopMatrix();//finrespaldo
}

void silla4() {
	glPushMatrix();//respaldo
	glTranslated(3, 0, 3);
	glPushMatrix();//asiento
	glTranslated(0, -1.25, 0.75);
	glPushMatrix();//p1
	glTranslated(-0.75, -2, 0.75);
	cilindro(0.2, 2);
	glPopMatrix();//finp1

	glPushMatrix();//p2
	glTranslated(0.85, -1.9, 0.75);
	glRotated(90, 0, 0, 1);
	cilindro(0.2, 1.7);
	glPopMatrix();//finp2

	glPushMatrix();//p3
	glTranslated(0.75, -2, 0.75);
	cilindro(0.2, 2);
	glPopMatrix();//finp3

	glPushMatrix();//p4
	glTranslated(0.75, -1.9, -0.75);
	glRotated(90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	cilindro(0.2, 1.5);
	glPopMatrix();//finp4

	glPushMatrix();//p5
	glTranslated(-0.75, -1.9, -0.75);
	glRotated(90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	cilindro(0.2, 1.5);
	glPopMatrix();//finp5
	cubo1(2, 0.5, 2);
	glPopMatrix();//finasiento
	cubo1(2, 2, 0.5);
	glPopMatrix();//finrespaldo
}
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	

	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	tex_mesa.LoadTGA("Mesa/V_Tisch.tga");
	tex_mesa.BuildGLTexture();
	tex_mesa.ReleaseImage();

	tex_mesa1.LoadTGA("Mesa/V_Tisch1.tga");
	tex_mesa1.BuildGLTexture();
	tex_mesa1.ReleaseImage();

	tex_mesa2.LoadTGA("Mesa/V_Tisch2.tga");
	tex_mesa2.BuildGLTexture();
	tex_mesa2.ReleaseImage();
	///------------------
	t_octa.LoadTGA("octa.tga");
	t_octa.BuildGLTexture();
	t_octa.ReleaseImage();

	t_dodeca.LoadTGA("dodeca.tga");
	t_dodeca.BuildGLTexture();
	t_dodeca.ReleaseImage();

	t_piso.LoadTGA("piso.tga");
	t_piso.BuildGLTexture();
	t_piso.ReleaseImage();

	t_pared.LoadTGA("pared.tga");
	t_pared.BuildGLTexture();
	t_pared.ReleaseImage();

	t_pared1.LoadTGA("pared1.tga");
	t_pared1.BuildGLTexture();
	t_pared1.ReleaseImage();

	t_pared2.LoadTGA("pared2.tga");
	t_pared2.BuildGLTexture();
	t_pared2.ReleaseImage();

	t_pared3.LoadTGA("pared3.tga");
	t_pared3.BuildGLTexture();
	t_pared3.ReleaseImage();

	t_techo.LoadTGA("techo.tga");
	t_techo.BuildGLTexture();
	t_techo.ReleaseImage();

	t_fachada.LoadTGA("fachada.tga");
	t_fachada.BuildGLTexture();
	t_fachada.ReleaseImage();

	t_puerta.LoadTGA("puerta.tga");
	t_puerta.BuildGLTexture();
	t_puerta.ReleaseImage();

	t_ventana.LoadTGA("ventana.tga");
	t_ventana.BuildGLTexture();
	t_ventana.ReleaseImage();

	t_poster1.LoadTGA("poster1.tga");
	t_poster1.BuildGLTexture();
	t_poster1.ReleaseImage();

	t_poster2.LoadTGA("poster2.tga");
	t_poster2.BuildGLTexture();
	t_poster2.ReleaseImage();

	t_poster3.LoadTGA("poster3.tga");
	t_poster3.BuildGLTexture();
	t_poster3.ReleaseImage();

	t_estante.LoadTGA("estante.tga");
	t_estante.BuildGLTexture();
	t_estante.ReleaseImage();

	t_estante.LoadTGA("estante.tga");
	t_estante.BuildGLTexture();
	t_estante.ReleaseImage();


	t_jenga1.LoadTGA("jenga1.tga");
	t_jenga1.BuildGLTexture();
	t_jenga1.ReleaseImage();

	t_jenga2.LoadTGA("jenga2.tga");
	t_jenga2.BuildGLTexture();
	t_jenga2.ReleaseImage();

	t_scrabble1.LoadTGA("scrabble1.tga");
	t_scrabble1.BuildGLTexture();
	t_scrabble1.ReleaseImage();

	t_scrabble2.LoadTGA("scrabble2.tga");
	t_scrabble2.BuildGLTexture();
	t_scrabble2.ReleaseImage();

	t_monopoly1.LoadTGA("monopoly1.tga");
	t_monopoly1.BuildGLTexture();
	t_monopoly1.ReleaseImage();

	t_monopoly2.LoadTGA("monopoly2.tga");
	t_monopoly2.BuildGLTexture();
	t_monopoly2.ReleaseImage();

	t_asiento.LoadTGA("asiento.tga");
	t_asiento.BuildGLTexture();
	t_asiento.ReleaseImage();

	t_asiento2.LoadTGA("asiento2.tga");
	t_asiento2.BuildGLTexture();
	t_asiento2.ReleaseImage();

	t_silla1.LoadTGA("silla.tga");
	t_silla1.BuildGLTexture();
	t_silla1.ReleaseImage();

	t_silla2.LoadTGA("silla2.tga");
	t_silla2.BuildGLTexture();
	t_silla2.ReleaseImage();
	//modelos
	lampeHaup._3dsLoad("ra.3ds");
	pez1._3dsLoad("A.3ds");
	lampe1._3dsLoad("s.3ds");
	


	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();

		glRotatef(g_lookupdown, 1.0f, 0, 0);

		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


		glPushMatrix();
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0, 12.5, 0);
				fig1.skybox(t_pared1.GLindex, t_pared.GLindex, t_pared2.GLindex, t_pared3.GLindex, t_piso.GLindex,t_techo.GLindex);
				glEnable(GL_LIGHTING);

				//lampara 1
				glPushMatrix();
				glTranslated(-20.1, 8.5, 21);
				glScaled(0.1, 0.1, 0.1);
				lampe1.GLrender(NULL, _SHADED, 1.0);
				glPopMatrix();

				//lampe2
				glPushMatrix();
				glTranslated(0, 12.5, 0);
				glScaled(0.02, 0.02, 0.02);
				lampeHaup.GLrender(NULL, _SHADED, 1.0);
				glPopMatrix();

			glPopMatrix();
			//foco
			glPushMatrix();
			glTranslatef(0, 18, 0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseLampara);
			glScaled(1.6, 1.6, 1.6);
			esfera();
			glPopMatrix();
		//objetos
		glPushMatrix();

			glScaled(3, 3, 3);
			glTranslated(-22, -1, -5);
			glPushMatrix();
				glRotatef(180, 1, 0, 0);
				glScalef(3, 3, 3);
				glTranslatef(5.374, -2.31, -2);
				glDisable(GL_LIGHTING);
				juego_mesa(0.5, 0.25, 0.125, t_jenga1.GLindex, t_jenga2.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glRotatef(180, 1, 0, 0);
				glScalef(3, 3, 3);
				glTranslatef(5.374, -2.31, -2);
				glRotatef(180, 0, 0, 1);
				glRotatef(270, 1, 0, 0);
				glTranslatef(0.025, 0.4, -0.18);
				glDisable(GL_LIGHTING);
				juego_mesa(0.5, 0.3, 0.15, t_scrabble1.GLindex, t_scrabble2.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glRotatef(180, 1, 0, 0);
				glScalef(3, 3, 3);
				glTranslatef(5.374, -2.31, -2);
				glRotatef(180, 0, 0, 1);
				glRotatef(270, 1, 0, 0);
				glTranslatef(0.025, -0.4, -0.21);
				glDisable(GL_LIGHTING);
				juego_mesa(0.5, 0.3, 0.1, t_monopoly1.GLindex, t_monopoly2.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

		glPopMatrix();//fin_objetos


		//dado
		glPushMatrix();
			glScaled(.1, .1, .1);
			glTranslated(25, 93, -10);
			glRotated(rota, 0, 1, 0);
			glDisable(GL_LIGHTING);
			dodecaedro(t_dodeca.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		

		//mesa
		glPushMatrix();
			glScaled(2, 2, 2);
			glTranslated(0, 4.5, 0);
			Mesa();
			glTranslated(0, 0.2, 0);
			glRotated(90, -1, 0, 0);
			glScaled(0.16, 0.16, 0.2);
			Tablero();
		glPopMatrix();

		//sillas
		glPushMatrix();
			
			glPushMatrix();//push_silla1_silla2
				glScalef(2.5, 2.5, 2.5);
				glTranslatef(2, 0.2, -1);
				glRotated(90, 0, 1, 0);
				silla_1(); //Silla
				glScalef(2.5, 2.5, 2.5);
				glTranslatef(1.3, 2.5, -2);
				glRotated(90, 0, 1, 0);
				silla_2(); //Silla 2
			glPopMatrix();//fin_pop_silla1_silla_"

			glPushMatrix();
				glScaled(3, 3, 3);
				glTranslated(-5.5, 0, 9);
				glRotated(90, 0, 1, 0);
				glPushMatrix();//push_silla3
					glScalef(0.85, 0.85, 0.85);
					glTranslatef(4.7, 3.5, 8.5);
					glRotated(90, 0, 1, 0);
					silla3(); //silla3
				glPopMatrix();//popsilla_3

				glPushMatrix();
					glScalef(0.85, 0.85, 0.85);
					glTranslatef(4.7, 3.5, 7.5);
					glRotated(90, 0, 1, 0);
					silla4();//silla4
				glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//pez
			glPushMatrix();
			glTranslated(2, 3, -4);
			glScaled(54, 54, 54);
			pez1.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
			glPopMatrix();
	glColor3f(1,1,1);

	glPopMatrix();

	

	glutSwapBuffers();

}

void mov_dado() {
	rota += 5;
	glutPostRedisplay();
}
void animacion()
{
	


	

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
				KeyFrame[playIndex].movBrazoIzqInc = (KeyFrame[playIndex + 1].movBrazoIzq - KeyFrame[playIndex].movBrazoIzq) / i_max_steps;		//100 frames
				KeyFrame[playIndex].movBrazoIzq2Inc = (KeyFrame[playIndex + 1].movBrazoIzq2 - KeyFrame[playIndex].movBrazoIzq2) / i_max_steps;		//100 frames

				KeyFrame[playIndex].rotMusIzqInc = (KeyFrame[playIndex + 1].rotMusIzq - KeyFrame[playIndex].rotMusIzq) / i_max_steps;

				KeyFrame[playIndex].rotRodDerInc = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;		//100 frames
				KeyFrame[playIndex].rotMusDerInc = (KeyFrame[playIndex + 1].rotMusDer - KeyFrame[playIndex].rotMusDer) / i_max_steps;
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
			movBrazoIzq += KeyFrame[playIndex].movBrazoIzqInc;
			movBrazoIzq2 += KeyFrame[playIndex].movBrazoIzq2Inc;

			rotMusDer += KeyFrame[playIndex].rotMusDerInc;
			rotRodDer += KeyFrame[playIndex].rotMusDerInc;

			rotMusIzq += KeyFrame[playIndex].rotMusIzqInc;

			i_curr_steps++;
		}

	}

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'O':		//  
	case 'o':
		//g_fanimacion ^= true; //Activamos/desactivamos la animacíon
		//circuito = false;
		break;

	case 'i':		//  
	case 'I':
		//circuito ^= true; //Activamos/desactivamos la animacíon
		//g_fanimacion = false;
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex<MAX_FRAMES)
		{
			FILE *fp;
			fp = fopen("file.txt", "a");


			printf("frameindex %d\n", FrameIndex);

			KeyFrame[FrameIndex].posX = posX;
			KeyFrame[FrameIndex].posY = posY;
			KeyFrame[FrameIndex].posZ = posZ;

			KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
			KeyFrame[FrameIndex].giroMonito = giroMonito;
			KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;
			KeyFrame[FrameIndex].movBrazoIzq = movBrazoIzq;
			//KeyFrame[FrameIndex].movBrazoIzq2 = movBrazoIzq2;

			KeyFrame[FrameIndex].rotMusDer = rotMusDer;
			KeyFrame[FrameIndex].rotRodDer = rotRodDer;

			KeyFrame[FrameIndex].rotMusIzq = rotMusIzq;

			fprintf(fp, "KeyFrame[%d].posX = %f;\n", FrameIndex, posX);
			fprintf(fp, "KeyFrame[%d].posY = %f;\n", FrameIndex, posY);
			fprintf(fp, "KeyFrame[%d].posZ = %f;\n", FrameIndex, posZ);
			fprintf(fp, "KeyFrame[%d].giroMonito = %f;\n", FrameIndex, giroMonito);
			fprintf(fp, "KeyFrame[%d].movBrazoDer = %f;\n", FrameIndex, movBrazoDer);
			fprintf(fp, "KeyFrame[%d].movBrazoIzq = %f;\n", FrameIndex, movBrazoIzq);
			fprintf(fp, "KeyFrame[%d].rotMusDer = %f;\n", FrameIndex, rotMusDer);
			fprintf(fp, "KeyFrame[%d].rotRodDer = %f;\n", FrameIndex, rotRodDer);
			fprintf(fp, "KeyFrame[%d].rotMusIzq = %f;\n", FrameIndex, rotMusIzq);
			fprintf(fp, "KeyFrame[%d].rotRodIzq = %f;\n", FrameIndex, rotRodIzq);
			fprintf(fp, "\n");

			fclose(fp);
			FrameIndex++;
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex>1))
		{
			posX = KeyFrame[0].posX;
			posY = KeyFrame[0].posY;
			posZ = KeyFrame[0].posZ;
			rotRodIzq = KeyFrame[0].rotRodIzq;
			giroMonito = KeyFrame[0].giroMonito;
			movBrazoDer = KeyFrame[0].movBrazoDer;
			movBrazoIzq = KeyFrame[0].movBrazoIzq;
			movBrazoIzq2 = KeyFrame[0].movBrazoIzq2;

			rotMusDer = KeyFrame[0].rotMusDer;
			rotRodDer = KeyFrame[0].rotRodDer;

			rotMusIzq = KeyFrame[0].rotMusIzq;

			//First Interpolation
			KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;		//100 frames
			KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;		//100 frames
			KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;		//100 frames
			KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;		//100 frames
			KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;		//100 frames
			KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;		//100 frames
			KeyFrame[playIndex].movBrazoIzqInc = (KeyFrame[playIndex + 1].movBrazoIzq - KeyFrame[playIndex].movBrazoIzq) / i_max_steps;		//100 frames
			KeyFrame[playIndex].movBrazoIzq2Inc = (KeyFrame[playIndex + 1].movBrazoIzq2 - KeyFrame[playIndex].movBrazoIzq2) / i_max_steps;		//100 frames

			KeyFrame[playIndex].rotMusDerInc = (KeyFrame[playIndex + 1].rotMusDer - KeyFrame[playIndex].rotMusDer) / i_max_steps;		//100 frames
			KeyFrame[playIndex].rotRodDerInc = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;		//100 frames

			KeyFrame[playIndex].rotMusIzqInc = (KeyFrame[playIndex + 1].rotMusIzq - KeyFrame[playIndex].rotMusIzq) / i_max_steps;		//100 frames

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
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

	case 'U':
	case 'u':
		posZ--;
		//printf("%f \n", posZ);
		break;

	case 'H':
	case 'h':
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


	case '1':
		movBrazoIzq++;
		break;
	case '2':
		movBrazoIzq--;
		break;
	
	case '4':
		movBrazoDer++;
		break;
	case '5':
		movBrazoDer--;
		break;

	case 'z':
		rotMusDer++;
		break;
	case 'Z':
		rotMusDer--;
		break;
	case 'x':
		rotRodDer++;
		break;
	case 'X':
		rotRodDer--;
		break;
	case 'v':
		rotMusIzq++;
		break;
	case 'V':
		rotMusIzq--;
		break;


	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
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
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 11"); // Nombre de la Ventana
									 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutIdleFunc(mov_dado);
	glutMainLoop();          // 

	return 0;
}