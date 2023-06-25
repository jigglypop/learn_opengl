#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h> // for strrchr()
#include <cstdarg>
// #include "./common.c"

const unsigned int W = 300;
const unsigned int H = 300;
const unsigned int X = 100;
const unsigned int Y = 100;

GLfloat positions[] = {
    -0.5f, -0.5f,
    -0.5f,  0.5f,
    0.5f, 0.5f,
};

const char* loadFile(const char* filename) {
    FILE *fp = fopen(filename, "r");
}

void AttachShader(GLuint program, GLenum type, const char *src){
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    glAttachShader(program, shader);
}

void initFunc(const char* shader, ...) {
    GLuint program = glCreateProgram();
    va_list args;
    va_start(args, shader);
    while (shader) {
        const GLenum type = va_arg( args, GLenum);
        AttachShader(program, type, shader);
        shader = va_arg(args, const char*);
    }
    va_end(args);
    glLinkProgram(program);
    glUseProgram(program);
}


const char* vertexShader = 
"#version 410 core \n\
in vec4 vertexPos; \n\
void main(void) { \n\
	gl_Position = vertexPos; \n\
}";

const char* fragmentShader = 
"#version 410 core \n\
out vec4 FragColor; \n\
void main(void) { \n\
	FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n\
}";

int main() {
    glfwInit();
    /* Core profile */
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // 윈도우 오픈
    GLFWwindow* window = glfwCreateWindow(W, H, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    if( glewInit() != GLEW_OK ) printf("error");

    GLuint vao = 0;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // 함수 시작 (버텍스 쉐이더, 프레그먼트 쉐이더 넣기)
    initFunc(vertexShader, GL_VERTEX_SHADER, fragmentShader, GL_FRAGMENT_SHADER, NULL);
    
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // 완료
    glfwTerminate();
    return 0;
}