#include <utility>
#include <iostream>
#include <list>
#include <fstream>
#include <string>

#include "Cache.h"

#define RESULTS_TITLE "# Informe"
#define TOTAL_HITS_TITLE "* Total de hits: "
#define TOTAL_MISSES_TITLE "* Total de misses: "

Cache::Cache(CacheConfiguration configuration)
		: configuration(std::move(configuration)),
		  hits(0),
		  misses(0) {}

Cache::Cache(const Cache &other) : Cache(other.configuration) {}

Cache::Cache(Cache &&other) noexcept : Cache(std::move(other.configuration)) {}

Cache &Cache::operator=(const Cache &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->configuration = other.configuration;
	this->hits = other.hits;
	this->misses = other.misses;

	return *this;
}

Cache &Cache::operator=(Cache &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->configuration = std::move(other.configuration);
	this->hits = other.hits;
	this->misses = other.misses;

	return *this;
}

void Cache::processFiles(std::list<std::string> list) {
	if (configuration.getReplacementPolicy().isLRU()) {
		processAddressesWithLRU(std::move(list));
	} else if (configuration.getReplacementPolicy().isFIFO()) {
		processAddressesWithFIFO(std::move(list));
	} else {
		throw std::runtime_error("Replacement Policy not supported");
	}
}

CacheConfiguration Cache::getConfiguration() const {
	return this->configuration;
}

void Cache::printStatus(std::ostream &ostream) {
	ostream << RESULTS_TITLE << std::endl << std::endl;
	ostream << TOTAL_HITS_TITLE << hits << std::endl;
	ostream << TOTAL_MISSES_TITLE << misses << std::endl;
}
