#pragma once
#include "subsystem.h"
#include "clickable_component.h"

class clickable_system : public subsystem
{
private:
	std::vector<clickable_data> _data;
	clickable_system();

public:

	static std::shared_ptr<clickable_system> get();

	std::shared_ptr<clickable_component> build_component(std::shared_ptr<entity> e, glm::dvec2 x_bounds, glm::dvec2 y_bounds);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};

