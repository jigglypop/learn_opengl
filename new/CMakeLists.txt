#OpenGL 라이브러리 설정시 find_packages 는 모든 OS 에서 잘 작동함.
find_package(OpenGL REQUIRED)

# #freeglut 라이브러리 설정
# set(GLUT_LIBRARIES libglut.3.dylib)
# set(GLUT_INCLUDE_DIRS /usr/local/Cellar/freeglut/3.0.0/include)
# set(GLUT_LIBRARY_DIRS /usr/local/Cellar/freeglut/3.0.0/lib)

#GLEW 라이브러리 설정
set(GLEW_LIBRARIES libGLEW.dylib)
set(GLEW_INCLUDE_DIRS /opt/homebrew/Cellar/glew/2.2.0_1/include)
set(GLEW_LIBRARY_DIRS /opt/homebrew/Cellar/glew/2.2.0_1/lib)

INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
LINK_LIBRARIES( ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
LINK_DIRECTORIES ( ${OPENGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})