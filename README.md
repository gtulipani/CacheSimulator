# CacheSimulator
## Description
CLI Multi-Threading Application that simulates a [Cache](https://en.wikipedia.org/wiki/Cache_(computing)),
parsing different memory addresses, validating the allignment and summarizing the **Hits** and **Misses**. 
The tag is ignored for this simulation.

## Multi-Threading
The Application is prepared to create a thread for every file of addresses and
process each one of them simultaneously. The Race Conditions have been resolved using a 
[Monitor](https://en.wikipedia.org/wiki/Monitor_(synchronization)) class for the
shared resources. If one thread throws an exception (E.g. memory disallignment), its execution finishes
but the rest of the threads continue processing.

## Building and Running
### Build
1. Navigate to the `src` folder
1. Execute `make -f Makefile`

### Run
The application must be executed with the following syntax `./cacheSimulator [config_file] [addresses_file_1] [[addresses_file_2] ...`
#### Configuration File
The Configuration File has the following format:
```
vendor_id=My Computer
model name=Fully Associative (FIFO) Test CPU
cpu MHz=1604.51
cache type=associative-fifo
cache size=1024
line size=256
debug=true
```
##### Configuration File Parameter
The application accepts the following parameters:
1. `vendor_id`: string representing the vendor.
1. `model name`: string representing the model of the cache.
1. `cpu MHz`: floating point number representing the CPU Processing Power.
1. `cache type`: represents the [type](https://en.wikipedia.org/wiki/Cache_Placement_Policies) of the cache. The following types are supported:
   1. `direct`: represents a **Direct Mapped Cache**.
   1. `associative-fifo`: represents a **Fully Associatve Cache** with [FIFO](https://en.wikipedia.org/wiki/Cache_replacement_policies#First_in_first_out_(FIFO)) replacement policy.
   1. `associative-lru`: represents a **Fully Associatve Cache** with [LRU](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)) replacement policy. 
1. `cache size`: complete size of the cache in bytes
1. `line size`: complete size of each line of the cache in bytes
1. `debug`: bool parameter that specifies if each address should be listed in **stdout**

#### Address File
The Addresses file has the following format:
```
0x00000001
0x00000100
0x00000000
0x00000200
0x00000000
0x00000000
0x00000300
0x00000000
0x00000500
0x00000000
```
##### Address File Format
The Addresses file is a regular text file, with every line containing an address
in hexadecimal format. The `0x` identifier must be prepended and the address must 
be conformed by 8 digits. E.g. `0x00001130`.

#### STDOUT
1. The application prints in **stdout** the configuration of the cache
1. Then the list of addresses is printed (only if the `debug` key is set to true)
1. Finally a status of all hits and misses is printed
```
# Cache Inicializada

* Fabricante: {vendor_id}
* Modelo: {model name}
* Cpu MHz: {cpu MHz}

{debug = true, [Hit/Miss: Address]}

# Informe

* Total de hits: {total_hits}
* Total de misses: {total_misses}
``` 

#### STDERROR
1. The application validates that the Memory Address is properly [alligned](https://en.wikipedia.org/wiki/Data_structure_alignment).
If one of the threads detects a disalligned memory address in the file, the execution is interrupted
and an error message is printed in **stderr**
```
Direccion invalida: {Address}
Abortando
```

### Examples
- Process the cache simulator using a FA Cache with FIFO Replacement Policy and
including one file with addresses. 
   - The program is executed with the following command: `./cacheSimulator fa-fifo.cfg fa-fifo.bin`
   - The following text is printed in **stdout**:
```
# Cache Inicializada

* Fabricante: Taller
* Modelo: Full Associative (FIFO) Test CPU
* Cpu MHz: 1604.51

Miss: 0x00001130
Miss: 0xff00113c
Hit: 0x0000113c
Miss: 0x0000123c
Miss: 0x00001338
Miss: 0x00002538

# Informe

* Total de hits: 1
* Total de misses: 5
``` 
- Process the cache simulator using a DM Cache and including **two** files with addresses.
    - The program is executed with the following command: `./cacheSimulator direct.cfg error-01.bin error-02.bin`
```
# Cache Inicializada

* Fabricante: Taller
* Modelo: Crashy Test CPU
* Cpu MHz: 1300.02

Direccion invalida: 0x00000001
Abortando
Direccion invalida: 0x00000001
Abortando

# Informe

* Total de hits: 2
* Total de misses: 2
```

### Clean
1. Navigate to the `src` folder
1. Execute `make -f Makefile clean`. This will remove the executable and all the **.o** files.

