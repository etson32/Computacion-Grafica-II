/*
Universidad Nacional San Antonio Abad del Cusco
Ingenieria Informatica y de Sistemas
Computacion Grafica II
Nombre:	     Tarea_2.cpp
Proposito:   Si los puntos anteriores se rotan 30° con respecto al origen. 
             Obtenga la nueva curva.
Autor:	     Etson Ronaldao Rojas Cahuana
FCreacion:   14 / 06 / 2021
*/

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <math.h>
#include <iostream>
#define WIDTH 500 /* Ancho ventanas en pixels */
#define HEIGHT 500 /* Alto ventanas en pixels */

#define MAX_CPTS 100
GLfloat X0, X1, X2, Y0, Y1, Y2;
GLfloat cpts[MAX_CPTS][2];
GLint ncpts = MAX_CPTS;
GLint nroPtos;
//--puntos
glm::vec2 p0(0.0f, 0.0f);
glm::vec2 p1(3.0f, 8.0f);
glm::vec2 p2(3.0f, 3.0f);
//--coeficientes
glm::vec2 a(0.0, 0.0);
glm::vec2 b(0.0, 0.0);
glm::vec2 c(0.0, 0.0);
//--parámetro t
float t = 0.7;
void curvaParametrica()
{
	c = p0;
	a = (t * (p2 - p0) + (p0 - p1)) / (t * (1 - t));
	b = p2 - p0 - a;
	printf("a= %f, %f\n", a.x, a.y);
	printf("b= %f, %f\n", b.x, b.y);
	printf("c= %f, %f\n", c.x, c.y);
	//ROTAR LOS PUNTOS CALCULADOS PREVIAMENTE
	//---definición de los puntos a rotar
	glm::vec4 pto0(a.x, a.y, 0.0f, 1.0f);
	glm::vec4 pto1(b.x, b.y, 0.0f, 1.0f);
	glm::vec4 pto2(c.x, c.y, 0.0f, 1.0f);
	//--creamos la matriz identidad
	glm::mat4 matriz_ident = glm::mat4(1.0f);
	//--definimos la matriz de rotación
	glm::mat4 matriz_rotacion = glm::rotate(matriz_ident, glm::radians(30.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
	//--obtenemos los puntos rotados
	glm::vec4 pto0_rotado = matriz_rotacion * pto0;
	glm::vec4 pto1_rotado = matriz_rotacion * pto1;
	glm::vec4 pto2_rotado = matriz_rotacion * pto2;
	//--obtenemos coordenadas de los ptos rotados
	a.x = pto0_rotado.x;
	a.y = pto0_rotado.y;
	b.x = pto1_rotado.x;
	b.y = pto1_rotado.y;
	c.x = pto2_rotado.x;
	c.y = pto2_rotado.y;
	//--mostrar puntos rotados
	printf("Puntos rotados:\n");
	printf("%f, %f\n ", a.x, a.y);
	printf("%f, %f\n ", b.x, b.y);
	printf("%f, %f\n ", c.x, c.y);
	//--generar los puntos de la curva
	GLfloat t = 0.0;
	GLint i = 0;
	while (t <= 1.0)
	{
		//--función paramétrica
		cpts[i][0] = a.x * (t * t) + b.x * t + c.x;
		cpts[i][1] = a.y * (t * t) + b.y * t + c.y;
		//--imprimir los puntos
		printf("%f, %f\n ", cpts[i][0], cpts[i][1]);
		t = t + 0.02;
		i++;
	}
	nroPtos = i - 1;
	printf("nro de ptos:, %d\n", nroPtos);
	glPointSize(1.5);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= nroPtos; i++)
	{
		glVertex2f(cpts[i][0], cpts[i][1]);
	}
	glEnd();
}
/* Dibuja los ejes de referencia */
void ejes(void) {
	glBegin(GL_LINES);
	glVertex2i(0, -100); //--eje Y
	glVertex2i(0, 100);

	glVertex2i(-100, 0); //--eje X
	glVertex2i(100, 0);
	glEnd();
}

/* Render de la ventana */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0); //--color amarillo
	ejes(); //--dibuja los ejes
	//--traza curva original
	curvaParametrica();
	glutSwapBuffers();
}
void ini(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(7.0, 7.0, 0.0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Curva paramétrica cuadrática");
	glutDisplayFunc(display);
	ini();
	glutMainLoop();
	return 0;
}