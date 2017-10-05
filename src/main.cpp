//
// Created by zoe on 28/09/17.
//

#include <iostream>
#include "engine.h"
#include "entity_manager.h"
#include "physics_system.h"
#include "renderer.h"
#include "state_machine.h"
//#include "engine_states.h"
#include "game_state.h"
#include "menu_state.h"
#include "input_handler.h"




// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

using namespace std;
// Include GLM
#include <glm/glm.hpp>
using namespace glm;


int main() {

    std::cout << "hello world" << std::endl;

    auto eng = engine::get();
    eng->add_subsystem("entity_manager", entity_manager::get());
    eng->add_subsystem("physics_system", physics_system::get());
    eng->add_subsystem("renderer", renderer::get());
    eng->add_subsystem("state_machine", engine_state_machine::get());
    eng->add_subsystem("input_handler", input_handler::get());

    engine_state_machine::get()->add_state("menu_state", std::make_shared<menu_state>());
    engine_state_machine::get()->add_state("game_state", std::make_shared<game_state>());
    engine_state_machine::get()->change_state("game_state");

    auto e = entity_manager::get()->create_entity("Test");
    e->add_component("physics", physics_system::get()->build_component(e));
    e->add_component("render", renderer::get()->build_component(e, "Blue", "Sphere", "Gouraud"));

	eng->run();

    return 0;
}