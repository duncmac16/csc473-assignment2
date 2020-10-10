#pragma once

#include "BaseSystem.h"
#include "BaseObject.h"
#include "Particle.h"

#include <vector>

class ParticleSystem: public BaseSystem {
public:
	ParticleSystem(const std::string& name) :
		BaseSystem{ name }, m_max{ 10 }
	{
		for (std::size_t i{ 0 }; i < m_max; ++i) {
			particles.push_back(Particle{});
		}
	}

	int command(int argc, myCONST_SPEC char** argv)
	{
		if (strcmp(argv[0], "dim") == 0) {
			try {
				set_max(std::stod(argv[1]));
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[dim] Error: %s", error.what());
			}
		}
		else if (strcmp(argv[0], "particle") == 0) {
			try {
				Vector pos, vel;
				std::size_t i{ std::stoi(argv[1]) };
				double mass{ std::stod(argv[2]) };
				setVector(pos, std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]));
				setVector(vel, std::stod(argv[6]), std::stod(argv[7]), std::stod(argv[8]));
				set_particle(i, mass, pos, vel);
			}
			catch (const std::exception& error) {
				animTcl::OutputMessage("[particle] Error: %s", error.what());
			}
		}
		else if (strcmp(argv[0], "all_velocities") == 0) {

		} 
	}

	void display(GLenum mode = GL_RENDER)
	{
		for (auto& p : particles){
			p.display(mode);
		}
	}

private:
	std::size_t m_max;
	std::vector<Particle> particles;

	void set_max(const std::size_t max)
	{
		m_max = max;
		particles.clear();
		for (std::size_t i{ 0 }; i < max; ++i) {
			particles.push_back(Particle{});
		}
	}

	void set_particle(const std::size_t& i, const double& mass,
		const Vector position, const Vector velocity)
	{
		particles[i].set_mass(mass);
		particles[i].set_position(position);
		particles[i].set_velocity(velocity);
	}

	void all_velocities(const Vector v)
	{
		for (auto& p : particles) {
			p.set_velocity(v);
		}
	}
};