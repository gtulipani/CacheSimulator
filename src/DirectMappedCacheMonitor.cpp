#include <string>
#include <vector>

#include "DirectMappedCacheMonitor.h"

/**
 * We are also reserving space for the necessary quantity of blocks
 * @param configuration
 */
DirectMappedCacheMonitor::DirectMappedCacheMonitor(
		const CacheConfiguration &configuration) :
		CacheMonitor(configuration) {
	std::vector<MemoryAddress> addresses(configuration.getBlocksQuantity(),
										 MemoryAddress());
	this->addresses = std::move(addresses);
}

// For DirectMappedCache, Address can't be moved to front
std::string
DirectMappedCacheMonitor::addIfNotExistsOrMoveToFront(MemoryAddress *address) {
	return this->addIfNotExists(address);
}

std::string DirectMappedCacheMonitor::addIfNotExists(MemoryAddress *address) {
	std::lock_guard<std::mutex> l(this->m);
	unsigned long index = address->getIndex();
	MemoryAddress found_address = this->addresses[index];
	if (found_address == *address) {
		this->hits++;
		return HIT_MESSAGE;
	} else {
		this->misses++;
		this->addresses[index] = *address;
		return MISS_MESSAGE;
	}
}
