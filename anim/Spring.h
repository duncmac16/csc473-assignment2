#pragma once

#include <vector>
#include "Particle.h"

class Spring {
public:
	Particle* m_p1, * m_p2;
	double m_ks, m_kd, m_rest_len;

	Spring(Particle* p1 = NULL, Particle* p2 = NULL, const double ks = 1.0, const double kd = 1.0, const double rest_len = 1.0) :
		m_p1{ p1 }, m_p2{ p2 }, m_ks{ ks }, m_kd{ kd }, m_rest_len{ rest_len } {}

	void display(GLenum mode = GL_RENDER)
	{
		glEnable(GL_LIGHTING);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glBegin(GL_LINE);
			glVertex3d(m_p1->m_position[0], m_p1->m_position[1], m_p1->m_position[1]);
			glVertex3d(m_p2->m_position[0], m_p2->m_position[1], m_p2->m_position[1]);
		glEnd();

		glPopAttrib();
		glPopMatrix();
	}
};