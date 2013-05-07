#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <iostream>
using namespace std;

namespace Graphos
{
	namespace Math
	{
		struct Vector2
		{
		public:
			Vector2( const float values[ 2 ] ) : x( values[ 0 ] ), y( values[ 1 ] ) { }
			Vector2( float x = 0.0f, float y = 0.0f ) : x( x ), y( y ) { }
			Vector2( const Vector2& other ) : x( other.x ), y( other.y ) { }

			float operator[]( const int index ) const
			{
				return *( &x + index );
			}

			Vector2& operator=( const Vector2& other )
			{
				if( &other != this )
				{
					x = other.x;
					y = other.y;
				}

				return *this;
			}

			Vector2 operator+( const Vector2& other ) const
			{
				return Vector2( x + other.x, y + other.y );
			}

			Vector2 operator-( const Vector2& other ) const
			{
				return Vector2( x - other.x, y - other.y );
			}

			float operator%( const Vector2& other ) const
			{
				return ( x * other.y ) - ( y * other.x );
			}

			float operator*( const Vector2& other ) const
			{
				return ( x * other.x ) + ( y * other.y );
			}

			Vector2 operator*( const float other ) const
			{
				return Vector2( x * other, y * other );
			}

			float Magnitude( void ) const
			{
				return sqrt( ( x * x ) + ( y * y ) );
			}

			Vector2 Normalize( void ) const
			{
				float mag = sqrt( ( x * x ) + ( y * y ) );

				return Vector2( x / mag, y / mag );
			}

			friend std::ostream& operator<<( std::ostream& os, const Vector2& vec )
			{
				os << "x: " << vec.x << " y: " << vec.y;

				return os;
			}

			float x, y;
		};
	}
}

#endif // _VECTOR2_H_