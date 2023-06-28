#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string.h> 
#include <cstdarg>
#include <mm_malloc.h>

GLint status;
GLuint vao = 0;
GLuint locPos;
GLuint locCor;

unsigned int buffer;
char buf[1024];
const unsigned int W = 300;
const unsigned int H = 300;

const char* vertFileName = "triangle.vert";
const char* fragFileName = "triangle.frag";

GLuint vert = 0; 
GLuint frag = 0; 
GLuint prog = 0; 

GLfloat vertPosFirst[] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.0F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.0F, 0.0F, 1.0F,
};
GLfloat vertPosSecond[] = {
	0.0F, 0.0F, 0.0F, 1.0F,
	0.5F, 0.0F, 0.0F, 1.0F,
	0.0F, 0.5F, 0.0F, 1.0F,
};
GLfloat vertColor[] = {
	1.0F, 0.0F, 0.0F, 1.0F, // red
	0.0F, 1.0F, 0.0F, 1.0F, // green
	0.0F, 0.0F, 1.0F, 1.0F, // blue
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
    // 에러처리
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    printf("vert compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
    glGetShaderInfoLog(shader, sizeof(buf), NULL, buf);
    printf("vert log = [%s]\n", buf);
}
// vao 에러 처리
void initVao() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}
// 펑션 시작
void initFunc(const char* shader, ...) {
    prog = glCreateProgram();
    va_list args;
    va_start(args, shader);
    while (shader) {
        const GLenum type = va_arg( args, GLenum);
        AttachShader(prog, type, shader);
        shader = va_arg(args, const char*);
    }
    va_end(args);
    glLinkProgram(prog);
    glUseProgram(prog);
}
// 그리기
void drawFunc(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    // 포지션
    locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, vertPosFirst);
    // 색깔
	locCor = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(locCor);
	glVertexAttribPointer(locCor, 4, GL_FLOAT, GL_FALSE, 0, vertColor);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 두번째 포지션
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, vertPosSecond);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    // done
	glFinish();
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
    glClearColor(0.3F, 0.3F, 0.3F, 1.0F);
    initFunc(
        loadFile(vertFileName), 
        GL_VERTEX_SHADER, 
        loadFile(fragFileName), 
        GL_FRAGMENT_SHADER, NULL
    );
    while (!glfwWindowShouldClose(window)) {
        drawFunc();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // 완료
    glfwTerminate();
    return 0;
}