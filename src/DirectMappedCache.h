#ifndef __DIRECTCACHE_H__
#define __DIRECTCACHE_H__

#include <vector>
#include <list>
#include <string>

#include "Cache.h"

class DirectMappedCache : public Cache {
private:
	void processAddressesGeneric(std::list<std::string> files_paths_list);

protected:
	void
	processAddressesWithLRU(std::list<std::string> files_paths_list) override;

	void
	processAddressesWithFIFO(std::list<std::string> files_paths_list) override;

public:
	explicit DirectMappedCache(CacheConfiguration configuration);

	DirectMappedCache(const DirectMappedCache &other);

	DirectMappedCache(DirectMappedCache &&other) noexcept;

	// Overloading the assignment by copy
	DirectMappedCache &operator=(const DirectMappedCache &other);

	// Overloading the assignment by movement
	DirectMappedCache &operator=(DirectMappedCache &&other) noexcept;

	~DirectMappedCache() override = default;
};


#endif //__DIRECTCACHE_H__
