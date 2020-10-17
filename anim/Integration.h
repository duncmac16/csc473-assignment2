#pragma once

#include "Particle.h"
#include "GroundPlane.h"

class Integration {
public:
	Integration(const double time_step, GroundPlane& gp) :
		m_step_size{ time_step }, m_ground_plane{ gp } {}

	virtual void step(Particle& p) = 0;
	virtual void gravity(const double& gravity) { m_gravity = gravity; }
	virtual void drag(const double& drag) { m_drag = drag; }
	virtual void ground_plane(const GroundPlane& gp) { m_ground_plane = gp; }

	virtual void force(Particle& p, Vector force)
	{
		double gf = p.m_mass * m_gravity;
		setVector(force, 0.0, gf, 0.0);
		for (const auto& s : p.m_springs) {
			s->force(p, force);
		}
		Vector momentum;
		VecCopy(momentum, p.m_velocity);
		VecScale(momentum, p.m_mass);
		VecAdd(force, force, momentum);
		m_ground_plane.force(p, force);
	}

protected:
	double m_step_size, m_gravity, m_drag = 0.0;
	GroundPlane m_ground_plane;
};

class Euler : public Integration {
public:
	Euler(const double time_step, GroundPlane gp) :
		Integration{ time_step, gp } {}

	virtual void step(Particle& p)
	{
		Vector vi, acc;
		// Acceleration Forces
		force(p, acc);
		VecScale(acc, m_step_size / p.m_mass);
		VecCopy(vi, p.m_velocity);
		VecAdd(p.m_velocity, p.m_velocity, acc);
		// Applying drag
		VecScale(vi, m_step_size * (1.0 - m_drag));
		VecAdd(p.m_position, p.m_position, vi);
	}
};

class Symplectic : public Integration {
public:
	Symplectic(const double time_step, GroundPlane gp) :
		Integration{ time_step, gp } {}

	virtual void step(Particle& p)
	{
		Vector vivd, acc;
		force(p, acc);
		VecScale(acc, m_step_size / p.m_mass);
		VecAdd(p.m_velocity, p.m_velocity, acc);
		VecCopy(vivd, p.m_velocity);
		VecScale(vivd, m_step_size * (1.0 - m_drag));
		VecAdd(p.m_position, p.m_position, vivd);
	}
};

class Verlet : public Integration {
public:
	Verlet(const double time_step, GroundPlane gp) :
		Integration{ time_step, gp } {}

	virtual void step(Particle& p)
	{
		Vector t1, t2, t3, num, x_1;
		force(p, t3);
		VecScale(t3, m_step_size * m_step_size);
		VecCopy(t1, p.m_position);
		VecScale(t1, 2.0);
		VecSubtract(t2, t1, p.x_1);
		VecCopy(x_1, p.x_1);
		VecCopy(p.x_1, p.m_position);
		VecAdd(p.m_position, t2, t3);
		VecSubtract(num, p.m_position, x_1);
		VecCopy(p.m_velocity, num);
		VecScale(p.m_velocity, 2 * m_step_size);
	}
};