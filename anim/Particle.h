#pragma once

#include "BaseSystem.h"

class Particle{
public:
	Particle()
	{
		m_mass = 1.0;
		setVector(m_position, 0.0, 0.0, 0.0);
		setVector(m_velocity, 0.0, 0.0, 0.0);
	}

	Particle(const double mass, const Vector position, const Vector velocity) : 
		m_mass{ mass }
	{
		VecCopy(m_position, position);
		VecCopy(m_velocity, velocity);
	}

	void set_velocity(const Vector v)
	{
		VecCopy(m_velocity, v);
	}

	void set_position(const Vector p)
	{
		VecCopy(m_position, p);
	}

	void set_mass(const double mass)
	{
		m_mass = mass;
	}

	void display(GLenum mode = GL_RENDER)
	{
		glEnable(GL_LIGHTING);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glTranslated(m_position[0], m_position[1], m_position[2]);
		glScaled(0.1f, 0.1f, 0.1f);

		glmDraw(&m_model, GL_POINT);

		glPopAttrib();
		glPopMatrix();
	}

private:
	double m_mass;
	Vector m_position, m_velocity;
	GLMmodel m_model;
	bool m_fixed;
};