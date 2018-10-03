#include "AddressProcessor.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "Thread.h"
#include "CacheMonitor.h"
#include "MemoryAddressNotAllignedException.h"

void AddressProcessor::log_debug(
		MemoryAddress address,
		const std::string &result) {
    if (is_debug) {
        std::cout << result << ": "
                  << address << std::endl;
    }
}

AddressProcessor::AddressProcessor(
		std::string addresses_file_path,
		bool must_reenqueue,
		bool is_debug,
            CacheMonitor &cache_monitor) :
    addresses_file_path(std::move(addresses_file_path)),
    must_reeenqueue(must_reenqueue),
    is_debug(is_debug),
    cache_monitor(cache_monitor) {}

void AddressProcessor::run() {
    std::fstream input_stream;
    input_stream.open(addresses_file_path, std::ios::in);
    std::string line;
    try {
        while (std::getline(input_stream, line)) {
            MemoryAddress memoryAddress(
                line,
                cache_monitor.getConfiguration().getOffsetBits(),
                cache_monitor.getConfiguration().getIndexBits());
            if (!memoryAddress.isAlligned()) {
                throw MemoryAddressNotAllignedException(memoryAddress);
            }
            std::string current_result = (must_reeenqueue)
                             ? cache_monitor.addIfNotExistsOrMoveToFront(
                             		&memoryAddress)
                             : cache_monitor.addIfNotExists(
                             		&memoryAddress);
            log_debug(memoryAddress, current_result);
        }
    } catch (MemoryAddressNotAllignedException &e) {
        cache_monitor.informInvalidAddress(e.getAddress());
    }
    input_stream.close();
}
