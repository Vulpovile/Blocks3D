#pragma once

namespace Enum
{
	namespace SurfaceType
	{
		static const char* STR_TABLE[] = {
			"Smooth", "Bumps", "Hinge", 
			"Motor", "StepperMotor", "Spawn"
		};
		enum Value {
			Smooth = 0, Bumps = 1, Hinge = 2, Motor = 3, StepperMotor = 4, Spawn = 5, LENGTH = 6
		};
		
	}
	namespace Shape
	{
		static const char* STR_TABLE[] = {
			"Ball", "Block", "Cylinder"
		};
		enum Value {
			Ball = 0, Block = 1, Cylinder = 2, LENGTH = 3
		};
	}
	namespace Controller
	{
		static const char* STR_TABLE[] = {
			"None", "KeyboardRight", "KeyboardLeft", "Joypad1", 
			"Joypad2", "Chase", "Flee"
		};
		enum Value {
			None = 0, KeyboardRight = 1, KeyboardLeft = 2, Joypad1 = 3, Joypad2 = 4, Chase = 5, Flee = 6, LENGTH=7
		};
	}
	namespace ActionType
	{
		static const char* STR_TABLE[] = {
			"Nothing", "Pause", "Lose", "Draw", "Win"
		};
		enum Value {
			Nothing = 0, Pause = 1, Lose = 2, Draw = 3, Win = 4, LENGTH = 5
		};
	}
	namespace AffectType
	{
		static const char* STR_TABLE[] = {
			"NoChange", "Increase", "Decrease"
		};
		enum Value {
			NoChange = 0, Increase = 1, Decrease = 2, LENGTH = 3
		};
	}
	namespace Sound
	{
		static const char* STR_TABLE[] = {
			"NoSound", "Victory", "Boing", "Bomb", 
			"Ping", "Break", "Splat", "Swoosh", 
			"Snap", "Page", "Click", "Clock", "Step", "StepOn"
		};
		enum Value {
			NoSound = 0, Victory = 1, Boing = 2, Bomb = 3, 
			Ping = 4, Break = 5, Splat = 6, Swoosh = 7, 
			Snap = 8, Page = 9, Click = 10, Clock = 11, Step = 12, StepOn = 13,
			LENGTH = 14
		};
	}
}