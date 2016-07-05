#include "system/SysWindow.h"

extern "C" {
    #include <GLFW/glfw3.h>
}

namespace izanagi
{
namespace sys
{
    // ウインドのもろもろを保持しておく用
    class CWindowGLFW : public CPlacementNew {
    public:
        static CWindowGLFW* s_Instance;

    public:
        // インスタンス作成
        static CWindowGLFW* Create(
            IMemoryAllocator* allocator,
            CMessageHandler* handler);

        // インスタンス破棄
        static void Destroy(CWindowGLFW* window);

    protected:
        CWindowGLFW() {}
        ~CWindowGLFW() {}

    public:
        CMessageHandler* GetHandler() { return m_MsgHandler; }

        GLFWwindow* glfwWindow{ nullptr };

        int mouseX{ 0 };
        int mouseY{ 0 };

    private:
        IMemoryAllocator* m_Allocator;
        CMessageHandler* m_MsgHandler;
    };

    CWindowGLFW* CWindowGLFW::s_Instance = IZ_NULL;

    // インスタンス作成
    CWindowGLFW* CWindowGLFW::Create(
        IMemoryAllocator* allocator,
        CMessageHandler* handler)
    {
        if (s_Instance == IZ_NULL) {
            void* buf = ALLOC(allocator, sizeof(CWindowGLFW));
            VRETURN_NULL(buf != IZ_NULL);

            CWindowGLFW* window = new(buf)CWindowGLFW();

            window->m_Allocator = allocator;
            window->m_MsgHandler = handler;

            s_Instance = window;
        }

        return s_Instance;
    }

    // インスタンス破棄
    void CWindowGLFW::Destroy(CWindowGLFW* window)
    {
        IMemoryAllocator* allocator = window->m_Allocator;

        delete window;
        FREE(allocator, window);

        s_Instance = IZ_NULL;
    }

    ///////////////////////////////////////////////////////////////////

    static void Display()
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

        CWindowGLFW::s_Instance->GetHandler()->OnIdle();
    }

    static void closeCallback(GLFWwindow* window)
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

#if 0
        CMessageHandler* handler = CWindowGLFW::s_Instance->GetHandler();

        handler->OnTerminate();
        
        CWindowGLFW::Destroy(CWindowGLFW::s_Instance);

        handler->OnDestroy();

        glfwDestroyWindow(CWindowGLFW::s_Instance->glfwWindow);
        glfwTerminate();
#else
        ::glfwSetWindowShouldClose(window, GL_TRUE);
#endif
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

        //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)

        E_KEYBOARD_BUTTON mappedKey = CSysWindow::GetKeyMap(key);

        if (action == GLFW_PRESS) {
            CWindowGLFW::s_Instance->GetHandler()->OnKeyDown(mappedKey);
        }
        else if (action == GLFW_RELEASE) {
            CWindowGLFW::s_Instance->GetHandler()->OnKeyUp(mappedKey);
        }
    }

    static void mouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

        CMessageHandler* handler = CWindowGLFW::s_Instance->GetHandler();

        auto x = CWindowGLFW::s_Instance->mouseX;
        auto y = CWindowGLFW::s_Instance->mouseY;

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                handler->OnMouseLBtnDown(CIntPoint(x, y));
            }
            else if (action == GLFW_RELEASE) {
                handler->OnMouseLBtnUp(CIntPoint(x, y));
            }
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            if (action == GLFW_PRESS) {
                handler->OnMouseRBtnDown(CIntPoint(x, y));
            }
            else if (action == GLFW_RELEASE) {
                handler->OnMouseRBtnUp(CIntPoint(x, y));
            }
        }
    }

    static void motionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

        CWindowGLFW::s_Instance->mouseX = (int)xpos;
        CWindowGLFW::s_Instance->mouseY = (int)ypos;

        CWindowGLFW::s_Instance->GetHandler()->OnMouseMove(
            CIntPoint(CWindowGLFW::s_Instance->mouseX, CWindowGLFW::s_Instance->mouseY));
    }

    static void wheelCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

        CWindowGLFW::s_Instance->GetHandler()->OnMouseWheel((int)xoffset);
    }

    E_KEYBOARD_BUTTON CSysWindow::GetKeyMap(IZ_UINT key)
    {
        if ('0' <= key && key <= '9') {
            key = key - '0';
            return (E_KEYBOARD_BUTTON)(E_KEYBOARD_BUTTON_0 + key);
        }
        else if ('A' <= key && key <= 'Z') {
            key = key - 'A';
            return (E_KEYBOARD_BUTTON)(E_KEYBOARD_BUTTON_A + key);
        }
        else {
            switch (key) {
            case GLFW_KEY_ESCAPE:
                return E_KEYBOARD_BUTTON_ESCAPE;
            case GLFW_KEY_ENTER:
                return E_KEYBOARD_BUTTON_RETURN;
            case GLFW_KEY_TAB:
                return E_KEYBOARD_BUTTON_TAB;
            case GLFW_KEY_BACKSPACE:
                return E_KEYBOARD_BUTTON_BACKSPACE;
            case GLFW_KEY_INSERT:
                return E_KEYBOARD_BUTTON_INSERT;
            case GLFW_KEY_DELETE:
                return E_KEYBOARD_BUTTON_DELETE;
            case GLFW_KEY_RIGHT:
                return E_KEYBOARD_BUTTON_RIGHT;
            case GLFW_KEY_LEFT:
                return E_KEYBOARD_BUTTON_LEFT;
            case GLFW_KEY_DOWN:
                return E_KEYBOARD_BUTTON_DOWN;
            case GLFW_KEY_UP:
                return E_KEYBOARD_BUTTON_UP;
            case GLFW_KEY_F1:
                return E_KEYBOARD_BUTTON_F1;
            case GLFW_KEY_F2:
                return E_KEYBOARD_BUTTON_F2;
            case GLFW_KEY_F3:
                return E_KEYBOARD_BUTTON_F3;
            case GLFW_KEY_F4:
                return E_KEYBOARD_BUTTON_F4;
            case GLFW_KEY_F5:
                return E_KEYBOARD_BUTTON_F5;
            case GLFW_KEY_F6:
                return E_KEYBOARD_BUTTON_F6;
            case GLFW_KEY_F7:
                return E_KEYBOARD_BUTTON_F7;
            case GLFW_KEY_F8:
                return E_KEYBOARD_BUTTON_F8;
            case GLFW_KEY_F9:
                return E_KEYBOARD_BUTTON_F9;
            case GLFW_KEY_F10:
                return E_KEYBOARD_BUTTON_F10;
            case GLFW_KEY_F11:
                return E_KEYBOARD_BUTTON_F11;
            case GLFW_KEY_F12:
                return E_KEYBOARD_BUTTON_F12;
            case GLFW_KEY_LEFT_SHIFT:
                return E_KEYBOARD_BUTTON_SHIFT;
            case GLFW_KEY_LEFT_CONTROL:
                return E_KEYBOARD_BUTTON_CONTROL;
            case GLFW_KEY_RIGHT_SHIFT:
                return E_KEYBOARD_BUTTON_SHIFT;
            case GLFW_KEY_RIGHT_CONTROL:
                return E_KEYBOARD_BUTTON_CONTROL;
            case GLFW_KEY_SPACE:
                return E_KEYBOARD_BUTTON_SPACE;
            default:
                break;
            }
        }

        //IZ_ASSERT(IZ_FALSE);
        return E_KEYBOARD_BUTTON_UNDEFINED;
    }

    static void errorCallback(int error, const char* description)
    {
        IZ_PRINTF("Error: %s\n", description);
    }

    WindowHandle CSysWindow::Create(
        IMemoryAllocator* allocator,
        const WindowParams& param)
    {
        ::glfwSetErrorCallback(errorCallback);

        auto result = ::glfwInit();
        if (!result) {
            IZ_ASSERT(IZ_FALSE);
            return nullptr;
        }

        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        CWindowGLFW* window = CWindowGLFW::Create(allocator, param.handler);
        VRETURN_NULL(window != IZ_NULL);

        window->glfwWindow = ::glfwCreateWindow(
            param.width,
            param.height,
            param.title,
            NULL, NULL);

        if (!window->glfwWindow) {
            ::glfwTerminate();
            IZ_ASSERT(IZ_FALSE);
            return nullptr;
        }

        ::glfwSetWindowCloseCallback(
            window->glfwWindow,
            closeCallback);

        ::glfwSetKeyCallback(
            window->glfwWindow,
            keyCallback);

        ::glfwSetMouseButtonCallback(
            window->glfwWindow,
            mouseCallback);

        ::glfwSetCursorPosCallback(
            window->glfwWindow,
            motionCallback);

        ::glfwSetScrollCallback(
            window->glfwWindow,
            wheelCallback);

        if (param.handler) {
            param.handler->OnInit(IZ_NULL);
        }

        return window;
    }

    // ウインドウ破棄.
    void CSysWindow::Destroy(WindowHandle handle)
    {
    }

    // ループ実行.
    void CSysWindow::RunLoop(WindowHandle handle)
    {
        IZ_ASSERT(CWindowGLFW::s_Instance != IZ_NULL);

        auto window = CWindowGLFW::s_Instance->glfwWindow;
        IZ_ASSERT(window != nullptr);

        while (!glfwWindowShouldClose(window))
        {
            CWindowGLFW::s_Instance->GetHandler()->OnIdle();

            glfwPollEvents();
        }
    }

    void* CSysWindow::GetNativeWindowHandle(const WindowHandle& handle)
    {
        return IZ_NULL;
    }

    void* CSysWindow::GetNativeDisplayHandle(const WindowHandle& handle)
    {
        return IZ_NULL;
    }

}   // namespace sys
}   // namespace izanagi
