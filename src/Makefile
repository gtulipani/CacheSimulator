# BASIC CONFIGURATION
###########################

target = cacheSimulator

extension = cpp

math = yes
threads = yes
#gtk = yes
#gtkmm = yes
#verbose = yes

# ADVANCED CONFIGURATION
###########################

CSTD = c99
CXXSTD = c++11
CFLAGS = -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline

#LDFLAGS =
#static = yes


# CONFIGURATION PROCESSING
####################################################

# Links optional libraries if defined

ifdef gtk
CFLAGS += $(shell pkg-config --cflags gtk+-3.0) \
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED
LDFLAGS += $(shell pkg-config --libs gtk+-3.0)
endif

ifdef gtkmm
CFLAGS += $(shell pkg-config --cflags gtkmm-3.0) \
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED	\
	-DGDKMM_DISABLE_DEPRECATED 	\
	-DGTKMM_DISABLE_DEPRECATED
LDFLAGS += $(shell pkg-config --libs gtkmm-3.0)
endif

ifdef math
LDFLAGS += -lm
endif

ifdef threads
LDFLAGS += -pthread
endif

ifdef static
LDFLAGS += -static
endif

CXXFLAGS += $(CFLAGS)

ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

# Si no especifica archivos, tomo todos.
sources ?= $(wildcard *.$(extension))
directories = $(shell find . -type d -regex '.*\w+')

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif


# RULES
#########

.PHONY: all clean

all: $(target)

o_files = $(patsubst %.$(extension),%.o,$(sources))

$(target): $(o_files)
	@if [ -z "$(o_files)" ]; \
	then \
		echo "No source files in current directory. Valid extension is '.$(extension)' and recursive directories are NOT supported."; \
		if [ -n "$(directories)" ]; then echo "Directories found: $(directories)"; fi; \
		false; \
	fi >&2
	$(LD) $(o_files) -o $(target) $(LDFLAGS)

clean:
	$(RM) $(o_files) $(target)

