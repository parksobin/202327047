#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread> 

using namespace std;
float m = 0;
float j = 0;
float speed = 0;
float gravity = 0;

int a; 
bool jumpsign = true;
float plusx = 0.4f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (jumpsign)
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
		{
			 speed = 0.03f; gravity = 0.000098f;  a = 1;
		}
	}
}

void DrawGround()
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex2f(1, -0.05);
	glVertex2f(-1, -0.05);

	glEnd();
}

void DrawBox(float x, float y, float jumo)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-x- plusx, -y+ jumo);
	glVertex2f(x - plusx, -y+ jumo);

	glVertex2f(x - plusx, -y+ jumo);
	glVertex2f(x - plusx, y+ jumo);

	glVertex2f(x - plusx, y+ jumo);
	glVertex2f(-x - plusx, y+ jumo);

	glVertex2f(-x - plusx, -y+ jumo);
	glVertex2f(-x - plusx, y+ jumo);
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
	chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	int delay_time_ms = 0;

	while (!glfwWindowShouldClose(window))
	{
		this_thread::sleep_for(chrono::milliseconds(10 + delay_time_ms));
		prev_end = end;
		end = chrono::steady_clock::now();
		chrono::steady_clock::duration diff = end - prev_end;
		delay_time_ms = 10 - chrono::duration_cast<chrono::milliseconds>(diff).count();

		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		DrawGround();
		switch (a)
		{
			case 0:
				j = 0; speed = 0; gravity = 0; 
				jumpsign = true;
				break;
			case 1:
				jumpsign = false;
				j += speed;
				if (j >= 0.5f) { a = 2;}
				break;
			case 2:
				speed += gravity;
				j -= speed;
				if (j<= 0) { a = 0; }
				break;
		}
		DrawBox(0.05f,0.05f, j);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}