/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <Scene.hpp>

#include <Platform.hpp>
#include <Column.hpp>
#include <Ground.hpp>
#include <Door.hpp>
#include <Tank.hpp>
#include <Wall.hpp>
#include <Key.hpp>

namespace bullet_3da
{
	/// Represents the custom Scene used for the demo
	class MyScene : public Scene
	{
		/// Used to keep track of the point of view.
		shared_ptr < Camera > camera;

		/// The Tank used in the scene.
		unique_ptr < Tank > tank;

		/// The Door used in the scene.
		shared_ptr < Door > door;

		/// Used to keep track of the tank's fire cooldown.
		std::clock_t time_fire;

		/// Used to keep track of the previous input.
		Tank::Controls controls;

		/// Set to true when the Door is open.
		bool door_opened;

	public:

		/// Builds the demos scene with all its components.
		MyScene();

		/// update is called on every frame.
		/// Now it's used to check for collissions between objects
		/// @param deltaTime Time since the previous frame.
		void update(float deltaTime) override;

		/// Performs the behaviour of all objects in the scene.
		/// @param input_data contains the input data from this frame.
		void processInput(Input::InputData input_data) override;
	};
}