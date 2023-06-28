#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string.h> 
#include <cstdarg>
#include <mm_malloc.h>

GLuint vao = 0;
unsigned int buffer;

const unsigned int W = 300;
const unsigned int H = 300;

const char* vertFileName = "triangle.vert";
const char* fragFileName = "triangle.frag";

GLfloat positions[] = {
    -0.5f, -0.5f,
    -0.5f,  0.5f,
    0.5f, 0.5f,
};
// 파일 로더
const char* loadFile(const char* filename) {
    FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	size_t len = ftell(fp);
    rewind(fp);
    char* buf = (char*) malloc(sizeof(char) * (len + 4));
	size_t size = fread(buf, sizeof(char), len, fp);
	fclose(fp);
	buf[size] = '\0';
	return (const char*)buf;
}
// 쉐이더 붙이기
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

// vao 에러 처리
void initVao() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}

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
    if(glewInit() != GLEW_OK) printf("error");
    // vao 에러 처리부
    initVao();
    // 함수 시작 (버텍스 쉐이더, 프레그먼트 쉐이더 넣기)
    initFunc(loadFile(vertFileName), GL_VERTEX_SHADER, loadFile(fragFileName), GL_FRAGMENT_SHADER, NULL);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 완료
    glfwTerminate();
    return 0;
}