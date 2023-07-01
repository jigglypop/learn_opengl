// static lib 사용
#define GLEW_STATIC
 
// include 순서는 glew > glfw 순서로.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
 
void render(GLFWwindow* window);
 
int main(void)
{
    // MAC일 경우에 4.1버전을 가져오기
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
 
    // glfw 초기화
    glfwInit();
 
    // window 만들기 (width, height, title, monitor, share)
    GLFWwindow* window = glfwCreateWindow(640, 480, "Inyong", 0, 0);
    
    // context는 그리기 위한 내용을 담고 있음
    // window가 두개이면 context가 두개일수도 있음
    // 그러면 어떤 context로 그릴지 정해줘야 함
    glfwMakeContextCurrent(window);
 
    // context가 만들어지고 난 후, glew 초기화
    glewInit();
 
    // 사용자가 window 창을 닫을 때까지
    while (!glfwWindowShouldClose(window)) {
        // window 그려주기
        render(window);
 
        // 마우스 움직이는 것. 이런것들 들고와서 필요한 window한테 보내주기
        glfwPollEvents();
    }
 
    // window가 닫혔을 경우 끝내자
    glfwDestroyWindow(window);
    glfwTerminate();
}
 
void render(GLFWwindow* window) { 
    // 지우는 색깔 (어떤 색으로 칠할건지)
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
 
    // 깜빡거림 방지
    glfwSwapBuffers(window);
}
