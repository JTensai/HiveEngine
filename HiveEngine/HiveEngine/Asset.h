#pragma once

#include <vector>

namespace Hive
{
	template <class T>
	class AssetData
	{
	private:
		bool isLoaded;
		std::string filepath;
		T* asset;

	public:
		void setFilepath(std::string str);
		const T* getAsset();
	};

	template <class T>
	void AssetData<T>::setFilepath(std::string str)
	{
		filepath = str;
	}

	template <class T>
	const T* AssetData<T>::getAsset()
	{
		if (isLoaded && asset != nullptr)
		{
			return asset;
		}
		asset = new T(filepath);
		if (asset == nullptr) throw std::exception(("Unable to load asset: " + filepath).c_str());
		isLoaded = true;
		return asset;
	}
}