/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <OpenGL.hpp>

#include <SFML/Window.hpp>

#include <Scene.hpp>

using namespace std;
using namespace sf;

namespace bullet_3da
{
	/// Encapsulates a SFML Window.
	class View
	{
		/// Window of the application.
		shared_ptr<Window> window;

	public:

		/// Creates a new view.
		View();

		void reset_viewport(Scene & scene);

		shared_ptr<Window> getWindow()
		{
			return window;
		}

	};

}