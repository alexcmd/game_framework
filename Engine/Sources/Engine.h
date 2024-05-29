#pragma once
#include "EngineConfig.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/math.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

// Platform-specific includes
#if BX_PLATFORM_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#elif BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    #define GLFW_EXPOSE_NATIVE_X11
    #include <GLFW/glfw3native.h>
#endif


// Vulkan instance and surface
VkInstance g_instance = VK_NULL_HANDLE;
VkSurfaceKHR g_surface = VK_NULL_HANDLE;

// GLFW error callback
static void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

// Initialize GLFW and create a window
GLFWwindow* initGLFW()
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "BGFX Vulkan Example", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    return window;
}

// Initialize Vulkan and create a surface for the given window
void initVulkan(GLFWwindow* window)
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "BGFX Vulkan Example";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (vkCreateInstance(&createInfo, nullptr, &g_instance) != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance" << std::endl;
        return;
    }

    // if (glfwCreateWindowSurface(g_instance, window, nullptr, &g_surface) != VK_SUCCESS)
    // {
    //     std::cerr << "Failed to create Vulkan surface" << std::endl;
    //     return;
    // }
}

// Initialize BGFX with Vulkan backend
void initBGFX(GLFWwindow* window)
{
    initVulkan(window);

    bgfx::Init init;
    init.type = bgfx::RendererType::Vulkan;
    init.resolution.width = 1280;
    init.resolution.height = 720;
    init.resolution.reset = BGFX_RESET_VSYNC;

#if BX_PLATFORM_WINDOWS
    init.platformData.nwh = glfwGetWin32Window(window);
#elif BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#endif

    if (!bgfx::init(init))
    {
        std::cerr << "Failed to initialize BGFX" << std::endl;
        return;
    }

    bgfx::reset(1280, 720, BGFX_RESET_VSYNC);
}

inline int run()
{
    GLFWwindow* window = initGLFW();
    if (!window) return -1;

    initBGFX(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Set view 0 clear state
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

        // Set view 0 viewport
        bgfx::setViewRect(0, 0, 0, uint16_t(1280), uint16_t(720));

        // Submit an empty frame
        bgfx::touch(0);

        // Frame
        bgfx::frame();
    }

    // Cleanup
    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    // Destroy Vulkan surface and instance
    vkDestroySurfaceKHR(g_instance, g_surface, nullptr);
    vkDestroyInstance(g_instance, nullptr);

    return 0;
}