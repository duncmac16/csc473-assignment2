#pragma once

#include "BaseSystem.h"
#include <memory>

class Spring;

class Particle{
public:
	double m_mass, m_radius, scale;
	Vector m_position, m_velocity, x_1;
	GLMmodel m_model;
	bool m_fixed = false;
	std::vector<std::shared_ptr<Spring>> m_springs;

	Particle()
	{
		m_mass = 1.0;
		m_radius = 1.0;
		scale = 0.1;
		setVector(m_position, 0.0, 0.0, 0.0);
		setVector(m_velocity, 0.0, 0.0, 0.0);
		VecCopy(x_1, m_position);
	}

	Particle(const double mass, const Vector position, const Vector velocity) : 
		m_mass{ mass }
	{
		VecCopy(m_position, position);
		VecCopy(m_velocity, velocity);
		VecCopy(x_1, m_position);
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
		glTranslated(m_position[0], m_position[1], m_position[2] - 40.55);
		glScaled(scale, scale, scale);

		/*glBegin(GL_POINTS);
			glVertex3d(m_position[0], m_position[1], m_position[1]);
		glEnd();*/

		GLdrawSphere(m_radius, m_position);

		glPopAttrib();
		glPopMatrix();
	}	
};