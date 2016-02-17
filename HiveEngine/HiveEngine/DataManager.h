#pragma once

#include <string>
#include <functional>

#include <tinyxml2/tinyxml2.h>

#include "IDataManager.h"
#include "DataCollection.h"
#include "XMLInterface.h"

namespace Hive
{

	class DataManager : public IDataManager
	{
	private:
		DataCollection<DAbility> _dAbilities;
		DataCollection<DActor> _dActors;
		DataCollection<DBehavior> _dBehaviors;
		DataCollection<DEffect> _dEffects;
		DataCollection<DUnit> _dUnits;
		DataCollection<DValidator> _dValidators;

		DataCollection<Shader> _shaders;
		DataCollection<GLuint> _vertexShaders;
		DataCollection<GLuint> _fragmentShaders;
		DataCollection<Texture> _textures;
		DataCollection<Mesh> _meshes;
		DataCollection<Model> _models;

#pragma region XML Functions
		void xmlFirstPass(XMLInterface& xmlif);

		void xmlFirstPassAbilities(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassActors(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassBehaviors(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassEffect(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassModels(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassUnits(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassValidator(XMLInterface::XMLIterator xmliter);

		void xmlSecondPass(XMLInterface& xmlif);

		void xmlSecondPassAbilities(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassActors(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassBehaviors(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassEffectModifyUnit(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSearch(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSet(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSetBehavior(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSpawnUnit(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSwitch(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassModels(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassUnits(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassValidatorBehaviorCount(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorCombine(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorCompareVital(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorCondition(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorLocationRange(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorLocationPathable(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorFilterUnit(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorPlayer(XMLInterface::XMLIterator xmliter);


		void xmlParseVitals(XMLInterface::XMLIterator iter, Vitals* vitals);
		void xmlParseCharges(XMLInterface::XMLIterator iter, Charges* charges);
		void xmlParseCost(XMLInterface::XMLIterator iter, Cost* cost);
		void xmlParseEffectList(XMLInterface::XMLIterator iter, EffectList* effects);
		void xmlParseFilter(XMLInterface::XMLIterator iter, Filter* filter);
		void xmlParseUnitFilter(XMLInterface::XMLIterator iter, UnitFilter* filter);

		void xmlParseTexture(XMLInterface::XMLIterator iter, int* texHandle);
		void xmlParseModel(XMLInterface::XMLIterator iter, int* modelHandle);
		void xmlParseShader(XMLInterface::XMLIterator iter, int* shaderHandle);
#pragma endregion

	public:
		DataManager();

		int loadCoreData();
		int loadXMLData(char* filename);

		DAbility* getAbilityData(int handle);
		DActor* getActorData(int handle);
		DBehavior* getBehaviorData(int handle);
		DEffect* getEffectData(int handle);
		DUnit* getUnitData(int handle);
		DValidator* getValidatorData(int handle);

		int getShaderHandle(const std::string vertexShader, const std::string fragmentShader);
		Shader* getShader(int handle);
		GLuint getVertexShader(int handle);
		GLuint getFragmentShader(int handle);

		int getModelHandle(const std::string filename);
		Model* getModel(int handle);

		Mesh* getMesh(int handle);

		int getTextureHandle(const std::string filename);
		Texture* getTexture(int handle);

		~DataManager();
	};

}