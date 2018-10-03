#ifndef __CACHE_H__
#define __CACHE_H__

#include <list>
#include <string>
#include "MemoryAddress.h"
#include "CacheConfiguration.h"

class Cache {
protected:
	CacheConfiguration configuration;
	int hits;
	int misses;

	virtual void
	processAddressesWithLRU(std::list<std::string> files_paths_list) = 0;

	virtual void
	processAddressesWithFIFO(std::list<std::string> files_paths_list) = 0;

public:
	explicit Cache(CacheConfiguration configuration);

	Cache(const Cache &other);

	Cache(Cache &&other) noexcept;

	// Overloading the assignment by copy
	Cache &operator=(const Cache &other);

	// Overloading the assignment by movement
	Cache &operator=(Cache &&other) noexcept;

	CacheConfiguration getConfiguration() const;

	void processFiles(std::list<std::string> files_paths_list);

	void printStatus(std::ostream &ostream);

	virtual ~Cache() = default;
};


#endif //__CACHE_H__
