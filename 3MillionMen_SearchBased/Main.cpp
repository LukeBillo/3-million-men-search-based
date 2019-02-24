#include <string>
#include <list>
#include "ThreeMillionMenSearch.h"
#include "ThreeMillionMenReader.h"
#include <iostream>


int main(int argc, const char* argv[])
{
	if (argc == 1)
	{
		std::cout << "Usage: 3MillionMen_SearchBased [input_file_name] [OPTIONAL: output_file_name]" << std::endl;
		return 1;
	}

	const std::string input_file = argv[1];

	auto* reader = new three_million_men_reader(input_file);
	reader->read_all_lines();
	auto names = reader->get_lines();
	delete reader;

	const auto algorithm = new three_million_men_search(names);
	algorithm->run();
	const auto results = algorithm->get_results();

	const std::string output_file = argc > 2 ? argv[2] : "results.txt";
	std::ofstream output_file_stream(output_file);

	for (const auto result : *results)
	{
		output_file_stream << result << std::endl;
	}

	delete results;
	delete algorithm;
    return 0;
}

