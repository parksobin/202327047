
/*
#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
const float M_PI = 3.14159265358979323846f;

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

int setVertexRotation(float x, float y, float angle_degree)
{ // 태양 그리기 기초 함수
    float angle = angle_degree / 180 * M_PI;
    glVertex2f(x * cos(angle) - (y * sin(angle)), x * sin(angle) + (y * cos(angle)));
    return 0;
}

int setVertexEarthRotation(float x, float y, float orbit_angle_degree, float rotate_angle_degree, float sun_center_x, float sun_center_y, float orbit_radius)
{ //  지구 그리기 함수
    // 공전 각도 계산
    float orbit_angle = orbit_angle_degree * M_PI / 180;
    // 자전 각도 계산
    float rotate_angle = rotate_angle_degree * M_PI / 180;
    // 공전 중심 좌표 계산
    float orbit_x = sun_center_x + orbit_radius * cos(orbit_angle);
    float orbit_y = sun_center_y + orbit_radius * sin(orbit_angle);
    // 회전된 좌표 설정
    glVertex2f(orbit_x + x * cos(rotate_angle) - (y * sin(rotate_angle)), orbit_y + x * sin(rotate_angle) + (y * cos(rotate_angle)));
    return 0;
}

int setVertexMoonRotation(float x, float y, float orbit_angle_degree, float rotate_angle_degree, float earth_center_x, float earth_center_y, float orbit_radius)
{ // 달? 별? 그리기 함수
    // 공전 각도 계산
    float orbit_angle = orbit_angle_degree * M_PI / 180;
    // 자전 각도 계산
    float rotate_angle = rotate_angle_degree * M_PI / 180;
    // 공전 중심 좌표 계산
    float orbit_x = earth_center_x + orbit_radius * cos(orbit_angle);
    float orbit_y = earth_center_y + orbit_radius * sin(orbit_angle);
    // 회전된 좌표 설정
    glVertex2f(orbit_x + x * cos(rotate_angle) - (y * sin(rotate_angle)), orbit_y + x * sin(rotate_angle) + (y * cos(rotate_angle)));
    return 0;
}

//객체별 시작 각도 설정
float sunAngle = 0;
float sun_pattern_angle1 = 140;
float sun_pattern_angle2 = 240;
float EarthRotateAngle = 0;
float EarthOrbitAngle = 0;
float StarRotationAngle = 0;
float StarOrbitAngle = 0;

float sunRotationSpeed = 360.0f / 30.0f; // 태양이 한 바퀴 자전 시, 30초
float EarthRotationSpeed = 360.0f / 10.0f; // 지구가 한 바퀴 자전 시, 10초
float EarthOrbitSpeed = 360.0f / 60.0f; // 지구가 한 바퀴 공전 시, 60초
float StarRotateOrbitSpeed = 360.0f / 3.0f; // 달? 별?이 한 바퀴 공전 시, 3초
double previousTime = 0.0;

int render(float deltaTime)
{
    // 태양 그리기
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.85f, 0.4f);
    double radius = 0.3;
    for (int i = 0; i < 360; i++)
    {
        double x = radius * cos(i * M_PI / 180);
        double y = radius * sin(i * M_PI / 180);
        setVertexRotation(x, y, sunAngle);
    }
    glEnd();

    // 태양 테두리 그리기
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.77f, 0.35f, 0.06f);
    double rad = 0.3;
    double x[360], y[360];
    for (int i = 0; i < 360; i++)
    {
        double angle = i * M_PI / 180;
        x[i] = rad * cos(angle);
        y[i] = rad * sin(angle);
    }
    for (int i = 0; i < 359; i++)
    {
        setVertexRotation(x[i], y[i], sunAngle);
        setVertexRotation(x[i + 1], y[i + 1], sunAngle);
    }
    glEnd();

    // 태양 큰 무늬 그리기
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.9f, 0.6f);
    float pattern1_radius = 0.1;
    for (int i = 0; i < 360; i++)
    {
        double x = pattern1_radius * cos(i * M_PI / 180);
        double y = pattern1_radius * sin(i * M_PI / 180);
        setVertexRotation(x + 0.13, y + 0.13, sun_pattern_angle1);
    }
    glEnd();

    // 태양 작은 무늬 그리기
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.75f, 0.0f);
    float pattern2_radius = 0.05;
    for (int i = 0; i < 360; i++)
    {
        double x = pattern2_radius * cos(i * M_PI / 180);
        double y = pattern2_radius * 0.3 * sin(i * M_PI / 180);
        setVertexRotation(x + 0.008, y + 0.27, sun_pattern_angle2);
    }
    glEnd();

    // 파란색 사각형 그리기
    float sun_center_x = 0.0f;
    float sun_center_y = 0.0f;
    // 지구 공전 반지름 설정
    float orbit_radius = 0.6f;
    // 지구 그리기
    glBegin(GL_POLYGON);
    glColor3f(0.35f, 0.6f, 0.83f);
    setVertexEarthRotation(-0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(-0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    glEnd();

    //지구 테두리 그리기
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    setVertexEarthRotation(-0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(-0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    glEnd();

    // 지구의 중심 좌표를 불러와서  
    float earth_center_x = sun_center_x + orbit_radius * cos(EarthOrbitAngle * M_PI / 180);
    float earth_center_y = sun_center_y + orbit_radius * sin(EarthOrbitAngle * M_PI / 180);
    // 별의 공전 반지름
    float moon_orbit_radius = 0.15f;
    // 별의 크기 설정
    float star_radius = 0.05f;
    // 별 그리기
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.94f, 0.0f);
    setVertexMoonRotation(0.0f, 0.0f, StarOrbitAngle, StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    for (int i = 0; i < 360; i += 72) {
        float x = star_radius * cos(i * M_PI / 180);
        float y = star_radius * sin(i * M_PI / 180);
        setVertexMoonRotation(x, y, StarOrbitAngle, i + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexMoonRotation(x * 0.5f, y * 0.5f, StarOrbitAngle, i + 36 + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    }
    setVertexMoonRotation(star_radius, 0.0f, StarOrbitAngle, StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    glEnd();

    //// 별 테두리 그리기
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 360; i += 72) {
        float x = star_radius * cos(i * M_PI / 180);
        float y = star_radius * sin(i * M_PI / 180);
        setVertexMoonRotation(x * 0.5f, y * 0.5f, StarOrbitAngle, i - 36 + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexMoonRotation(x, y, StarOrbitAngle, i + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexMoonRotation(x, y, StarOrbitAngle, i + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexMoonRotation(x * 0.5f, y * 0.5f, StarOrbitAngle, i + 36 + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    }
    glEnd();

    //각 객체의 시작 각도에 회전 속도를 더하여 회전 이벤트 부여
    sunAngle -= sunRotationSpeed * deltaTime;
    sun_pattern_angle1 -= sunRotationSpeed * deltaTime;
    sun_pattern_angle2 -= sunRotationSpeed * deltaTime;
    EarthOrbitAngle += EarthOrbitSpeed * deltaTime;
    EarthRotateAngle += EarthRotationSpeed * deltaTime;
    StarRotationAngle += StarRotateOrbitSpeed * deltaTime;
    StarOrbitAngle -= StarRotateOrbitSpeed * deltaTime;
    return 0;
}
*/
/*
int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    previousTime = glfwGetTime(); //'이전 시간'이라는 변수에 현재 시간을 불러옴

    while (!glfwWindowShouldClose(window))
    {
        //기기 프레임별 회전 속도가 바뀌는 현상을 막기 위해 사용
        double currentTime = glfwGetTime(); // '현재 시간'이라는 변수에도 현재 시간을 불러옴
        float deltaTime = static_cast<float>(currentTime - previousTime); //현재 시간과 이전 시간의 차이를 deltaTime 변수로 계산
        previousTime = currentTime; // 이전 시간을 현재 시간으로 바꿔서 재사용 가능하게 설정

        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render(deltaTime);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
*/
