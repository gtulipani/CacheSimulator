#include "CacheCreator.h"

AssociativeCache *
CacheCreator::createAssociativeCache(CacheConfiguration configuration) {
	return new AssociativeCache(std::move(configuration));
}

DirectMappedCache *
CacheCreator::createDirectCache(CacheConfiguration configuration) {
	return new DirectMappedCache(std::move(configuration));
}

Cache *CacheCreator::factoryMethod(CacheConfiguration configuration) {
	if (configuration.isAssociative()) {
		return createAssociativeCache(std::move(configuration));
	}
	if (configuration.isDirect()) {
		return createDirectCache(std::move(configuration));
	}
	throw std::runtime_error("Cache Type is invalid");
}
