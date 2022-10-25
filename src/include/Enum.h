#pragma once
#include <string>
#include <map>

namespace Enum
{
	namespace SurfaceType
	{
		enum Value {
			Smooth = 0, Bumps = 1, Hinge = 2, Motor = 3, StepperMotor = 4, Spawn = 5
		};
		static std::pair<std::string, Value> map_data[] = {
			std::make_pair("Smooth", Smooth),
			std::make_pair("Bumps", Bumps),
			std::make_pair("Hinge", Hinge),
			std::make_pair("Motor", Motor),
			std::make_pair("StepperMotor", StepperMotor),
			std::make_pair("Spawn", Spawn)
		};
		static std::map<std::string, Value> nameMap(map_data,
		map_data + sizeof map_data / sizeof map_data[0]);

		static Value getByName(std::string name) {
			if(nameMap.find(name) != nameMap.end()){
				return nameMap[name];
			}
			return Smooth;
		}

		static std::string getName(Value value) {
			for (std::map<std::string, Value>::iterator it = nameMap.begin(); it != nameMap.end(); ++it)
				if (it->second == value)
					return it->first;
			return "";
		}
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