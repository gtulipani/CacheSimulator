#include <utility>

#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "CacheConfiguration.h"
#include "TransformationUtils.h"

#define KEY_VALUE_SEPARATOR '='
#define VENDOR_ID_KEY "vendor_id"
#define MODEL_NAME_KEY "model name"
#define CPU_MHZ_KEY "cpu MHz"
#define CACHE_TYPE_KEY "cache type"
#define CACHE_SIZE_KEY "cache size"
#define LINE_SIZE_KEY "line size"
#define DEBUG_KEY "debug"

#define VENDOR_ID_OUTPUT_KEY "* Fabricante: "
#define MODEL_NAME_KEY_OUTPUT "* Modelo: "
#define CPU_MHZ_KEY_OUTPUT "* Cpu MHz: "

bool CacheConfiguration::parseDebug(ConfigMap config_map) {
	return (config_map.count(DEBUG_KEY) > 0)
			? str_to_bool(config_map[DEBUG_KEY])
			: false;
}

/**
 * Private function that creates a ConfigMap based on a file of key values
 * @param config_file_path {@link std::string} with the path
 */
ConfigMap CacheConfiguration::parseConfigurationFile(
		const std::string &config_file_path) {
	std::fstream input_stream;
	input_stream.open(config_file_path, std::ios::in);
	ConfigMap key_values_map;
	std::string line;
	while (std::getline(input_stream, line)) {
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, KEY_VALUE_SEPARATOR)) {
			std::string value;
			if (std::getline(is_line, value)) {
				key_values_map[key] = value;
			}
		}
	}
	input_stream.close();
	return key_values_map;
}

CacheConfiguration::CacheConfiguration(
		std::string vendor_id,
		std::string model_name,
		std::string cpu_mhz,
		std::string type,
		CacheReplacementPolicy cache_replacement_policy,
		int cache_size,
		int line_size,
		bool debug) :
	vendor_id(std::move(vendor_id)),
	model_name(std::move(model_name)),
	cpu_mhz(std::move(cpu_mhz)),
	cache_type(std::move(type)),
	cache_replacement_policy(std::move(cache_replacement_policy)),
	cache_size(cache_size),
	line_size(line_size),
	debug(debug) {}

CacheConfiguration::CacheConfiguration(ConfigMap config_map) :
			CacheConfiguration(
		std::move(config_map[VENDOR_ID_KEY]),
		std::move(config_map[MODEL_NAME_KEY]),
		std::move(config_map[CPU_MHZ_KEY]),
		config_map[CACHE_TYPE_KEY],
		CacheReplacementPolicy(config_map[CACHE_TYPE_KEY]),
		std::stoi(config_map[CACHE_SIZE_KEY]),
		std::stoi(config_map[LINE_SIZE_KEY]),
		parseDebug(config_map)
) {
 	std::vector<std::string> valid_keys = {VENDOR_ID_KEY, MODEL_NAME_KEY,
										   CPU_MHZ_KEY,
										   CACHE_TYPE_KEY, CACHE_SIZE_KEY,
										   LINE_SIZE_KEY};
	if (config_map.size() < valid_keys.size()) {
		throw std::runtime_error("Mandatory parameters missing");
	}
}

CacheConfiguration::CacheConfiguration(const std::string& config_file_path) :
	CacheConfiguration(parseConfigurationFile(config_file_path)) {}

CacheConfiguration::CacheConfiguration(const CacheConfiguration &other) :
			CacheConfiguration(
		other.vendor_id,
		other.model_name,
		other.cpu_mhz,
		other.cache_type,
		other.cache_replacement_policy,
		other.cache_size,
		other.line_size,
		other.debug) {}

CacheConfiguration::CacheConfiguration(CacheConfiguration &&other) noexcept :
			CacheConfiguration(
		std::move(other.vendor_id),
		std::move(other.model_name),
		std::move(other.cpu_mhz),
		std::move(other.cache_type),
		std::move(other.cache_replacement_policy),
		other.cache_size,
		other.line_size,
		other.debug) {
	other.cache_size = 0;
	other.line_size = 0;
}

CacheConfiguration
&CacheConfiguration::operator=(const CacheConfiguration &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->vendor_id = other.vendor_id;
	this->model_name = other.model_name;
	this->cpu_mhz = other.cpu_mhz;
	this-> cache_type = other.cache_type;
	this->cache_replacement_policy = other.cache_replacement_policy;
	this->cache_size = other.cache_size;
	this->line_size = other.line_size;
	this->debug = other.debug;

	return *this;
}

CacheConfiguration
&CacheConfiguration::operator=(CacheConfiguration &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->vendor_id = std::move(other.vendor_id);
	this->model_name = std::move(other.model_name);
	this->cpu_mhz = std::move(other.cpu_mhz);
	this-> cache_type = std::move(other.cache_type);
	this->cache_replacement_policy = std::move(other.cache_replacement_policy);
	this->cache_size = other.cache_size;
	this->line_size = other.line_size;
	this->debug = other.debug;

	return *this;
}

bool CacheConfiguration::isAssociative() const {
	return (this->cache_type == ASSOCIATE_LRU_VALUE) ||
		   (this->cache_type == ASSOCIATIVE_FIFO_VALUE);
}

bool CacheConfiguration::isDirect() const {
	return this->cache_type == DIRECT_VALUE;
}

bool CacheConfiguration::isDebug() const {
	return this->debug;
}

CacheReplacementPolicy CacheConfiguration::getReplacementPolicy() const {
	return this->cache_replacement_policy;
}

unsigned long CacheConfiguration::getBlocksQuantity() const {
	return static_cast<unsigned long>((this->cache_size) / this->line_size);
}

int CacheConfiguration::getOffsetBits() const {
	return static_cast<int>(log2(this->line_size));
}

int CacheConfiguration::getIndexBits() const {
	return (this->isAssociative()) ? 0 : static_cast<int>(log2(
			this->getBlocksQuantity()));
}

void CacheConfiguration::printConfiguration() const {
	std::cout << VENDOR_ID_OUTPUT_KEY << this->vendor_id << std::endl;
	std::cout << MODEL_NAME_KEY_OUTPUT << this->model_name << std::endl;
	std::cout << CPU_MHZ_KEY_OUTPUT << this->cpu_mhz << std::endl;
}
