#include "SphereCollider.h"

using namespace Graphos;

SphereCollider::SphereCollider( GameObject* owner ) : Collider( Sphere, owner ) { }

const Vector3 SphereCollider::GetFurthestPointInDirection( const Vector3& direction ) const
{
	return owner->transform.Position() + centerOffset + ( direction.Normalize() * radius );
}