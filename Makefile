TARGET = libpaku

CXXFLAGS = -std=c++1y -Iinclude -Iinclude/paku -Ivendor/optional -Ivendor/variant -fPIC -Wall -Wextra -Os
LDFLAGS =

SRCS = \
	source/packet/ether.cpp source/packet/arp.cpp source/packet/ip.cpp source/packet/icmp.cpp source/packet/tcp.cpp \
	source/builder/base.cpp source/builder/buffer.cpp source/builder/icmp.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET}.so ${TARGET}.a

$(TARGET).so: $(OBJS)
	$(CXX) ${LDFLAGS} -shared -o $@.so $^

$(TARGET).a: $(OBJS)
	$(AR) rcs $@.a $^

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS}
