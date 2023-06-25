## glfwMakeContextCurrent

```c++

void glfwMakeContextCurrent	(GLFWwindow *window)

```

이 함수는 지정된 창의 OpenGL 또는 OpenGL ES 컨텍스트를 호출 스레드에서 현재로 만듭니다. 컨텍스트는 한 번에 하나의 스레드에서만 최신 상태로 만들어야 하며 각 스레드는 한 번에 하나의 현재 컨텍스트만 가질 수 있습니다.

스레드 간에 컨텍스트를 이동할 때 새 스레드에서 현재 상태로 만들기 전에 이전 스레드에서 컨텍스트를 현재 상태가 아닌 상태로 만들어야 합니다.

기본적으로 컨텍스트를 현재가 아닌 상태로 만들면 암시적으로 파이프라인 플러시가 강제로 실행됩니다. 를 지원하는 시스템에서는 GLFW_CONTEXT_RELEASE_BEHAVIORGL_KHR_context_flush_control 힌트 를 설정하여 컨텍스트가 이 플러시를 수행할지 여부를 제어할 수 있습니다 .

지정된 창에는 OpenGL 또는 OpenGL ES 컨텍스트가 있어야 합니다. 컨텍스트 없이 창을 지정하면 GLFW_NO_WINDOW_CONTEXT 오류가 발생합니다.

매개변수
[안에] 창문 NULL컨텍스트를 현재로 만들거나 현재 컨텍스트를 분리할 창입니다 .
오류
가능한 오류에는 GLFW_NOT_INITIALIZED , GLFW_NO_WINDOW_CONTEXT 및 GLFW_PLATFORM_ERROR 가 포함됩니다 .
스레드 안전성
이 함수는 모든 스레드에서 호출할 수 있습니다.
또한보십시오
현재 컨텍스트
glfwGetCurrentContext
부터
3.0 버전에서 추가되었습니다.
