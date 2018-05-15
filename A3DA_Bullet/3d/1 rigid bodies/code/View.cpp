

#include <View.hpp>

namespace bullet_3da
{

	View::View()
	{
		this->window = make_shared<Window>
		(
			sf::VideoMode(1024, 720),
			"Bullet Rigid Bodies",
			sf::Style::Default,
			sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      // Se usa OpenGL 3.2 core profile
		);

		// Se determinan las características de OpenGL disponibles en la máquina:

		if (!glt::initialize_opengl_extensions())
		{
			exit(-1);
		}

		// Se activa la sincronización vertical:

		this->window->setVerticalSyncEnabled(true);
	}

	void View::reset_viewport(Scene & scene)
	{
		GLsizei width = GLsizei(window->getSize().x);
		GLsizei height = GLsizei(window->getSize().y);

		scene.get_graphics_scene()->get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);
	}

}