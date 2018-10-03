#include "CacheReplacementPolicy.h"

#include <stdexcept>
#include <string>

replacement_type parseReplacementPolicy(const std::string &policy) {
	if (policy == ASSOCIATE_LRU_VALUE || policy == DIRECT_VALUE) {
		return LRU;
	}
	if (policy == ASSOCIATIVE_FIFO_VALUE) {
		return FIFO;
	}
	throw std::runtime_error("Invalid Replacement Policy");
}

CacheReplacementPolicy::CacheReplacementPolicy(replacement_type type) : type(
		type) {}

CacheReplacementPolicy::CacheReplacementPolicy(std::string type)
		: CacheReplacementPolicy(parseReplacementPolicy(type)) {}

CacheReplacementPolicy::CacheReplacementPolicy(
		const CacheReplacementPolicy &other) : CacheReplacementPolicy(
		other.type) {}

CacheReplacementPolicy::CacheReplacementPolicy(
		CacheReplacementPolicy &&other) noexcept : CacheReplacementPolicy(
		std::move(other.type)) {}

CacheReplacementPolicy &
CacheReplacementPolicy::operator=(const CacheReplacementPolicy &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->type = other.type;

	return *this;
}

CacheReplacementPolicy &
CacheReplacementPolicy::operator=(CacheReplacementPolicy &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->type = std::move(other.type);

	return *this;
}

bool CacheReplacementPolicy::isLRU() {
	return (this->type == LRU);
}

bool CacheReplacementPolicy::isFIFO() {
	return (this->type == FIFO);
}

CacheReplacementPolicy::operator std::string() const {
	switch (this->type) {
		case LRU: {
			return ASSOCIATE_LRU_VALUE;
		}
		case FIFO: {
			return ASSOCIATIVE_FIFO_VALUE;
		}
		default: {
			throw std::runtime_error("Invalid replacement_type");
		}
	}
}
