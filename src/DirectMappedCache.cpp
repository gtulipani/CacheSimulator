#include <utility>
#include <list>
#include <vector>
#include <string>

#include "DirectMappedCache.h"
#include "DirectMappedCacheMonitor.h"
#include "Thread.h"
#include "AddressProcessor.h"
#include "MemoryAddressNotAllignedException.h"

DirectMappedCache::DirectMappedCache(CacheConfiguration configuration) :
		Cache(std::move(configuration)) {}

DirectMappedCache::DirectMappedCache(const DirectMappedCache &other)
		: DirectMappedCache(other.configuration) {}

DirectMappedCache::DirectMappedCache(DirectMappedCache &&other) noexcept
		: DirectMappedCache(std::move(other.configuration)) {}

DirectMappedCache &
DirectMappedCache::operator=(const DirectMappedCache &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->configuration = other.configuration;
	this->hits = other.hits;
	this->misses = other.misses;

	return *this;
}

DirectMappedCache &
DirectMappedCache::operator=(DirectMappedCache &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->configuration = std::move(other.configuration);
	this->hits = other.hits;
	this->misses = other.misses;

	return *this;
}

/**
 * Private function that has all the logic to iterate over the elements from
 * {@link files_paths_list} and trigger a AddressProcessor for each one of them.
 * It also creates a CacheMonitor for the critical sections from the Cache
 */
void DirectMappedCache::processAddressesGeneric(
		std::list<std::string> files_paths_list) {
	std::vector<Thread *> threads;
	unsigned long files_quantity = files_paths_list.size();
	bool is_debug = configuration.isDebug();

	CacheMonitor *cacheMonitor = new DirectMappedCacheMonitor(configuration);

	std::for_each(files_paths_list.begin(), files_paths_list.end(),
				  [&threads, &is_debug, &cacheMonitor](
						  std::string file_path_to_process) {
					  threads.push_back(new AddressProcessor(
							  std::move(file_path_to_process), false, is_debug,
							  *cacheMonitor));
				  });

	for (unsigned int i = 0; i < files_quantity; i++) {
		threads[i]->start();
	}

	for (unsigned int i = 0; i < files_quantity; i++) {
		threads[i]->join();
		delete threads[i];
	}

	hits = cacheMonitor->getHits();
	misses = cacheMonitor->getMisses();

	delete cacheMonitor;
}

/**
 * In DirectMappedCache, FIFO and LRU have the same implementation
 */
void DirectMappedCache::processAddressesWithFIFO(
		std::list<std::string> file_path_list) {
	processAddressesGeneric(file_path_list);
}

/**
 * In DirectMappedCache, FIFO and LRU have the same implementation
 */
void DirectMappedCache::processAddressesWithLRU(
		std::list<std::string> file_path_list) {
	processAddressesGeneric(file_path_list);
}
