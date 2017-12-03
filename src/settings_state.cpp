#define GLM_ENABLE_EXPERIMENTAL
#include "settings_state.h"
#include "entity_manager.h"
#include <iostream>
#include "text2D.h"
#include <sstream>
#include <iomanip>
void settings_state::initialise()
{
	initText2D("res/textures/myriad.png");

	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size / 1.25, y_size / 1.25, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::SETTINGS, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// Resolution transform
	transform_data resolution_transform;
	resolution_transform.x = x_size / 2 - 225;
	resolution_transform.y = y_size / 2;
	// Resolution
	auto resolution = entity_manager::get()->create_entity("Resolution", state_type::SETTINGS, resolution_transform);
	resolution->add_component("render", renderer::get()->build_component(resolution, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	resolution->add_component("text", text_system::get()->build_component(resolution, "RESOLUTION"));

	// Resolution value transform
	transform_data resolution_value_transform;
	resolution_value_transform.x = resolution_transform.x;
	resolution_value_transform.y = y_size / 2 - 50;
	// Resolution value
	std::stringstream streamx;
	streamx << std::fixed << std::setprecision(4) << x_size;
	std::string sx = streamx.str();
	std::stringstream streamy;
	streamy << std::fixed << std::setprecision(4) << y_size;
	std::string sy = streamy.str();
	std::cout << sx << " x " << sy << std::endl;
	auto resolution_value = entity_manager::get()->create_entity("ResolutionValue", state_type::SETTINGS, resolution_value_transform);
	resolution_value->add_component("render", renderer::get()->build_component(resolution_value, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	resolution_value->add_component("text", text_system::get()->build_component(resolution_value, sx + " x " + sy));

	// Title transform
	transform_data title_transform;
	title_transform.x = x_size / 2 - 200;
	title_transform.y = y_size - 250;
	// Title
	auto title = entity_manager::get()->create_entity("Title", state_type::SETTINGS, title_transform);
	title->add_component("render", renderer::get()->build_component(title, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	title->add_component("text", text_system::get()->build_component(title, "SETTINGS"));

	// Buttons

	int x_center = x_size / 2;
	int y_center = y_size / 2;

	int x_button_size = 25;
	int y_button_size = 25;

	// right arrow trans
	transform_data right_arrow_transform;
	right_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	right_arrow_transform.x = 250;
	right_arrow_transform.y = 60;

	// left arrow trans
	transform_data left_arrow_transform;
	left_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	left_arrow_transform.x = -250;
	left_arrow_transform.y = 60;

	// Right arrow button
	auto button_right = entity_manager::get()->create_entity("buttonRight", state_type::SETTINGS, right_arrow_transform);
	button_right->add_component("clickable", clickable_system::get()->build_component(button_right, glm::dvec2(250, -60), glm::dvec2(x_button_size, y_button_size)));
	button_right->add_component("render", renderer::get()->build_component(button_right, glm::vec4(0.0f, 0.0f,  0.0f, 1.0f), "res/textures/arrow_right_transparent.png", "rectangle", "Gouraud", simple_texture));
	button_right->add_component("camera", camera_system::get()->build_component(button_right, camera_type::ORTHO));

	// Left arrow button
	auto button_left = entity_manager::get()->create_entity("buttonLeft", state_type::SETTINGS, left_arrow_transform);
	button_left->add_component("clickable", clickable_system::get()->build_component(button_left, glm::dvec2(-250, -60), glm::dvec2(x_button_size, y_button_size)));
	button_left->add_component("render", renderer::get()->build_component(button_left, glm::vec4(0.0f, 0.0f,  0.0f, 1.0f), "res/textures/arrow_left_transparent.png", "rectangle", "Gouraud", simple_texture));
	button_left->add_component("camera", camera_system::get()->build_component(button_left, camera_type::ORTHO));

}

void settings_state::on_reset()
{

}

void settings_state::on_enter()
{
	// Switch off physics
	auto m = engine::get()->get_subsystem("entity_manager");
	// TODO: Should entity manager be enabled?
	engine::get()->get_subsystem("entity_manager")->set_active(true);
	engine::get()->get_subsystem("entity_manager")->set_visible(true);
	engine::get()->get_subsystem("physics_system")->set_active(false);
	engine::get()->get_subsystem("clickable_system")->set_active(true);
	engine::get()->get_subsystem("renderer")->set_visible(true);
	engine::get()->get_subsystem("text_system")->set_active(true);

	glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	std::cout << "Entered settings state, press ENTER to go to game state" << std::endl;
}

void determine_screen_res(resolution &res)
{
	switch (res)
	{
		case _1024x768:
			glfwSetWindowSize(glfw::window, 1024, 768);
			break;
		case _1280x720:
			glfwSetWindowSize(glfw::window, 1280, 720);
			break;
		case _1600x1200:
			glfwSetWindowSize(glfw::window, 1600, 1200);
			break;
		case _1920x1080:
			glfwSetWindowSize(glfw::window, 1920, 1080);
			break;
	}
}

void settings_state::on_update(float delta_time)
{
	//std::cout << "********** SETTINGS DISPLAYED ****************" << std::endl;
	std::shared_ptr<clickable_system> cs = std::static_pointer_cast<clickable_system>(engine::get()->get_subsystem("clickable_system"));
	if (cs->get_clicked_component_name() == "buttonRight")
	{
		// Wrap around
		switch (current_resolution)
		{
		case _1024x768:
			current_resolution = _1280x720;
			break;
		case _1280x720:
			current_resolution = _1600x1200;
			break;
		case _1600x1200:
			current_resolution = _1920x1080;
			break;
		case _1920x1080:
			current_resolution = _1024x768;
			break;
		}
		determine_screen_res(current_resolution);

		//glfwSetWindowSize(glfw::window, 1600, 1200);
		cs->clear_clicked_component_name();

	}
	else if (cs->get_clicked_component_name() == "buttonLeft")
	{
		// Wrap around
		switch (current_resolution)
		{
		case _1024x768:
			current_resolution = _1920x1080;
			break;
		case _1280x720:
			current_resolution = _1024x768;
			break;
		case _1600x1200:
			current_resolution = _1280x720;
			break;
		case _1920x1080:
			current_resolution = _1600x1200;
			break;
		}
		determine_screen_res(current_resolution);

		cs->clear_clicked_component_name();
	}
}

void settings_state::on_exit()
{
	std::cout << "Exiting settings state" << std::endl;
}