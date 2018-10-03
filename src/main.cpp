#include <iostream>
#include <string>
#include <list>
#include "CacheCreator.h"
#include "CacheConfiguration.h"

#define PROGRAM_RESULT_SUCCESS 0
#define PROGRAM_RESULT_FAILURE 1

#define CACHE_INITIALIZED_TITLE "# Cache Inicializada"

/**
 * Define the friend function for the CacheConfiguration
 */
std::ostream &
operator<<(std::ostream &out, const CacheConfiguration &configuration) {
	configuration.printConfiguration();
	return out;
}

/**
 * Define the friend function for the MemoryAddress
 */
std::ostream &operator<<(std::ostream &out, const MemoryAddress &address) {
	out << (std::string) address;
	return out;
}


/**
 * Define the friend function for the CacheReplacementPolicy
 */
std::ostream &operator<<(std::ostream &out, const CacheReplacementPolicy &c) {
	out << (std::string) c;
	return out;
}

/**
 * Private function that creates a list of std::string representing a input file
 */
static std::list<std::string>
buildMemoryAddressFilesList(int argc, char *argv[]) {
	std::list<std::string> input_files_list;
	for (int i = 2; i < argc; i++) {
		input_files_list.emplace_back(argv[i]);
	}
	return input_files_list;
}

int main(int argc, char *argv[]) {
	if (argc <= 2) {
		return PROGRAM_RESULT_FAILURE;
	} else {
		Cache *cache = CacheCreator::factoryMethod(CacheConfiguration(argv[1]));
		std::cout << CACHE_INITIALIZED_TITLE << std::endl << std::endl;
		std::cout << cache->getConfiguration() << std::endl;
		cache->processFiles(buildMemoryAddressFilesList(argc, argv));
		std::cout << std::endl;
		cache->printStatus(std::cout);
		delete cache;
	}
	return PROGRAM_RESULT_SUCCESS;
}
