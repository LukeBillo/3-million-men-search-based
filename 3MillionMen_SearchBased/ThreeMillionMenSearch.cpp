#include "ThreeMillionMenSearch.h"
#include <string>
#include <list>
#include <map>
#include <algorithm>


three_million_men_search::three_million_men_search(std::shared_ptr<std::map<std::string, std::string>>& name_mapping)
{
	_names = name_mapping;
	_results = std::make_unique<std::list<std::string>>();
}

void three_million_men_search::run()
{
	const auto starting_point = _names->begin();
	run_recursive_west(starting_point);
	run_recursive_east(starting_point);
}

void three_million_men_search::run_recursive_west(std::map<std::string, std::string>::iterator current_name_pair)
{
	_results->push_back(current_name_pair->first);
	const auto west_neighbour = _names->find(current_name_pair->second);

	// Reached western-most person, has no neighbour
	// as this is the back of the line.
	// Time to return East from the start.
	if (west_neighbour == _names->end())
	{
		_results->push_back(current_name_pair->second);
		return;
	}

	return run_recursive_west(west_neighbour);
}

void three_million_men_search::run_recursive_east(std::map<std::string, std::string>::iterator current_name_pair)
{
	// iterator init, allows return to be outside of for loop
	// for tail call optimisation
	const auto east_neighbour = std::find_if(_names->begin(), _names->end(), 
		[current_name_pair](const std::pair<std::string, std::string> name) { return name.second == current_name_pair->first; });

	if (east_neighbour == _names->end())
	{
		// end of the line!
		return;
	}

	_results->push_front(east_neighbour->first);
	return run_recursive_east(east_neighbour);
}

std::list<std::string>* three_million_men_search::get_results()
{
	return _results.release();
}
