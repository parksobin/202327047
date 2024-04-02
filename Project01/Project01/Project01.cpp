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
/*
void MyMouseClick(int key) {
    if ( key == GLFW_MOUSE_BUTTON_1) {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    }
}
*/

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

