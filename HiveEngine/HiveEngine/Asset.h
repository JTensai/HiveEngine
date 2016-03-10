#pragma once

#include <vector>

namespace Hive
{
	class AssetLoadException : public std::exception
	{
	public:
		AssetLoadException(std::string err) : err(err) {};
		std::string err;
	};

	template <class T, class D>
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

	template <class T, class D>
	void AssetData<T, D>::setFilepath(std::string str)
	{
		filepath = str;
	}

	template <class T, class D>
	const T* AssetData<T, D>::getAsset()
	{
		if (isLoaded && asset != nullptr)
		{
			return asset;
		}
		asset = new T(filepath, static_cast<D*>(this));
		if (asset == nullptr) throw AssetLoadException("Unable to load asset: " + filepath);
		isLoaded = true;
		return asset;
	}
}