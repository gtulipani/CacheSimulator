#ifndef __CACHECREATOR_H__
#define __CACHECREATOR_H__

#include "DirectMappedCache.h"
#include "AssociativeCache.h"

/**
 * Class that handles the logic to create the proper cache based on the Configuration
 */
class CacheCreator {
private:
	static DirectMappedCache *
	createDirectCache(CacheConfiguration configuration);

	static AssociativeCache *
	createAssociativeCache(CacheConfiguration configuration);

public:
	static Cache *factoryMethod(CacheConfiguration configuration);
};


#endif //__CACHECREATOR_H__
