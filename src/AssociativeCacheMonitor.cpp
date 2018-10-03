#include <deque>
#include <string>

#include "AssociativeCacheMonitor.h"

void AssociativeCacheMonitor::addMissingAddress(MemoryAddress* address) {
    if (this->addresses.size() < configuration.getBlocksQuantity()) {
        this->addresses.push_front(*address);
    } else { // Replaced element from the back
        this->addresses.pop_back();
        this->addresses.push_front(*address);
    }
}

typename std::deque<MemoryAddress>::iterator
AssociativeCacheMonitor::getMemoryAddressIterator(MemoryAddress* address) {
    return std::find(addresses.begin(), addresses.end(), *address);
}

AssociativeCacheMonitor::AssociativeCacheMonitor(
        const CacheConfiguration& configuration) :
    CacheMonitor(configuration) {}

std::string
AssociativeCacheMonitor::addIfNotExistsOrMoveToFront(MemoryAddress* address) {
    std::lock_guard<std::mutex> l(this->m);
    auto it = this->getMemoryAddressIterator(address);
    if (it != this->addresses.end()) { // Found
        this->hits++;
        this->addresses.erase(it);
        this->addresses.push_front(*address);
        return HIT_MESSAGE;
    } else { // Not found
        this->misses++;
        this->addMissingAddress(address);
        return MISS_MESSAGE;
    }
}

std::string AssociativeCacheMonitor::addIfNotExists(MemoryAddress* address) {
    std::lock_guard<std::mutex> l(this->m);
    auto it = this->getMemoryAddressIterator(address);
    if (it != this->addresses.end()) {
        this->hits++;
        return HIT_MESSAGE;
    } else {
        this->misses++;
        this->addMissingAddress(address);
        return MISS_MESSAGE;
    }
}
