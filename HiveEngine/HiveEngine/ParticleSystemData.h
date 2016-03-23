#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Hive
{
	class DParticleSystem : public DataCollection<DParticleSystem> 
	{
	public:
		std::vector<int> emitters_handles;
	};
	class DParticleEmitter : public DataCollection<DParticleEmitter>
	{
	public:
		std::string emitterName;
		std::string blendingMode;
		int texture_handle;
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
		std::vector<int> modules_handles;
	};
	class DModule
	{
	public:
		std::string moduleType;
	};
	class DModuleSizeOverLife: public DataCollection<DModuleSizeOverLife>, DModule
	{
	public:
		float beinningFactor;
		float endFactor;
	};
	class DModuleColorOverLife: public DataCollection<DModuleColorOverLife>, DModule
	{
	public:
		glm::vec4 beginningColor;
		glm::vec4 endColor;
	};
	class DModuleInitialRotation: public DataCollection<DModuleInitialRotation>, DModule
	{
	public:
		float min;
		float max;
	};
	class DModuleInitialRotationRate: public DataCollection<DModuleInitialRotationRate>, DModule
	{
	public:
		float min;
		float max;
	};
	class DModuleSubImageIndexOverLife: public DataCollection<DModuleSubImageIndexOverLife>, DModule
	{
	public:
		int beginningIndex;
		int endIndex;
	};
	class DModuleSubImageIndexRandom: public DataCollection<DModuleSubImageIndexRandom>, DModule
	{
	public:
		int min;
		int max;
	};
}
