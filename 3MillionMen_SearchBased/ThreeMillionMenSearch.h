#pragma once
#include <memory>
#include <map>
#include <list>

class three_million_men_search
{
public:
	three_million_men_search(std::shared_ptr<std::map<std::string, std::string>>&);
	~three_million_men_search() = default;

	void run();
	std::list<std::string>* get_results();

private:
	std::shared_ptr<std::map<std::string, std::string>> _names;
	std::unique_ptr<std::list<std::string>> _results;

	void run_recursive_west(std::map<std::string, std::string>::iterator current_name_pair);
	void run_recursive_east(std::map<std::string, std::string>::iterator current_name_pair);
};

