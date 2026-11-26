#pragma once

#include "Engine/EngineTypes.h"
#include "Chaos/ChaosEngineInterface.h"

namespace WeaponCollision
{
	constexpr ECollisionChannel WeaponChannel = ECC_GameTraceChannel1;
	constexpr EPhysicalSurface HeadSurface = SurfaceType1;
}