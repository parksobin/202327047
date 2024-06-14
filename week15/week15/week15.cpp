#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>

// 상수 정의
const int INPUT_HZ = 8000; // 입력 처리 빈도 (1초에 8000회)
const int RENDER_HZ = 60;  // 렌더링 빈도 (1초에 60회)
const double INPUT_INTERVAL = 1.0 / INPUT_HZ; // 입력 처리 주기
const double RENDER_INTERVAL = 1.0 / RENDER_HZ; // 렌더링 주기

// 함수 선언
void processInput(GLFWwindow* window); // 입력 처리 함수
void render(); // 렌더링 함수

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    // 창 생성 및 OpenGL 컨텍스트 생성
    GLFWwindow* window = glfwCreateWindow(640, 480, "Game Loop Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "GLFW 창 생성 실패" << std::endl;
        return -1;
    }

    // 생성한 창의 컨텍스트를 현재 컨텍스트로 설정
    glfwMakeContextCurrent(window);

    // 시간 설정
    auto previousTime = std::chrono::high_resolution_clock::now();
    double inputAccumulator = 0.0;
    double renderAccumulator = 0.0;

    // 메인 게임 루프
    while (!glfwWindowShouldClose(window)) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - previousTime;
        previousTime = currentTime;
        double deltaTime = elapsed.count();

        // 축적기 업데이트
        inputAccumulator += deltaTime;
        renderAccumulator += deltaTime;

        // 입력 처리를 1초에 8000회 실행
        while (inputAccumulator >= INPUT_INTERVAL) {
            processInput(window);
            inputAccumulator -= INPUT_INTERVAL;
        }

        // 렌더링을 1초에 60회 실행
        if (renderAccumulator >= RENDER_INTERVAL) {
            render();
            renderAccumulator = 0.0;
        }

        // CPU 사용량을 줄이기 위해 잠시 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // 정리 및 종료
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    // 이벤트 폴링 및 처리
    glfwPollEvents();

    // 입력 처리 예제
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        std::cout << "스페이스당" << std::endl;
    }
}


void render() {
    // 렌더링
    // 예제 렌더링: 여기에 렌더링 코드 추가
    std::cout << "렌더링 중..." << std::endl;
}
