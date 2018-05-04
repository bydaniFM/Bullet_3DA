/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <OpenGL.hpp>

#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

namespace bullet_3da
{

	class View
	{
		shared_ptr<Window> window;

	public:

		View();
	};

}