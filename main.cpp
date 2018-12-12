#include <iostream>
#include <string>
#include <algorithm>
#include "src/utils.hpp"
#include "src/EcsComponent.hpp"
#include "src/EcsCore.hpp"
#include "src/Position.hpp"
#include "src/EcsSystem.hpp"
#include "src/Math/Vector3.hpp"
#include "src/Math/common.hpp"
#include <cmath>

int main()
{

//	ECS::Core core{};
//
//	PositionComponent pos;
//	MovementComponent mov;
//	PositionShowSystem posSystem;
//	ECS::SystemList motionSystems;
//
//
//	pos.x = 10;
//	pos.y = 2;
//	motionSystems.addSystem(posSystem);
//	auto ent = core.makeEntity(MovementComponent{.x =10, .y= 10}, pos);
//	core.updateSystems(motionSystems, 0);

	Math3d::Vector3 vec1{-1, -1, 0};
	Math3d::Vector3 wall{0, 1, 0};

	std::cout << vec1 << std::endl;
	std::cout << Math3d::Vector3::reflect(vec1, wall) << std::endl;
}