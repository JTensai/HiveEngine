#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Hive
{
	struct ParticleSystem {
		std::string id;
		std::vector<std::string> emittersIDs[];
	};
	struct ParticleEmitter {
		std::string id;
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

	struct Module {
		std::string id;
	};
	struct ModuleSizeOverLife: Module {
		float beinningFactor;
		float endFactor;
	};
	struct ModuleColorOverLife: Module {
		glm::vec4 beginningColor;
		glm::vec4 endColor;
	};
	struct ModuleInitialRotation: Module {
		float min;
		float max;
	};
	struct ModuleInitialRotationRate: Module {
		float min;
		float max;
	};
	struct ModuleSubImageIndexOverLife: Module{
		int beginningIndex;
		int endIndex;
	};
	struct ModuleSubImageIndexRandom: Module {
		int beginningIndex;
		int endIndex;
	};
}
