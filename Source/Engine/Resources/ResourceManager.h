#pragma once
#include "Core/StringHelper.h"
#include "Resources/Resource.h"
#include "Core/Singleton.h"
#include <string>
#include <map>
#include <iostream>

namespace viper {
	class ResourceManager : public Singleton<ResourceManager>{
	public:
		template<typename T, typename ... Args>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template<typename T, typename ... Args>
		inline res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};
	template<typename T, typename ... Args>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args)
	{
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
	}


	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args && ...args)
	{
		std::string key = tolower(id);

		auto iter = m_resources.find(key);
		//check if resource exists
		if (iter != m_resources.end()) {
			//get vaule in interator
			auto base = iter->second;
			//cast to data type T
			auto resource = std::dynamic_pointer_cast<T>(base);
			//check if cast was successful
			if (resource == nullptr) {
				std::cerr << "Resourece type mismatch: " << key << std::endl;
				return res_t<T>();
			}
			//return the derived resource
			return resource;
		}

		///load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Args>(args)...) == false) {
			std::cerr << "Cold not load resource: " << name << std::endl;
			return res_t<T>();
		}
		//add resourece to resource manager
		m_resources[key] = resource;

		return resource;
	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }

}
