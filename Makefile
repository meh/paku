TARGET = libpaku

CXXFLAGS = -std=c++1y -Iinclude -Iinclude -Ivendor/optional -Ivendor/variant -fPIC -Wall -Wextra -Os
LDFLAGS =

SOURCES = \
	source/packet/ether.cpp source/packet/arp.cpp source/packet/ip.cpp source/packet/icmp.cpp source/packet/tcp.cpp \
	source/builder/base.cpp source/builder/buffer.cpp source/builder/icmp.cpp

.PHONY: all
all: ${TARGET}.so ${TARGET}.a

$(TARGET).so: $(SOURCES:.cpp=.o)
	$(CXX) ${LDFLAGS} -shared -o $@ $^

$(TARGET).a: $(SOURCES:.cpp=.o)
	$(AR) rcs $@ $^

.PHONY: test
test: ${TARGET}.a
	@$(CXX) ${CXXFLAGS} -Wno-unused-function -Ivendor/amirite -o test/layer test/layer.cpp ${TARGET}.a
	@test/layer

.PHONY: clean
clean:
	-${RM} ${TARGET}.so ${TARGET}.a $(SOURCES:.cpp=.o)
