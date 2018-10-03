#ifndef __CACHECONFIGURATION_H__
#define __CACHECONFIGURATION_H__

#include <map>
#include <string>
#include "CacheReplacementPolicy.h"

typedef std::map<std::string, std::string> ConfigMap;

class CacheConfiguration {
private:
	std::string vendor_id;
	std::string model_name;
	std::string cpu_mhz;
	std::string cache_type;
	CacheReplacementPolicy cache_replacement_policy;
	int cache_size;
	int line_size;
	bool debug;

	bool parseDebug(ConfigMap config_map);
	ConfigMap parseConfigurationFile(const std::string& config_file_path);

public:
	CacheConfiguration(std::string vendor_id, std::string model_name,
					   std::string cpu_mhz, std::string type,
					   CacheReplacementPolicy replacement_policy,
					   int cache_size,
					   int line_size,
					   bool debug);

	explicit CacheConfiguration(ConfigMap config_map);

	explicit CacheConfiguration(const std::string& config_file_path);

	CacheConfiguration(const CacheConfiguration &other);

	CacheConfiguration(CacheConfiguration &&other) noexcept;

	// Overloading the assignment by copy
	CacheConfiguration &operator=(const CacheConfiguration &other);

	// Overloading the assignment by movement
	CacheConfiguration &operator=(CacheConfiguration &&other) noexcept;

	~CacheConfiguration() = default;

	bool isAssociative() const;

	bool isDirect() const;

	bool isDebug() const;

	CacheReplacementPolicy getReplacementPolicy() const;

	unsigned long getBlocksQuantity() const;

	int getOffsetBits() const;

	int getIndexBits() const;

	void printConfiguration() const;

	// Overloading the << operator but we make it friend
	// to be callable from outside
	friend std::ostream &
	operator<<(std::ostream &out, const CacheConfiguration &c);
};

#endif //__CACHECONFIGURATION_H__
