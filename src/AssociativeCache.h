#ifndef __ASSOCIATIVECACHE_H__
#define __ASSOCIATIVECACHE_H__

#include <deque>
#include <list>
#include <string>

#include "Cache.h"

class AssociativeCache : public Cache {
private:
	void processAddressesGeneric(std::list<std::string> files_paths_list,
								 bool must_reenqueue);

protected:
	void
	processAddressesWithLRU(std::list<std::string> files_paths_list) override;

	void
	processAddressesWithFIFO(std::list<std::string> files_paths_list) override;

public:
	explicit AssociativeCache(CacheConfiguration configuration);

	AssociativeCache(const AssociativeCache &other);

	AssociativeCache(AssociativeCache &&other) noexcept;

	// Overloading the assignment by copy
	AssociativeCache &operator=(const AssociativeCache &other);

	// Overloading the assignment by movement
	AssociativeCache &operator=(AssociativeCache &&other) noexcept;

	~AssociativeCache() override = default;
};


#endif //__ASSOCIATIVECACHE_H__
