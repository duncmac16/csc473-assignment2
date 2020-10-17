#pragma once

#include <vector>
#include "Particle.h"

class Spring {
public:
	Particle* m_p1, * m_p2;
	double m_ks, m_kd, m_rest_len;

	Spring(Particle* p1 = NULL, Particle* p2 = NULL, const double ks = 1.0, const double kd = 1.0, const double rest_len = 1.0) :
		m_p1{ p1 }, m_p2{ p2 }, m_ks{ ks }, m_kd{ kd }, m_rest_len{ rest_len } {}

	void force(const Particle& p, Vector force)
	{
		int point{ 0 };
		if (&p == m_p1) {
			point = 1;
		}
		else if (&p == m_p2) {
			animTcl::OutputMessage("point 2");
			point = 2;
		}
		else {
			animTcl::OutputMessage("Neither points");
		}
		f_ks(p, force, point);
		f_kd(p, force, point);
	}

	void display(GLenum mode = GL_RENDER)
	{
		glEnable(GL_LIGHTING);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glBegin(GL_LINES);
			glVertex3d(m_p1->m_position[0], m_p1->m_position[1], m_p1->m_position[2] - 40.0);
			glVertex3d(m_p2->m_position[0], m_p2->m_position[1], m_p2->m_position[2] - 40.0);
		glEnd();

		glPopAttrib();
		glPopMatrix();
	}

private:
	void f_ks(const Particle& p, Vector force, int point)
	{
		Vector dist_vec;
		const double dist_mag = spring_len(dist_vec, point);
		VecScale(dist_vec, m_ks * (m_rest_len * dist_mag) / dist_mag);
		VecAdd(force, force, dist_vec);
	}

	void f_kd(const Particle& p, Vector force, int point)
	{
		Vector dist_vec, vel_diff;
		const double dist_mag = spring_len(dist_vec, point);
		VecScale(dist_vec, 1.0 / dist_mag);
		if (point == 1) {
			VecSubtract(vel_diff, m_p1->m_velocity, m_p2->m_velocity);
		}
		else if (point == 2) {
			VecSubtract(vel_diff, m_p2->m_velocity, m_p1->m_velocity);
		}
		double dot = VecDotProd(vel_diff, dist_vec);
		VecScale(dist_vec, dot * -m_kd);
		VecAdd(force, force, dist_vec);
	}

	double spring_len(Vector dist_vec, int point) const
	{
		if (point == 1) {
			VecSubtract(dist_vec, m_p2->m_position, m_p1->m_position);
		}
		else if (point == 2) {
			VecSubtract(dist_vec, m_p1->m_position, m_p2->m_position);
		}
		return magnitude(dist_vec);
	}

	double magnitude(const Vector v) const 
	{
		return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}
};