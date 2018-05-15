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

	class View
	{
		shared_ptr<Window> window;

	public:

		View();

		void reset_viewport(Scene & scene);

		shared_ptr<Window> getWindow()
		{
			return window;
		}

	};

}