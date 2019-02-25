#include "ThreeMillionMenSearch.h"
#include <string>
#include <list>
#include <map>
#include <algorithm>


three_million_men_search::three_million_men_search(std::unique_ptr<name_map>& name_mapping)
{
	_names_by_key = std::move(name_mapping);

	_names_by_value = std::make_unique<name_map>();
	for (auto i = _names_by_key->begin(); i != _names_by_key->end(); ++i)
	{
		_names_by_value->operator[](i->second) = i->first;
	}

	_results = std::make_unique<std::list<std::string>>();
}

void three_million_men_search::run()
{
	const auto starting_point = _names_by_key->begin();
	run_recursive_west(starting_point);

	const auto starting_point_east = _names_by_value->find(_results->front());
	if (starting_point_east == _names_by_value->end())
		return;

	run_recursive_east(starting_point_east);
}

void three_million_men_search::run_recursive_west(name_map::iterator current_name_pair)
{
	_results->push_back(current_name_pair->first);
	const auto west_neighbour = _names_by_key->find(current_name_pair->second);

	// Reached western-most person, has no neighbour
	// as this is the back of the line.
	// Time to return East from the start.
	if (west_neighbour == _names_by_key->end())
	{
		_results->push_back(current_name_pair->second);
		return;
	}

	_names_by_key->erase(current_name_pair);

	return run_recursive_west(west_neighbour);
}

void three_million_men_search::run_recursive_east(name_map::iterator current_name_pair)
{
	_results->push_front(current_name_pair->second);

	const auto east_neighbour = _names_by_value->find(current_name_pair->second);
	_names_by_value->erase(current_name_pair);

	if (east_neighbour == _names_by_value->end())
	{
		// end of the line!
		return;
	}

	return run_recursive_east(east_neighbour);
}

std::list<std::string>* three_million_men_search::get_results()
{
	return _results.release();
}
