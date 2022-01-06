program_NAME := main
program_CXX_SRCS := $(wildcard *.c)
program_CXX_OBJS := ${program_CXX_SRCS:.c=.o}
program_OBJS := $(program_CXX_OBJS)
program_INCLUDE_DIRS := /usr/include/SDL2
program_LIBRARY_DIRS :=
program_LIBRARIES := SDL2 SDL2_mixer SDL2_ttf SDL2_image

CPPFLAGS = $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS = $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDLIBS = $(foreach library,$(program_LIBRARIES),-l$(library))

LINK.cc = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME) $(LDLIBS)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean