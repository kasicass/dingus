#pragma once

namespace dingus { namespace stl_utils {

// Deletes items in pointer container
template <class T>
void wipe(T& container)
{
	for (T::iterator it = container.begin(); it != container.end(); ++it)
	{
		delete *it;
	}
	container.clear();
}

// Deletes values in map (values by pointers).
template <class T>
void wipe_map(T& map)
{
	for (T::iterator it = map.begin(); it != map.end(); ++it)
	{
		delete it->second;
	}
	map.clear();
}

}}
