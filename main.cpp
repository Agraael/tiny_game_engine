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

	Math3d::Vector3 vec1{10, 0, 10};
//	Math3d::Vector3 vec2{0, 1, 0};

	std::cout << vec1 << std::endl;
	std::cout << vec1.magnitude() << std::endl;
	std::cout << vec1.angleXY() << std::endl;

	vec1.rotateXY(Math3d::degreeToRadian(90));
//	vec1.x = 0;
//	vec1.y = 10;

	std::cout << vec1 << std::endl;
	std::cout << vec1.magnitude() << std::endl;
	std::cout << vec1.angleXY() << std::endl;
}