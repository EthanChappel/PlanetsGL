#include <GL/glew.h>
#include <GL/freeglut.h>

//glm library
#include <glm/glm.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

glm::vec3 move(0.0f,0.0f, 30.0f);
glm::vec3 center(0.0f,0.0f,0.0f);
Shader shader; // loads our vertex and fragment shaders
Model *sphere; //a sphere

glm::mat4 projection; // projection matrix
glm::mat4 view; // where the camera is looking

glm::mat4 sunTrans, mercuryTrans, venusTrans, earthTrans, moonTrans, marsTrans;
glm::mat4 jupTrans, ioTrans, eurTrans, ganTrans, calTrans;
glm::mat4 satTrans, mimasTrans, enceladusTrans, tethysTrans, dioneTrans, rheaTrans, titanTrans, iapetusTrans;
glm::mat4 uraTrans, mirandaTrans, arielTrans, umbrielTrans, titaniaTrans, oberonTrans;
glm::mat4 nepTrans, tritonTrans;

float sunAngle = 0, mercuryAngle = 0, venusAngle = 90, earthAngle = 180, moonAngle = 0, marsAngle = 270;
float jupAngle = 180, ioAngle = 0, eurAngle = 0, ganAngle = 90, calAngle = 0;
float satAngle = 0, mimasAngle = 0, enceladusAngle = 0, tethysAngle = 0, dioneAngle = 0, rheaAngle = 0, titanAngle = 0, iapetusAngle = 0;
float uraAngle = 0, mirandaAngle = 90, arielAngle = 90, umbrielAngle = 90, titaniaAngle = 90, oberonAngle = 90;
float nepAngle = 90, tritonAngle = 0;

glm::vec4 lightPosition = glm::vec4(0.0f, 100.0f, 0.0f, 100.0f);

/* report GL errors, if any, to stderr */
void checkError(const char *functionName)
{
	GLenum error;
	while (( error = glGetError() ) != GL_NO_ERROR) {
		std::cerr << "GL error " << error << " detected in " << functionName << std::endl;
	}
}

void initShader(void)
{
	shader.InitializeFromFile("shaders/phong.vert", "shaders/phong.frag");
	shader.AddAttribute("vertexPosition");
	shader.AddAttribute("vertexNormal");

	checkError ("initShader");
}

void initRendering(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f); // Dodger Blue
	checkError ("initRendering");
}

void init(void) 
{	
	// Perspective projection matrix.
	projection = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 1000.0f);

	
	// Load identity matrix into model matrix (no initial translation or rotation)
	

	initShader ();
	initRendering ();
}

/* This prints in the console when you start the program*/
void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
	checkError ("dumpInfo");
}

/*This gets called when the OpenGL is asked to display. This is where all the main rendering calls go*/
void display(void)
{

	// The transformation heirarchy is sun -> jupiter -> cube
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer data from the last frame

	shader.Activate();
	//draw the light!
	shader.SetUniform("surfaceEmissive", glm::vec4(1.0, 1.0, 1.0, 1.0));

	view = glm::lookAt(move, center, glm::vec3(0.0f, 1.0f, 0.0f));

	sunTrans = glm::scale(0.8f, 0.8f, 0.8f);
	sphere->render(view * sunTrans * glm::rotate(sunAngle += 0.2f, 0.0f, 1.0f, 0.0f), projection); // Render the sun

	// Does not work at the moment.
	shader.Activate(); // Bind shader.
	shader.SetUniform("lightPosition", view * lightPosition);
	shader.SetUniform("lightDiffuse", glm::vec4(1.0, 1.0, 1.0, 1.0));
	shader.SetUniform("lightSpecular", glm::vec4(1.0, 1.0, 1.0, 1.0));
	shader.SetUniform("lightAmbient", glm::vec4(0.4, 0.0, 0.0, 1.0));

	shader.SetUniform("surfaceDiffuse", glm::vec4(1.0, 0.0, 0.0, 1.0));
	shader.SetUniform("surfaceSpecular", glm::vec4(1.0, 1.0, 1.0, 1.0));
	shader.SetUniform("surfaceAmbient", glm::vec4(1.0, 0.0, 0.0, 1.0));
	shader.SetUniform("shininess", 20.0f);
	shader.SetUniform("surfaceEmissive", glm::vec4(0.0, 0.0, 0.0, 1.0));

	mercuryTrans = sunTrans * glm::rotate(mercuryAngle += 0.15f, 0.0f, 1.0f, 0.0f) * glm::translate(2.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::rotate(25.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * mercuryTrans, projection);

	venusTrans = sunTrans * glm::rotate(venusAngle += 0.09f, 0.0f, 1.0f, 0.0f) * glm::translate(2.67f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::scale(0.3f, 0.3f, 0.3f) * glm::rotate(25.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * venusTrans, projection);
	
	earthTrans = sunTrans * glm::rotate(earthAngle += 0.09f, 0.0f, 1.0f, 0.0f) * glm::translate(4.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::scale(0.3f, 0.3f, 0.3f) * glm::rotate(25.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * earthTrans, projection);

	moonTrans = earthTrans * glm::rotate(-18.0f, 1.0f, 0.0f, 0.0f) * glm::rotate(moonAngle += 0.18f, 0.0f, 1.0f, 0.0f) * glm::translate(8.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::scale(1.1f, 1.1f, 1.1f) * glm::rotate(5.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * moonTrans, projection);
	
	marsTrans = sunTrans * glm::rotate(marsAngle += 0.04f, 0.0f, 1.0f, 0.0f) * glm::translate(6.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::scale(0.15f, 0.15f, 0.15f) * glm::rotate(25.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * marsTrans, projection);

	jupTrans = sunTrans * glm::rotate(jupAngle += 0.02f, 0.0f, 1.0f, 0.0f)  * glm::translate(10.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::scale(1.0f, 0.94f, 1.0f) * glm::rotate(3.1f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * jupTrans, projection);

	ioTrans = jupTrans * glm::rotate(ioAngle += 0.2f, 0.0f, 1.0f, 0.0f) * glm::translate(5.0f, 0.0f, 0.0f) * glm::scale(0.08f, 0.08f, 0.08f);
	sphere->render(view * ioTrans, projection);
	
	eurTrans = jupTrans * glm::rotate(eurAngle += 0.1f, 0.0f, 1.0f, 0.0f) * glm::translate(7.5f, 0.0f, 0.0f) * glm::scale(0.07f, 0.07f, 0.07f);
	sphere->render(view * eurTrans, projection);

	ganTrans = jupTrans * glm::rotate(ganAngle += 0.05f, 0.0f, 1.0f, 0.0f) * glm::translate(11.25f, 0.0f, 0.0f) * glm::scale(0.12f, 0.12f, 0.12f);
	sphere->render(view * ganTrans, projection);

	calTrans = jupTrans * glm::rotate(calAngle += 0.0173f, 0.0f, 1.0f, 0.0f) * glm::translate(18.0f, 0.0f, 0.0f) * glm::scale(0.11f, 0.11f, 0.11f);
	sphere->render(view * calTrans, projection);

	satTrans = sunTrans * glm::rotate(satAngle += 0.008f, 0.0f, 1.0f, 0.0f) * glm::translate(20.0f, 0.0f, 0.0f) * glm::scale(0.085f, 0.085f, 0.085f) * glm::scale(1.0f, 0.9f, 1.0f) * glm::rotate(25.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * satTrans, projection);

	mimasTrans = satTrans * glm::rotate(mimasAngle += 0.15f, 0.0f, 1.0f, 0.0f) * glm::translate(6.0f, 0.0f, 0.0f) * glm::scale(0.03f, 0.03f, 0.03f);
	sphere->render(view * mimasTrans, projection);

	enceladusTrans = satTrans * glm::rotate(enceladusAngle += 0.12f, 0.0f, 1.0f, 0.0f) * glm::translate(8.0f, 0.0f, 0.0f) * glm::scale(0.035f, 0.035f, 0.035f);
	sphere->render(view * enceladusTrans, projection);

	tethysTrans = satTrans * glm::rotate(tethysAngle += 0.09f, 0.0f, 1.0f, 0.0f) * glm::translate(10.0f, 0.0f, 0.0f) * glm::scale(0.05f, 0.05f, 0.05f);
	sphere->render(view * tethysTrans, projection);

	dioneTrans = satTrans * glm::rotate(dioneAngle += 0.06f, 0.0f, 1.0f, 0.0f) * glm::translate(16.0f, 0.0f, 0.0f) * glm::scale(0.05f, 0.05f, 0.05f);
	sphere->render(view * dioneTrans, projection);

	rheaTrans = satTrans * glm::rotate(rheaAngle += 0.03f, 0.0f, 1.0f, 0.0f) * glm::translate(20.0f, 0.0f, 0.0f) * glm::scale(0.06f, 0.06f, 0.06f);
	sphere->render(view * rheaTrans, projection);

	titanTrans = satTrans * glm::rotate(titanAngle += 0.01f, 0.0f, 1.0f, 0.0f) * glm::translate(30.0f, 0.0f, 0.0f) * glm::scale(0.11f, 0.11f, 0.11f);
	sphere->render(view * titanTrans, projection);

	iapetusTrans = satTrans * glm::rotate(-8.0f, 1.0f, 0.0f, 0.0f) * glm::rotate(iapetusAngle += 0.003f, 0.0f, 1.0f, 0.0f) * glm::translate(90.0f, 0.0f, 0.0f) * glm::scale(0.06f, 0.06f, 0.06f);
	sphere->render(view * iapetusTrans, projection);

	uraTrans = sunTrans * glm::rotate(uraAngle += 0.002f, 0.0f, 1.0f, 0.0f) * glm::translate(40.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.096f, 0.1f)  * glm::rotate(98.0f, 1.0f, 0.0f, 1.0f);
	sphere->render(view * uraTrans, projection);

	mirandaTrans = uraTrans * glm::rotate(mirandaAngle += 0.2f, 0.0f, 1.0f, 0.0f) * glm::translate(4.0f, 0.0f, 0.0f) * glm::scale(0.05f, 0.05f, 0.05f);
	sphere->render(view * mirandaTrans, projection);

	arielTrans = uraTrans * glm::rotate(arielAngle += 0.13f, 0.0f, 1.0f, 0.0f) * glm::translate(7.0f, 0.0f, 0.0f) * glm::scale(0.06f, 0.06f, 0.06f);
	sphere->render(view * arielTrans, projection);

	umbrielTrans = uraTrans * glm::rotate(umbrielAngle += 0.056f, 0.0f, 1.0f, 0.0f) * glm::translate(10.0f, 0.0f, 0.0f) * glm::scale(0.06f, 0.06f, 0.06f);
	sphere->render(view * umbrielTrans, projection);

	titaniaTrans = uraTrans * glm::rotate(titaniaAngle += 0.0272f, 0.0f, 1.0f, 0.0f) * glm::translate(14.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f);
	sphere->render(view * titaniaTrans, projection);

	oberonTrans = uraTrans * glm::rotate(oberonAngle += 0.0135f, 0.0f, 1.0f, 0.0f) * glm::translate(18.0f, 0.0f, 0.0f) * glm::scale(0.09f, 0.09f, 0.09f);
	sphere->render(view * oberonTrans, projection);

	nepTrans = sunTrans * glm::rotate(nepAngle += 0.001f, 0.0f, 1.0f, 0.0f) * glm::translate(60.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::rotate(29.0f, 1.0f, 0.0f, 1.0f);;
	sphere->render(view * nepTrans, projection);

	tritonTrans = nepTrans * glm::rotate(tritonAngle -= 0.1f, 0.0f, 1.0f, 0.0f) * glm::translate(10.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f);
	sphere->render(view * tritonTrans, projection);

	shader.DeActivate(); // Unbind shader.
	
	glutSwapBuffers(); // Swap the buffers.
	checkError ("display");
}

/*This gets called when nothing is happening (OFTEN)*/
void idle()
{
	glutPostRedisplay(); // create a display event. Display calls as fast as CPU will allow when put in the idle function
}

/*Called when the window is resized*/
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	checkError ("reshape");
}

/*Called when a normal key is pressed*/
void keyboard(unsigned char key, int x, int y)
{
	glm::vec3 x1 = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), center - move));
	glm::vec3 y1 = glm::normalize(glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), center - move));
	glm::vec3 lookatdir = glm::normalize(center - move);
	switch (key) {
	case 27: // this is an ascii value
		exit(0);
		break;
	case 'w':
		// move forward
		move += lookatdir;
		center += lookatdir;
		break;

	case 's':
		// move back
		move -= lookatdir;
		center -= lookatdir;
		break;

	case 'a':
		// move left
		move += x1;
		center += x1;
		break;

	case 'd':
		// move right
		move = move - x1;
		center -= x1;
		break;

	case 'q':
		// turn left
		
		center = center + x1 * 0.5f;
		break;

	case 'e':
		// turn right
		center = center + x1 * -0.5f;
		break;
	case 'r':
		// move up
		move += y1;
		center += y1;
		break;
	case 'f':
		// move down
		move -= y1;
		center -= y1;
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (800, 600); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	glewInit();
	dumpInfo ();
	init ();
	glutDisplayFunc(display); 
	glutIdleFunc(idle); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc (keyboard);
	glEnable(GL_DEPTH_TEST);

	
	sphere = new Model(&shader, "models/sphere.obj");


	glutMainLoop();

	return 0;
}