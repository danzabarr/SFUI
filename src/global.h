#pragma once

#include <unordered_map>
#include <string>
#include <functional>

namespace sfui
{
	template <typename T>
	class GlobalModel
	{
	private:
		static std::unordered_map<std::string, std::pair<T, std::vector<std::function<void(T)>>>> binds;

	public:
		static inline void notify(const std::string& name, T value)
		{
			if (binds.find(name) != binds.end())
			{
				binds[name].first = value;
				for (std::function<void(T)> callback : binds[name].second)
					callback(value);
			}
		}

		static inline T listen(const std::string& name, std::function<void(T)> callback)
		{
			std::pair<T, std::vector<std::function<void(T)>>> callbacks;
			if (binds.find(name) != binds.end())
				callbacks = binds[name];

			callbacks.second.push_back(callback);
			binds[name] = callbacks;

			return callbacks.first;
		}

		static inline T get(const std::string& name)
		{
			if (binds.find(name) != binds.end())
				return binds[name].first;

			return T();
		}
	};

	template <typename T>
	std::unordered_map<std::string, std::pair<T, std::vector<std::function<void(T)>>>> GlobalModel<T>::binds;
}
