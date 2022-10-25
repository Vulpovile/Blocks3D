#pragma once

namespace Enum
{
	class B3DEnum {
		public:
			B3DEnum(int id, std::string name)
			{
				this->id = id;
				this->name = name;
			}
			const int getId() {
				return id;
			}
			const std::string getName() {
				return name;
			}
			virtual B3DEnum getByName(std::string name);
			virtual B3DEnum getById(int id);
		private:
			int id;
			std::string name;
	}
}