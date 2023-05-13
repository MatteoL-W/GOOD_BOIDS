#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <tiny_gltf.h>
#include <cstdlib>
#include "Scene.h"
#include "utils/ProjectionMatrixHandler.h"

int main(int argc, char* argv[])
{
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;

        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    auto ctx = p6::Context{{.title = "GOOD_BOIDS"}};
    ctx.maximize_window();
    ctx.framerate_capped_at(60); // Avoid different results on 240Hz/60Hz

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto* window = ctx.underlying_glfw_window();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    ctx.key_pressed = [&](p6::Key const& key) {
        if (key.physical == GLFW_KEY_ESCAPE)
        {
            if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    };

    auto scene = Scene{};
    scene.setupWorld(ctx);

    auto& projectionMatrixHandler = utils::getProjectionMatrixHandlerInstance();
    projectionMatrixHandler.setProjection(ctx.aspect_ratio());
    ctx.main_canvas_resized = [&]() {
        projectionMatrixHandler.setProjection(ctx.aspect_ratio());
    };

    ctx.start();
    glpp::shut_down();
}