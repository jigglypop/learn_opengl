#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h> // for strrchr()

// 윈도우 사이즈 정의
const unsigned int WIN_W = 300; 
const unsigned int WIN_H = 300;
// 윈도우 픽셀 정의 
const unsigned int WIN_X = 100; 
const unsigned int WIN_Y = 100;
// 점 정의
GLfloat vertPos[] = {
	-0.5F,
	-0.5F,
	0.0F,
	1.0F,
	+0.5F,
	-0.5F,
	0.0F,
	1.0F,
	-0.5F,
	+0.5F,
	0.0F,
	1.0F,
};




void refreshFunc(GLFWwindow* window) {
	// refresh
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();
	// GLFW action
	glfwSwapBuffers(window);
}

void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
		break;

	}

}


int main(int argc, char* argv[]) {
    // get your program name
#if defined(_WIN32) || defined(_WIN64)
	char* win_name = (strrchr(argv[0], '\\') == NULL) ? argv[0] : (strrchr(argv[0], '\\') + 1);
#else // Unix, Linux, MacOS
	char* win_name = (strrchr(argv[0], '/') == NULL) ? argv[0] : (strrchr(argv[0], '/') + 1);
#endif
	// start GLFW & GLEW
	glfwInit();
    // 윈도우 정의
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, win_name, NULL, NULL);
    // 윈도우 크기 정의
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);
	glewInit();
	// prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.933F, 0.009F, 0.098F, 1.0F);
	// main loop
	while (! glfwWindowShouldClose(window)) {
		// draw
		glClear(GL_COLOR_BUFFER_BIT);
		glFinish();
		// GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// done
	glfwTerminate();
	return 0;
}
