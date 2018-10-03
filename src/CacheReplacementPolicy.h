#ifndef __CACHEREPLACEMENTPOLICY_H__
#define __CACHEREPLACEMENTPOLICY_H__

#include <string>

#define ASSOCIATE_LRU_VALUE "associative-lru"
#define ASSOCIATIVE_FIFO_VALUE "associative-fifo"
#define DIRECT_VALUE "direct"

enum replacement_type {
	LRU,
	FIFO
};

class CacheReplacementPolicy {
private:
	replacement_type type;

public:
	explicit CacheReplacementPolicy(replacement_type type);

	explicit CacheReplacementPolicy(std::string type);

	CacheReplacementPolicy(const CacheReplacementPolicy &other);

	CacheReplacementPolicy(CacheReplacementPolicy &&other) noexcept;

	// Overloading the assignment by copy
	CacheReplacementPolicy &operator=(const CacheReplacementPolicy &other);

	// Overloading the assignment by movement
	CacheReplacementPolicy &operator=(CacheReplacementPolicy &&other) noexcept;

	bool isLRU();

	bool isFIFO();

	// Overloading the std::string casting to take the cache replacement policy
	// as char sequence
	explicit operator std::string() const;

	friend std::ostream &
	operator<<(std::ostream &out, const CacheReplacementPolicy &m);
};

#endif //__CACHEREPLACEMENTPOLICY_H__
