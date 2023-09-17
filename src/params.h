#pragma once
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <typeindex>


//Instead of comparing two parameter packs, which can't be defined, we compare two tuples.
template<typename TTuple, typename UTuple, std::size_t... Indices>
static constexpr bool is_convertible_tuple(std::index_sequence<Indices...>) {
	return
		// Parameter counts match
		std::tuple_size<TTuple>::value == std::tuple_size<UTuple>::value &&

		// All types are convertible
		(
			... &&
			std::is_convertible
			<
			std::tuple_element_t<Indices, TTuple>,
			std::tuple_element_t<Indices, UTuple>
			>::value
			);
}

template<typename TTuple, typename UTuple>
static constexpr bool is_convertible_tuple()
{
	return is_convertible_tuple<TTuple, UTuple>(std::make_index_sequence<std::tuple_size_v<TTuple>> {});
}

template <typename... T>
struct ConvertibleParameters
{

	template<typename... Params>
	static constexpr bool has_convertible_params = false;

	template<typename... Params>
	static constexpr bool has_convertible_params<Params...> =
		is_convertible_tuple<std::tuple<Params...>, std::tuple<T...>>();

};
