#include <Windows.h>
#include "wunise/application.h"
#include "wunise/mygl.h"
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {

    wunise::Application app;
    app.InitWindow(hInstance, 300, 300);
    const char* vertexShaderSource = "#version 450 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 450 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    wunise::GLObject globject;

    globject.InitShader(vertexShaderSource, fragmentShaderSource);

    while (!app.WindowShouldClose()) {

        app.SwapBuffer();
    }
    app.DestroyWindow();
    return 0;
}
