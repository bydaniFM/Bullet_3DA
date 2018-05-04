

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

		// Se determinan las caracter�sticas de OpenGL disponibles en la m�quina:

		if (!glt::initialize_opengl_extensions())
		{
			exit(-1);
		}

		// Se activa la sincronizaci�n vertical:

		this->window->setVerticalSyncEnabled(true);
	}

}