#pragma once

namespace Enum
{
	namespace SurfaceType
	{
		enum Value {
			Smooth = 0, Bumps = 1, Hinge = 2, Motor = 3, StepperMotor = 4, Spawn = 5
		};
	}
	namespace Shape
	{
		enum Value {
			Ball = 0, Block = 1, Cylinder = 2
		};
	}
	namespace Controller
	{
		enum Value {
			Player = 7, KeyboardRight = 1, KeyboardLeft = 2, Joypad1 = 3, Joypad2 = 4, Chase = 5, Flee = 6, None = 0
		};
	}
	namespace ActionType
	{
		enum Value {
			Nothing = 0, Pause = 1, Lose = 2, Draw = 3, Win = 4
		};
	}
	namespace AffectType
	{
		enum Value {
			NoChange = 0, Increase = 1, Decrease = 2
		};
	}
	namespace Sound
	{
		enum Value {
			NoSound = 0, Victory = 1, Boing = 2, Bomb = 3, 
			Ping = 4, Break = 5, Splat = 6, Swoosh = 7, 
			Snap = 8, Page = 9
		};
	}
}