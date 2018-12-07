/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 02/12/18
*/

#include "CollisionEngine.hpp"

void CollisionEngine::onMakeEntity(ECS::EntityHandler entity)
{
	entities.push_back(entity);
}

void CollisionEngine::onRemoveEntity(ECS::EntityHandler entity)
{
	entitiesToRemove.push_back(entity);
}

void CollisionEngine::onAddComponent(ECS::EntityHandler entity, ECS::CompTypeId id)
{
	if (id == TransformComponent::TypeId) {
		if(core_ecs.getComponent<ColliderComponent>(entity) != nullptr)
			entities.push_back(entity);
	} else if(id == ColliderComponent::TypeId) {
		if(core_ecs.getComponent<TransformComponent>(entity) != nullptr)
			entities.push_back(entity);
	} else if(core_ecs.getComponent<ColliderComponent>(entity) != nullptr
	        && core_ecs.getComponent<TransformComponent>(entity) != nullptr)
		entities.push_back(entity);
}

void CollisionEngine::onRemoveComponent(ECS::EntityHandler entity, ECS::CompTypeId id)
{
	if (id == TransformComponent::TypeId || id == ColliderComponent::TypeId)
		entitiesToRemove.push_back(entity);
}

void CollisionEngine::processInteractions(float delta)
{
	(void)(delta);
//	auto newEnd = std::remove_if(R_ENTIRE(entities), [this](ECS::EntityHandler entity){
//		return std::find(R_ENTIRE(entitiesToRemove), entity) != entitiesToRemove.end();
//	});
//	entities.erase(newEnd, entities.end());
//
//	std::sort(R_ENTIRE(entities), [this](ECS::EntityHandler a, ECS::EntityHandler b){
//		float aMin = core_ecs.getComponent<ColliderComponent>(a)->boxCollider.getMinExtents()[compare_axis];
//		float bMin = core_ecs.getComponent<ColliderComponent>(b)->boxCollider.getMinExtents()[compare_axis];
//		return aMin < bMin;
//	});
//
//	Vector3f centerSum(0.0f);
//	Vector3f centerSqSum(0.0f);
//	std::for_each(R_ENTIRE(entities), [this, centerSum, centerSqSum] (ECS::EntityHandler entity) mutable {
//		AABB boxCollider = core_ecs.getComponent<ColliderComponent>(entity)->boxCollider;
//
//		centerSum += boxCollider.getCenter();
//		centerSqSum += (boxCollider.getCenter() * boxCollider.getCenter());
//		for (auto& otherEntity : entities) {
//			AABB otherBoxCollider = core_ecs.getComponent<ColliderComponent>(otherEntity)->boxCollider;
//			if (otherBoxCollider.getMaxExtents()[compare_axis] > boxCollider.getMaxExtents()[compare_axis])
//				break;
//			if (boxCollider.intersects(otherBoxCollider)) {
//				//do something
//			}
//		}
//	});
//
//	//set max variance and max var axis
//	centerSum /= entities.size();
//	centerSqSum /= entities.size();
//	Vector3f variance = centerSqSum - (centerSum * centerSum);
//	float maxVar = variance[0];
//	compare_axis = 0;
//	if (variance[1] > maxVar) {
//		maxVar = variance[1];
//		compare_axis = 1;
//	}
//	if (variance[2] > maxVar) {
//		maxVar = variance[2];
//		compare_axis = 2;
//	}
}
