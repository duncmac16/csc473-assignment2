#pragma once

#include "BaseSystem.h"
#include "BaseObject.h"
#include "Particle.h"
#include "Spring.h"
#include "GroundPlane.h"

#include <vector>

class ParticleSystem : public BaseSystem {
public:
	ParticleSystem(const std::string& name) :
		BaseSystem{ name }, m_max{ 0 }
	{
		for (std::size_t i{ 0 }; i < m_max; ++i) {
			m_particles.push_back(Particle{});
		}
	}

	int command(int argc, myCONST_SPEC char** argv)
	{
		if (strcmp(argv[0], "dim") == 0) {
			try {
				set_max(std::stod(argv[1]));
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[dim] Error: %s\n", error.what());
				return TCL_ERROR;
			}
			return TCL_OK;
		}
		else if (strcmp(argv[0], "particle") == 0) {
			try {
				Vector pos, vel;
				std::size_t i{ static_cast<std::size_t>(std::stoi(argv[1])) };
				double mass{ std::stod(argv[2]) };
				setVector(pos, std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]));
				setVector(vel, std::stod(argv[6]), std::stod(argv[7]), std::stod(argv[8]));
				set_particle(i, mass, pos, vel);
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[particle] Error: %s\n", error.what());
				return TCL_ERROR;
			}
			return TCL_OK;
		}
		else if (strcmp(argv[0], "all_velocities") == 0) {
			Vector vel;
			try {
				setVector(vel, std::stod(argv[1]), std::stod(argv[2]), std::stod(argv[3]));
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[all_velocities] Error: %s\n", error.what());
				return TCL_ERROR;
			}
			for (auto& p : m_particles) {
				p.set_velocity(vel);
			}
			return TCL_OK;
		}
		else {
			animTcl::OutputMessage("[Particle System] Error: Could not match command \"%s\" to any known commands\n",
				argv[0]);
			return TCL_ERROR;
		}
	}

	void display(GLenum mode = GL_RENDER)
	{
		for (auto& p : m_particles) {
			p.display(mode);
		}
		for (auto& s : m_springs) {
			s->display(mode);
		}
		m_ground_plane.display(mode);
	}

	virtual std::vector<Particle>& particles() override {
		return m_particles;
	}

	virtual void set_spring(std::size_t p1, std::size_t p2, double ks, double kd, double rest_len) override
	{
		std::shared_ptr<Spring> s = std::make_shared<Spring>(&m_particles[p1], &m_particles[p2], ks, kd, rest_len);
		m_particles[p1].m_springs.push_back(s);
		m_particles[p2].m_springs.push_back(s);
		m_springs.push_back(s);
	}

	virtual std::vector<std::shared_ptr<Spring>>& springs() override { return m_springs; }

	virtual GroundPlane& ground_plane() override { return m_ground_plane; }


private:
	std::size_t m_max;
	std::vector<Particle> m_particles;
	std::vector<std::shared_ptr<Spring>> m_springs;
	GroundPlane m_ground_plane;


	void set_max(const std::size_t max)
	{
		m_max = max;
		m_particles.clear();
		for (std::size_t i{ 0 }; i < max; ++i) {
			m_particles.push_back(Particle{});
		}
	}

	void set_particle(const std::size_t& i, const double& mass,
		const Vector position, const Vector velocity)
	{
		m_particles[i].set_mass(mass);
		m_particles[i].set_position(position);
		m_particles[i].set_velocity(velocity);
	}

	void all_velocities(const Vector v)
	{
		for (auto& p : m_particles) {
			p.set_velocity(v);
		}
	}
};