#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread> 

using namespace std;
float m = 0.0f;
float j = 0.0f;
int a; 
float speed = 0.0f;
float gravity = 0.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
	{
		speed = 0.03f; gravity = 0.00098f;  a = 1;
		//  100        9.8
		// .0100     .00098
	}
}

void DrawGround()
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.9, -0.8);
	glVertex2f(0.9, -0.8);

	glVertex2f(0.9, -0.8);
	glVertex2f(0.9, -0.05);

	glVertex2f(0.9, -0.05);
	glVertex2f(-0.9, -0.05);

	glVertex2f(-0.9, -0.8);
	glVertex2f(-0.9, -0.05);

	glEnd();
}
void DrawBox(float x, float y, float m, float jumo)
{
	//x = 0.1 y=0.1
	//x = -0.1 y= -0.1
	//x = 0.1 y=-0.1
	//x = 0.1 y=0.1
	//x = -0.1 y=0.1
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-x+ m, -y+ jumo);
	glVertex2f(x+m, -y+ jumo);

	glVertex2f(x+ m, -y+ jumo);
	glVertex2f(x+ m, y+ jumo);

	glVertex2f(x+ m, y+ jumo);
	glVertex2f(-x+ m, y+ jumo);

	glVertex2f(-x+ m, -y+ jumo);
	glVertex2f(-x+ m, y+ jumo);
	glEnd();
}
int main(void)
{

	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1680, 960, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		DrawGround();
		this_thread::sleep_for(chrono::milliseconds(10));


		DrawBox(0.05f,0.05f,m, j);
		switch (a)
		{
			case 1:
				j += speed;
				if (j>= 0.9f) { a = 2; }
				break;
			case 2:
				speed += gravity;
				j -= speed;
				if (j<= 0) { a = 0; }
				break;
			default:
				j = 0; speed = 0; gravity = 0;
				break;
		}
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}