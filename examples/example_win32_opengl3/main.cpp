// Dear ImGui: standalone example application for Win32 + OpenGL 3
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// This is provided for completeness, however it is strongly recommended you use OpenGL with SDL or GLFW.

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>

// Data stored per platform window
struct WGL_WindowData { HDC hDC; };

// Data
static HGLRC            g_hRC;
static WGL_WindowData   g_MainWindow;
static int              g_Width;
static int              g_Height;

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    // :: with no class name before it means GLOBAL Function/Variable.
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui Win32+OpenGL3 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize OpenGL
    if (!CreateDeviceWGL(hwnd, &g_MainWindow))
    {
        CleanupDeviceWGL(hwnd, &g_MainWindow);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }
    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Load Fonts
    // backslash '\\' need double \ 
    ImFont* font1 = io.Fonts->AddFontFromFileTTF("C:\\Users\\ths\\Desktop\\imgui-master\\misc\\fonts\\Roboto-Medium.ttf", 18.0f);
    ImFont* font2 = io.Fonts->AddFontFromFileTTF("C:\\Users\\ths\\Desktop\\imgui-master\\misc\\fonts\\SourceHanSansSC.otf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    // background color parameter
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    // TODO: 
    //      1. Language switch. --> Font Switch.(Chinese is always output ?, pretty strange.) Finished.
    //      2. Center every component.
    //      3. Color & Background switch. # BackgroundColor in Tables & Columns Finished.
    //      4. Sub Window for Tips. Finished.
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        // if (show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGuiStyle& Style = ImGui::GetStyle();
            auto color = Style.Colors;

            static float f = 0.0f;
            static int counter = 0;
            static int Color = 1;
            static char str1[128] = "";
            static char str2[128] = "";
            static bool animate = true;
            static float progress = 0.0f, progress_dir = 1.0f;
            static int cnt = 0;
            static int font = 0;
            static bool change = false;

            enum Color { red, blue };
            enum Font { RobotoMedium, SourceHanSansSC };
            switch (Color) {
            case Color::blue:
                Style.ChildRounding = 8.0f;
                Style.FrameRounding = 5.0f;

                color[ImGuiCol_WindowBg] = ImColor(1,7,75,150);
                color[ImGuiCol_Button] = ImColor(51, 120, 255, 255);
                color[ImGuiCol_ButtonHovered] = ImColor(71, 140, 255, 255);
                color[ImGuiCol_ButtonActive] = ImColor(31, 100, 225, 255);

                color[ImGuiCol_FrameBg] = ImColor(54, 54, 54, 150);
                color[ImGuiCol_FrameBgActive] = ImColor(42, 42, 42, 150);
                color[ImGuiCol_FrameBgHovered] = ImColor(100, 100, 100, 150);

                color[ImGuiCol_CheckMark] = ImColor(51, 120, 255, 255);

                color[ImGuiCol_SliderGrab] = ImColor(51, 120, 255, 255);
                color[ImGuiCol_SliderGrabActive] = ImColor(31, 100, 225, 255);

                color[ImGuiCol_Header] = ImColor(51, 120, 255, 255);
                color[ImGuiCol_HeaderHovered] = ImColor(71, 140, 255, 255);
                color[ImGuiCol_HeaderActive] = ImColor(31, 100, 225, 255);
                break;

            case Color::red:
                Style.ChildRounding = 8.0f;
                Style.FrameRounding = 5.0f;

                color[ImGuiCol_WindowBg] = ImColor(94, 2, 38, 150);
                color[ImGuiCol_Button] = ImColor(192, 51, 74, 255);
                color[ImGuiCol_ButtonHovered] = ImColor(212, 71, 94, 255);
                color[ImGuiCol_ButtonActive] = ImColor(172, 31, 54, 255);

                color[ImGuiCol_FrameBg] = ImColor(54, 54, 54, 150);
                color[ImGuiCol_FrameBgActive] = ImColor(42, 42, 42, 150);
                color[ImGuiCol_FrameBgHovered] = ImColor(100, 100, 100, 150);

                color[ImGuiCol_CheckMark] = ImColor(192, 51, 74, 255);

                color[ImGuiCol_SliderGrab] = ImColor(192, 51, 74, 255);
                color[ImGuiCol_SliderGrabActive] = ImColor(172, 31, 54, 255);

                color[ImGuiCol_Header] = ImColor(192, 51, 74, 255);
                color[ImGuiCol_HeaderHovered] = ImColor(212, 71, 94, 255);
                color[ImGuiCol_HeaderActive] = ImColor(172, 31, 54, 255);
                break;
            }
            switch (font) {
                case Font::RobotoMedium:
                    if (change) {
                        change = false;
                        //ImGui::PopFont();
                    }
                    break;

                case Font::SourceHanSansSC:
                    change = true;
                    ImGui::PushFont(font2);
                    break;
            }

            ImGui::Begin("Login & Loader Demo");                          // Create a window called "Hello, world!" and append into it.
            //ImGui::PushFont(font2);
            ImGui::Text("A login & loading UI supporting dynamic color and font change.");               // Display some text (you can use a format strings too)
            //ImGui::PopFont();
            // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Tips here, click for more.", &show_another_window);

            // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            // if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //      counter++;
            // ImGui::SameLine();
            // ImGui::Text("counter = %d", counter);

            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            // // ImGui::SetCursorPos({ 430.0f,330.0f });
            // ImGui::Text(u8"color");
            // ImGui::SameLine();
            // // ImGui::SetCursorPos({ 505.0f,328.0f });
            // ImGui::SetNextItemWidth(80.0f);
            ImGui::Combo("Change color here!", &Color, "red\0blue\0", 3);
            ImGui::Combo("Change fonts here!", &font, "RobotoMedium\0SourceHanSansSC\0", 3);
            // Multiple same widget inside a window needs tag to differ.
            // Simply add tag after '##' as below.
            ImGui::Text("Account");
            // ImGui::DebugTextEncoding((const char *)u8"你好");
            // ImGui::Text(u8"中文 ");
            ImGui::InputTextWithHint(u8"##account", u8"Your account id here!", str1, 128);

            ImGui::Text(u8"Key");
            ImGui::InputTextWithHint(u8"##key", "Your password here!", str2, IM_ARRAYSIZE(str2), ImGuiInputTextFlags_Password);

            if (ImGui::Button("LogIn") && strlen(str1) && strlen(str2)) cnt++;
            ImGui::SameLine();
            if (animate && cnt > 0) {
                progress += progress_dir * 0.2f * ImGui::GetIO().DeltaTime;
                if (progress >= +1.1f) { animate = false; }
                if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
            }
            if (cnt && strlen(str1) && strlen(str2)) ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
            // ImGui::SetWindowPos(ImVec2(100, 100), ImGuiCond_Always);
            if (cnt) ImGui::Text("Current State : ");
            ImGui::SameLine();
            if (cnt == 0) {
                if (strlen(str1) == 0) {
                    ImGui::TextColored(ImVec4(1.0f, 0.16f, 0.0f, 0.5f), "Account is empty.");
                }
                else if (strlen(str2) == 0) {
                    ImGui::TextColored(ImVec4(1.0f, 0.16f, 0.0f, 0.5f), "Password is empty.");
                }
            }
            if (cnt > 0) {
                if (strlen(str1) == 0) {
                    ImGui::TextColored(ImVec4(1.0f, 0.16f, 0.0f, 0.5f), "Account is empty.");
                }
                else if (strlen(str2) == 0) {
                    ImGui::TextColored(ImVec4(1.0f, 0.16f, 0.0f, 0.5f), "Password is empty.");
                }
                else if (progress < 0.3f) {
                    ImGui::TextColored(ImVec4(1.0f, 0.16f, 0.0f, 0.5f), "Linking to the server.");
                }
                else if (progress < 0.6f) {
                    ImGui::TextColored(ImVec4(1.0f,0.5f, 0.0f, 1.0f), "Verifying account.");
                }
                else if (progress < 0.85f) {
                    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 0.5f), "Account pass.");
                }
                else if (progress < 0.99f) {
                    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 0.5f), "Loading.");
                }
                else {
                    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 0.5f), "Success.");
                }
            }
            if (change) ImGui::PopFont();
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Tips for how to use this GUI", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Welcome to tips.");
            ImGui::Text("1. You can change color between red and blue. Check the color combo.");
            ImGui::Text("2. You can change fonts between Roboto-Medium and SourceHanSansSC. Check the font combo.");
            ImGui::Text("3. Type in your account and password before pressing the Login, or nothing will happen.");
            ImGui::Text("4. You can check your current login state at the state output.");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, g_Width, g_Height);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Present
        ::SwapBuffers(g_MainWindow.hDC);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceWGL(hwnd, &g_MainWindow);
    wglDeleteContext(g_hRC);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    if (!g_hRC)
        g_hRC = wglCreateContext(data->hDC);
    return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    wglMakeCurrent(NULL, NULL);
    ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            g_Width = LOWORD(lParam);
            g_Height = HIWORD(lParam);
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}


// dark color
// R:42 G:14 B:47 A:255
// shallow color
// R:66 G:150 B:250 A:179
