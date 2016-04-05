#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "DataCollection.h"
#include "Data.h"

namespace Hive
{
#pragma region Typedefs
	typedef Handle DParticleSystemHandle;
	typedef Handle DParticleEmitterHandle;
	typedef Handle DModuleHandle;
#pragma endregion
#pragma region Enums
	enum class ModuleType {
		SIZE_OVER_LIFE,
		COLOR_OVER_LIFE,
		INITIAL_ROTATION,
		INITIAL_ROTATION_RATE,
		SUB_IMAGE_INDEX_OVER_LIFE,
		SUB_IMAGE_INDEX_RANDOM
	};
#pragma endregion

	class DParticleSystem : public DataCollection<DParticleSystem> 
	{
	public:
		std::vector<DParticleEmitterHandle> emitters_handles;
	};
	class DParticleEmitter : public DataCollection<DParticleEmitter>
	{
	public:
		std::string emitterName;
		std::string blendingMode;
		DMaterialHandle mat_handle;
		glm::vec3 emitterLocalOrigin;
		glm::vec2 lifetime;
		glm::vec2 initialSize;
		glm::vec3 initialVelocity;
		int constantRate;
		int burst;
		bool looping;
		float emitterDelay;
		int subImagesHorizontal;
		int subImagesVertical;
		std::vector<DModuleHandle> modules_handles;
	};

	struct DModuleBase {
		ModuleType type;
	};

	class DModuleSizeOverLife : DModuleBase
	{
	public:
		float beinningFactor;
		float endFactor;
	};
	class DModuleColorOverLife : DModuleBase
	{
	public:
		glm::vec4 beginningColor;
		glm::vec4 endColor;
	};
	class DModuleInitialRotation : DModuleBase
	{
	public:
		float min;
		float max;
	};
	class DModuleInitialRotationRate : DModuleBase
	{
	public:
		float min;
		float max;
	};
	class DModuleSubImageIndexOverLife : DModuleBase
	{
	public:
		int beginningIndex;
		int endIndex;
	};
	class DModuleSubImageIndexRandom : DModuleBase
	{
	public:
		int min;
		int max;
	};

	union DModuleUnion
	{
		DModuleBase base;
		DModuleColorOverLife color_over_life;
		DModuleInitialRotation initial_rotation;
		DModuleInitialRotationRate initial_rotation_rate;
		DModuleSizeOverLife size_over_life;
		DModuleSubImageIndexOverLife sub_image_index_over_life;
		DModuleSubImageIndexRandom sub_image_index_random;

		DModuleUnion() {}
		DModuleUnion(const DModuleUnion& o)
		{
			switch (o.base.type)
			{
			case ModuleType::COLOR_OVER_LIFE:
				color_over_life = o.color_over_life;
				break;
			case ModuleType::INITIAL_ROTATION:
				initial_rotation = o.initial_rotation;
				break;
			case ModuleType::INITIAL_ROTATION_RATE:
				initial_rotation_rate = o.initial_rotation_rate;
				break;
			case ModuleType::SIZE_OVER_LIFE:
				size_over_life = o.size_over_life;
				break;
			case ModuleType::SUB_IMAGE_INDEX_OVER_LIFE:
				sub_image_index_over_life = o.sub_image_index_over_life;
				break;
			case ModuleType::SUB_IMAGE_INDEX_RANDOM:
				sub_image_index_random = o.sub_image_index_random;
				break;
			}
		}
		~DModuleUnion() {}
	};

	class DModule : public DataCollection<DModule>
	{
	public:
		DModuleUnion u;
	};
}
