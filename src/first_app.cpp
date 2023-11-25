//
// Created by llaczko on 25/11/23.
//
#include "first_app.hpp"

namespace lve {
    void FirstApp::run() {
        while(!lveWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}