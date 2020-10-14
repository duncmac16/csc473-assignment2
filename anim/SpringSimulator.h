#pragma once

#include "BaseSimulator.h"
#include "BaseSystem.h"
#include "ParticleSystem.h"
#include "GlobalResourceManager.h"

class SpringSimulator : public BaseSimulator {
public:
	SpringSimulator(const std::string& name) : BaseSimulator{ name } {}

	int command(int argc, myCONST_SPEC char** argv)
	{
		if (strcmp(argv[0], "link") == 0) {
			try {
				BaseSystem* p_sys = GlobalResourceManager::use()->getSystem(argv[1]);
				link_system(p_sys, std::stoi(argv[2]));
			}
		}
		else if (strcmp(argv[0], "spring") == 0) {

		}
		else if (strcmp(argv[0], "fix") == 0) {

		}
		else if (strcmp(argv[0], "integration") == 0) {

		}
		else if (strcmp(argv[0], "ground") == 0) {

		}
		else if (strcmp(argv[0], "gravity") == 0) {

		}
		else if (strcmp(argv[0], "drag") == 0) {

		}
		else {
			animTcl::OutputMessage("[Spring Simulator] Error: Could not match command \"%s\" to any known"
				"spring commands\n", argv[0]);
		}
	}

private:
	std::vector<ParticleSystem*> particle_systems;

	void link_system(BaseSystem* p_sys, std::size_t num_springs)
	{

	}
};