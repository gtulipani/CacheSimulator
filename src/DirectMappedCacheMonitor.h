#ifndef __DIRECT_MAPPED_CACHE_MONITOR_H__
#define __DIRECT_MAPPED_CACHE_MONITOR_H__

#include "CacheMonitor.h"
#include <string>
#include <vector>

class DirectMappedCacheMonitor : public CacheMonitor {
private:
	std::vector<MemoryAddress> addresses;
public:
	explicit DirectMappedCacheMonitor(const CacheConfiguration &configuration);

	std::string addIfNotExistsOrMoveToFront(MemoryAddress* address) override;
	std::string addIfNotExists(MemoryAddress* address) override;

	~DirectMappedCacheMonitor() override = default;
};

#endif //__DIRECT_MAPPED_CACHE_MONITOR_H__
