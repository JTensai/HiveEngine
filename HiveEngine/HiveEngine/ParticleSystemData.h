#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Hive
{
	class ParticleSystem : public DataCollection<ParticleSystem> 
	{
	public:
		std::vector<std::string> emittersIDs;
	};
	class ParticleEmitter : public DataCollection<ParticleEmitter>
	{
	public:
		std::string emitterName;
		std::string blendingMode;
		std::string texture;
		glm::vec3 emitterLocalOrigin;
		glm::vec2 lifetime;
		glm::vec2 initialSize;
		glm::vec3 InitialVelocity;
		int constantRate;
		int burst;
		bool Looping;
		float EmitterDelay;
		int subImagesHorizontal;
		int subImagesVertical;
		std::vector<std::string> modulesIDs;
	};
	class ModuleSizeOverLife: public DataCollection<ModuleSizeOverLife>
	{
	public:
		float beinningFactor;
		float endFactor;
	};
	class ModuleColorOverLife: public DataCollection<ModuleColorOverLife>
	{
	public:
		glm::vec4 beginningColor;
		glm::vec4 endColor;
	};
	class ModuleInitialRotation: public DataCollection<ModuleInitialRotation>
	{
	public:
		float min;
		float max;
	};
	class ModuleInitialRotationRate: public DataCollection<ModuleInitialRotationRate>
	{
	public:
		float min;
		float max;
	};
	class ModuleSubImageIndexOverLife: public DataCollection<ModuleSubImageIndexOverLife>
	{
	public:
		int beginningIndex;
		int endIndex;
	};
	class ModuleSubImageIndexRandom: public DataCollection<ModuleSubImageIndexRandom>
	{
	public:
		int beginningIndex;
		int endIndex;
	};
}
