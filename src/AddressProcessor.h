#ifndef __ADDRESS_PROCESSOR_H__
#define __ADDRESS_PROCESSOR_H__

#include <string>
#include "Thread.h"
#include "CacheMonitor.h"

class AddressProcessor : public Thread {
private:
    std::string addresses_file_path;
    bool must_reeenqueue;
    bool is_debug;
    CacheMonitor &cache_monitor;

    void log_debug(MemoryAddress address, const std::string &result);
public:
    AddressProcessor(std::string addresses_file_path,
                     bool must_reenqueue,
                     bool is_debug,
                     CacheMonitor &cache_monitor);

    void run() override;
};

#endif //__ADDRESS_PROCESSOR_H__
