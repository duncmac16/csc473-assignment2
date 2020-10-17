#pragma once

#include <shared/opengl.h>
#include <shared/defs.h>
#include "Spring.h"
#include <memory>


class GroundPlane {
public:
	GroundPlane(double height = -1.0) :
		m_height{ height }
	{
		Particle* p = new Particle();
		setVector(p->m_position, 0.0, m_height, 0.0);
		m_spring.m_p1 = p;
		m_spring.m_rest_len = 0.0;
	}

	~GroundPlane()
	{
		delete m_spring.m_p1;
	}

	void ks(const double k)
	{
		m_spring.m_ks = k;
	}

	void kd(const double k)
	{
		m_spring.m_kd = k;
	}

	void force(Particle& p, Vector force)
	{
		double bottom = p.m_position[Y] - (p.m_radius * p.scale);
		if (bottom < m_height) {
			/*Vector bounce, up;
			setVector(up, 0.0, 1.0, 0.0);
			double dot = VecDotProd(up, p.m_velocity);
			double fkd = -m_kd * dot;
			double s = m_height - bottom;
			double fks = m_ks * s;
			setVector(bounce, 0.0, fks + fkd, 0.0);*/

			m_spring.m_p2 = &p;
			m_spring.m_p1->m_position[0] = p.m_position[0];
			m_spring.m_p1->m_position[2] = p.m_position[2];
			m_spring.force(p, force);
		}
	}

	void display(GLenum mode = GL_RENDER)
	{
		glEnable(GL_LIGHTING | GL_COLOR_MATERIAL);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glTranslated(0, m_height - 0.1, 0);
		glScaled(1.0f, 1.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glColorMaterial(GL_BACK, GL_SPECULAR);

		glBegin(GL_QUADS);
			glVertex3d(-100.0, 0.0, 100.0);
			glVertex3d(-100.0, 0.0, -100.0);
			glVertex3d(100.0, 0.0, -100.0);
			glVertex3d(100.0, 0.0, 100.0);
		glEnd();
		glDisable(GL_COLOR_MATERIAL);
		glPopAttrib();
		glPopMatrix();
	}

private:
	double m_height;
	Spring m_spring;
};
