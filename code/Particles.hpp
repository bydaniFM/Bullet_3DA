
#pragma once

#include <vector>

#include <Entity.hpp>


class Particle3D
{
	typedef glm::vec3 Point3f;

	bool alive;

	Point3f position;

public:

	Particle3D()
	{
		alive = true;
	}

	bool is_alive() const
	{
		return alive;
	}

	virtual bool   update(float delta_time) = 0;
	virtual size_t get_number_of_vertices() const = 0;
	virtual size_t update_vertices(vector< Point3f > & vertices, size_t start) = 0;
};

class Fire_Particle : public Particle3D
{
public:

	size_t get_number_of_vertices() const override
	{
		return 4;
	}
};

template< class PARTICLE >
class Particle_Emitter
{

	typedef PARTICLE Particle;

	vector< Particle > & particles;

public:

	Particle_Emitter(vector< Particle > & particles)
		:
		particles(particles)
	{
	}

	virtual void update(float time) = 0;

};

class Fire_Emitter : public Particle_Emitter< Fire_Particle >
{
public:

	void update(float time) override;

};

template< class PARTICLE, class EMITTER >
class Particle_System
{
	typedef PARTICLE Particle;
	typedef EMITTER  Emitter;

private:

	vector< Particle > particles;
	vector< Point3f  > vertices;

	Emitter emitter;

	size_t  vertex_count;

public:

	Particle_System(size_t number_of_particles)
		:
		particles(number_of_particles),
		emitter(particles)
	{
		vertex_count = 0;

		for (auto & particle : particles) vertex_count += particle.get_number_of_vertices();

		vertices.resize(vertex_count);

		glGenBuffers(1, vbo_id);
	}

	void update(float time)
	{
		emitter.update();

		vertex_count = 0;

		for (auto & particle : particles)
		{
			if (particle.is_alive())
			{
				if (particle.update(time))
				{
					vertex_count += particle.update_vertices(vertices, vertex_count);
				}
			}
		}
	}

	void render()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

		glBufferData
		(
			GL_ARRAY_BUFFER,
			vertex_count * sizeof(Point3f),
			vertices.data(),
			GL_DYNAMIC_DRAW
		);

		glDrawArrays(GL_TRIANGLES, 0, vertex_count);
	}

};

//int main()
//{
//	// CREAR VENTANA
//	// INICIALIZAR EL CONTEXTO GRÁFICO (GLEW o GLBINDING, etc.)
//
//	Particle_System< Fire_Particle, Fire_Emitter > particle_system;
//
//	// BUCLE PRINCIPAL
//
//	return 0;
//}
