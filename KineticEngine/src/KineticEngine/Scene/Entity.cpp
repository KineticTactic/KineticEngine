#include "kepch.h"
#include "Entity.h"

namespace KE {

	Entity::Entity(entt::entity entityHandle, Scene* scene)
		:m_EntityHandle(entityHandle), m_Scene(scene) {

	}

}