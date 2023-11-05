			//Operator Overloads
			T operator()()
			{
				return *value;
			}
			//Assignment Operators
			T operator=(T nVal)
			{
				(*value) = nVal;
				return *value;
			}

			T operator+=(T nVal)
			{
				(*value) += nVal;
				return *value;
			}

			T operator-=(T nVal)
			{
				(*value)-= nVal;
				return *value;
			}

			T operator/=(T nVal)
			{
				(*value) /= nVal;
				return *value;
			}
			
			T operator*=(T nVal)
			{
				(*value) *= nVal;
				return *value;
			}

			T operator%=(T nVal)
			{
				(*value) %= nVal;
				return *value;
			}

			T operator^=(T nVal)
			{
				(*value) ^= nVal;
				return *value;
			}

			T operator&=(T nVal)
			{
				(*value) &= nVal;
				return *value;
			}

			T operator|=(T nVal)
			{
				(*value) |= nVal;
				return *value;
			}

			T operator>>=(T nVal)
			{
				(*value) >>= nVal;
				return *value;
			}

			T operator<<=(T nVal)
			{
				(*value) <<= nVal;
				return *value;
			}


			//Mathematical Operations
			T operator+(T nVal)
			{
				return (*value) + nVal;
			}

			T operator-(T nVal)
			{
				return (*value) - nVal;
			}

			T operator*(T nVal)
			{
				return (*value) - nVal;
			}

			T operator/(T nVal)
			{
				return (*value) / nVal;
			}

			T operator%(T nVal)
			{
				return (*value) % nVal;
			}

			//Boolean operations
			bool operator==(T nVal)
			{
				return (*value) == nVal;
			}

			bool operator!=(T nVal)
			{
				return (*value) != nVal;
			}

			bool operator<(T nVal)
			{
				return (*value) < nVal;
			}

			bool operator<=(T nVal)
			{
				return (*value) <= nVal;
			}

			bool operator>(T nVal)
			{
				return (*value) > nVal;
			}

			bool operator>=(T nVal)
			{
				return (*value) >= nVal;
			}

			T operator&&(T nVal)
			{
				return (*value) && nVal;
			}

			T operator||(T nVal)
			{
				return (*value) && nVal;
			}

			T operator!()
			{
				return !(*value);
			}

			//Bitwise operations
			T operator&(T nVal)
			{
				return (*value) && nVal;
			}

			T operator|(T nVal)
			{
				return (*value) && nVal;
			}

			T operator>>(T nVal)
			{
				return (*value) >> nVal;
			}

			T operator<<(T nVal)
			{
				return (*value) << nVal;
			}

			T operator^(T nVal)
			{
				return (*value) ^ nVal;
			}

			T operator~()
			{
				return ~(*value);
			}