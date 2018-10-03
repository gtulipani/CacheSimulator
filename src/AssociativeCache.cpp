#include <utility>

#include <vector>
#include <deque>
#include <list>
#include <string>

#include "AssociativeCache.h"
#include "AssociativeCacheMonitor.h"
#include "Thread.h"
#include "AddressProcessor.h"
#include "MemoryAddressNotAllignedException.h"

AssociativeCache::AssociativeCache(CacheConfiguration configuration) :
		Cache(std::move(configuration)) {}

AssociativeCache::AssociativeCache(const AssociativeCache &other) :
	AssociativeCache(other.configuration) {}

AssociativeCache::AssociativeCache(AssociativeCache &&other) noexcept :
	AssociativeCache(std::move(other.configuration)) {}

AssociativeCache &AssociativeCache::operator=(const AssociativeCache &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->configuration = other.configuration;
	this->hits = other.hits;
	this->misses = other.misses;

	return *this;
}

AssociativeCache &AssociativeCache::operator=(AssociativeCache &&other)
		noexcept {
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
 * {@link files_list} and trigger a AddressProcessor for each one of them.
 * It also creates a CacheMonitor for the critical sections from the Cache
 *
 * @param must_reenqueue  {@param bool} that describes if the element must
 * be re-enqueued to the front when found. E.g.
 * 	Element A is found in the queue, then:
 * 	- If {@param must_reenqueue} is true, the element is moved to the front
 * 	- If {@param must_reenqueue} is false, the element is not moved at all
 */
void AssociativeCache::processAddressesGeneric(
		std::list<std::string> files_paths_list,
		bool must_reenqueue) {
	std::vector<Thread *> threads;
	unsigned long files_quantity = files_paths_list.size();
	bool is_debug = configuration.isDebug();

	CacheMonitor *cacheMonitor = new AssociativeCacheMonitor(configuration);

	std::for_each(files_paths_list.begin(), files_paths_list.end(),
		[&threads, &must_reenqueue, &is_debug, &cacheMonitor](
						  std::string file_path_to_process) {
			threads.push_back(new AddressProcessor(
					std::move(file_path_to_process),
					must_reenqueue,
					is_debug,
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
 * Implementation that process the addresses using FIFO replacement policy
 * @param addresses_list
 */
void AssociativeCache::processAddressesWithFIFO(
		std::list<std::string> files_paths_list) {
	processAddressesGeneric(std::move(files_paths_list), false);
}

/**
 * Implementation that process the addresses using LRU replacement policy
 * The logic is the same as FIFO, but when the element is found is moved to
 * the front. The replacement will always look for the element from the back.
 * @param addresses_list
 */
void AssociativeCache::processAddressesWithLRU(
		std::list<std::string> files_paths_list) {
	processAddressesGeneric(std::move(files_paths_list), true);
}


