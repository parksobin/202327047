#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread> //sleep 이라는 함수 (잠깐 아무것도 안 하는 거)

using namespace std;
float m = 0.0f;
float j = 0.0f;

int speed2 = 3;
float g = 9.8f;
float a;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		//speed += 0.1f;
		
		a = 1;
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

	// +0.1
	//x = 0.0 y= -0.1
	//x = 0.2 y=-0.1
	//x = 0.2 y=0.1
	//x = 0.0 y=0.1

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
float power = 0.03f;
float speed = 0.04f;
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
		//j += 0.05f;

		if(a==1) //점프신호
		{
			j += 0.05f+ speed;
			if(j >= 0.4f)
			{
				a = 2;
			}
		}
		if (a==2) //떨어지는 신호
		{
			j -= 0.05f- speed;
			if (j <= 0.01)
			{
				a = 0;
			}
		}
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}