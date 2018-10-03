#ifndef __CACHE_MONITOR_H__
#define __CACHE_MONITOR_H__

#include <mutex>
#include <algorithm>
#include <string>
#include <iostream>

#include "MemoryAddress.h"
#include "CacheConfiguration.h"

#define HIT_MESSAGE "Hit"
#define MISS_MESSAGE "Miss"
#define MISSALLIGNED_ADDRESS_MESSAGE "Direccion invalida: "
#define ADDRESS_PROCESSING_ABORTION_MESSAGE "Abortando"

class CacheMonitor {
protected:
	std::mutex m;
	unsigned int hits;
	unsigned int misses;
	CacheConfiguration configuration;

public:
	explicit CacheMonitor(const CacheConfiguration& configuration);

	virtual std::string addIfNotExistsOrMoveToFront(MemoryAddress *address) = 0;
	virtual std::string addIfNotExists(MemoryAddress *address) = 0;

	void informInvalidAddress(MemoryAddress address);

	unsigned int getHits();

	unsigned int getMisses();

	CacheConfiguration getConfiguration() const;

	virtual ~CacheMonitor() = default;
};


#endif //__CACHE_MONITOR_H__
