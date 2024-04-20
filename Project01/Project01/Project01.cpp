#pragma comment(lib, "Opengl32.lib")﻿

//#include "stdafx.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "mObject.h"
#include "Mostar.h"

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

std::vector<Mostar*> list;

void errorCallback(int error, const char* description)
{
	std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}


int initialize()
{

	for (int i = 0; i < 1000; i++)
	{
		list[i] = new list();
	}
	return 0;
}
int release()
{
	for (int i = 0; i < 1000; i++)
	{
		delete(objects[i]);
	}
	return 0;
}

int update()
{
	for (int i = 0; i < 1000; i++)
	{
		objects[i]->Update();
	}
	return 0;
}

int render()
{
	glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return 0;
}

int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		render();
		glfwSwapBuffers(window);
	}

	release();

	glfwTerminate();
	return 0;

}


/*
* --------------------------------------------------------------------------------
#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;


void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "Position: (" << xpos << "," << ypos << ")";
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{

		}
		else if (action == GLFW_RELEASE)
		{
			
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			
		}
		else if (action == GLFW_RELEASE)
		{
			
		}
	}
}


void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	int leftButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

	if (leftButton == GLFW_PRESS)
	{
		// 왼쪽 버튼을 누르고 드래그 중이면 마젠타색으로 변경
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
}



int render()
{
    glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.0f, 0.5f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.15f, 0.0f);	
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.15f, 0.0f);	

	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.5f, 0.05f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.2f, 0.0f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.2f, -0.3f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.5f, 0.05f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.2f, 0.0f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.2f, -0.3f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.35f, -0.85f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.12f, 0.0f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.4f, 0.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.35f, -0.85f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.12f, 0.0f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.4f, 0.0f);
	
	/*
	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.0f, 0.5f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(-0.5f, 0.0f);
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(0.0f, -0.5f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);	
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glBegin(GL_TRIANGLES);

    glBegin(GL_POINT);
	//점1
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f * scaleFactor, (1.0f + moveFactor) * scaleFactor);
	//점2
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.5f * scaleFactor, (0.0f + moveFactor) * scaleFactor);
	//점3
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.5f * scaleFactor, (0.0f + moveFactor) * scaleFactor);
	glEnd();

	return 0;
}


int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}


* --------------------------------------------------------------------------------
* 
#pragma comment(lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
//#include <Window.h>
#include <iostream>


void errorcllback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}
void MyMouseClick(int key) {
    if ( key == GLFW_MOUSE_BUTTON_1) {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    }
}


int main()
{

    GLFWwindow* window;

    //glfwInit(); //glfw초기화
    if (!glfwInit())
    
        return -1;


    window = glfwCreateWindow(1280, 768, "HoHoHo HimNae", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetErrorCallback(errorcllback);
    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}
 */




/*  ------------------------------------------------------
    //3주차 수업
#include <iostream>

using namespace std;
int main()
{
    int num1;
    cout << "그림을 그릴 물체코드를 입력하세요" << endl;
    cin >> num1;

    cout << num1 % 4;

    //std string name;
    cout << "num을 18로 입력하지마세요" << endl;
    int num;
    string name;
    cin >> num; //cin 콘솔 입력 / cout 콘솔 출력

    
    while (num == 18)
    {
        cout << "다시 입력하세요" << endl;
        cin >> num;
    }

    cout << "while문 종료 신호  " << num << endl; 
    return 0;
}
    */

