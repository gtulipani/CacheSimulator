#include "CacheMonitor.h"

CacheMonitor::CacheMonitor(const CacheConfiguration& configuration) :
        hits(0),
        misses(0),
        configuration(configuration) {}

void CacheMonitor::informInvalidAddress(MemoryAddress address) {
    std::lock_guard<std::mutex> l(m);
    std::cerr << MISSALLIGNED_ADDRESS_MESSAGE << address << std::endl
              << ADDRESS_PROCESSING_ABORTION_MESSAGE << std::endl;
}

unsigned int CacheMonitor::getHits() {
    std::lock_guard<std::mutex> l(m);
    return hits;
}

unsigned int CacheMonitor::getMisses() {
    std::lock_guard<std::mutex> l(m);
    return misses;
}

CacheConfiguration CacheMonitor::getConfiguration() const {
    return configuration;
}
