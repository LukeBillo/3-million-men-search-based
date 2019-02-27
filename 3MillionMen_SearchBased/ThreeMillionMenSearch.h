#pragma once
#include <memory>
#include <list>
#include <unordered_map>
#include <map>

class three_million_men_search
{
public:
	using name_map = std::map<std::string, std::string>;
	using name_list = std::list<std::string>;

	three_million_men_search(std::unique_ptr<name_map>&);
	~three_million_men_search() = default;

	void run();
	std::list<std::string>* get_results();

private:
	std::unique_ptr<name_map> _names_by_key;
	std::unique_ptr<name_map> _names_by_value;
	std::unique_ptr<name_list> _results;

	void run_recursive_west(name_map::iterator current_name_pair);
	void run_recursive_east(name_map::iterator current_name_pair);
};

