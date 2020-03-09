#pragma once

namespace Enum
{
	namespace SurfaceType
	{
		enum Value {
			Smooth, Snaps, Inlets, Glue, Weld, Spawn, Hinge, Motor, Bumps
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
}