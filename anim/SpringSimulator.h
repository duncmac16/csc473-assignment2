#pragma once

#include "BaseSimulator.h"
#include "BaseSystem.h"
#include "ParticleSystem.h"
#include "GlobalResourceManager.h"
#include "Integration.h"

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
			catch (const std::exception& error) {
				animTcl::OutputMessage("[link] %s", error.what());
				return TCL_ERROR;
			}
		}
		else if (strcmp(argv[0], "spring") == 0) {
			try {
				m_particle_system->set_spring(std::stoi(argv[1]),
					std::stoi(argv[2]),
					std::stoi(argv[3]),
					std::stod(argv[4]),
					std::stod(argv[5]));
				return TCL_OK;
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[spring] %s", error.what());
				return TCL_ERROR;
			}
		}
		else if (strcmp(argv[0], "fix") == 0) {
			try {
				m_particle_system->particles()[std::stoi(argv[1])].m_fixed = true;
				return TCL_OK;
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[fix] %s", error.what());
				return TCL_ERROR;
			}
		}
		else if (strcmp(argv[0], "integration") == 0) {
			try {
				set_integration(argv[1], std::stod(argv[2]));
				m_integration->ground_plane(m_particle_system->ground_plane());
				return TCL_OK;
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[integration] %s", error.what());
				return TCL_ERROR;
			}
		}
		else if (strcmp(argv[0], "ground") == 0) {
			try {
				m_particle_system->ground_plane().ks(std::stod(argv[1]));
				m_particle_system->ground_plane().kd(std::stod(argv[2]));
				if (m_integration) {
					m_integration->ground_plane(m_particle_system->ground_plane());
				}
				return TCL_OK;
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[ground] %s", error.what());
				return TCL_ERROR;
			}
		}
		else if (strcmp(argv[0], "gravity") == 0) {
			try {
				m_gravity = std::stod(argv[1]);
				if (m_integration) {
					m_integration->gravity(m_gravity);
				}
				return TCL_OK;
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[gravity] %s", error.what());
				return TCL_ERROR;
			}
		}
		else if (strcmp(argv[0], "drag") == 0) {
			try {
				m_drag = std::stod(argv[1]);
				if (m_integration) {
					m_integration->drag(m_drag);
				}
				return TCL_OK;
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[drag] %s", error.what());
				return TCL_ERROR;
			}
		}
		else {
			animTcl::OutputMessage("[Spring Simulator] Error: Could not match command \"%s\" to any known"
				"spring commands\n", argv[0]);
			return TCL_ERROR;
		}
	}

	virtual int step(double time)
	{
		for (auto& p : m_particle_system->particles()) {
			if (!p.m_fixed) {
				m_integration->step(p);
			}
		}
		return 0;
	}

	virtual int init(double time)
	{
		return 0;
	}

private:
	BaseSystem* m_particle_system;
	double m_gravity, m_drag = 0.0;
	std::shared_ptr<Integration> m_integration;

	void link_system(BaseSystem* p_sys, std::size_t num_springs)
	{
		m_particle_system = p_sys;
	}

	void set_integration(const std::string& inte, const double step_size)
	{
		if (inte == "euler") {
			m_integration = std::make_shared<Euler>(step_size, m_particle_system->ground_plane());
		}
		else if (inte == "symplectic") {
			m_integration = std::make_shared<Symplectic>(step_size, m_particle_system->ground_plane());
		}
		else if (inte == "verlet") {
			m_integration = std::make_shared<Verlet>(step_size, m_particle_system->ground_plane());
		}
		else {
			throw std::runtime_error("Spring simulator does not support " + inte + " integration");
		}
		m_integration->gravity(m_gravity);
	}
};