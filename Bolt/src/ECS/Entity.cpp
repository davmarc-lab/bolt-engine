#include <vcruntime_typeinfo.h>
#include <ECS/Entity.hpp>

namespace Bolt {
	template <class T>
	const b8& Entity::removeSingleComponent() { return false; }
}
