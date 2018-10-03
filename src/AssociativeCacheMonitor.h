#ifndef __ASSOCIATIVE_CACHE_MONITOR_H__
#define __ASSOCIATIVE_CACHE_MONITOR_H__

#include "CacheMonitor.h"
#include <string>
#include <deque>

class AssociativeCacheMonitor : public CacheMonitor {
private:
	std::deque<MemoryAddress> addresses;

	void addMissingAddress(MemoryAddress *address);

	typename std::deque<MemoryAddress>::iterator
	getMemoryAddressIterator(MemoryAddress *address);

public:
	explicit AssociativeCacheMonitor(const CacheConfiguration &configuration);

	std::string addIfNotExistsOrMoveToFront(MemoryAddress *address) override;

	std::string addIfNotExists(MemoryAddress *address) override;

	~AssociativeCacheMonitor() override = default;
};

#endif //__ASSOCIATIVE_CACHE_MONITOR_H__
