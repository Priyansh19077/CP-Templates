CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I..

SRCS := $(wildcard test_*.cpp)
BINS := $(SRCS:.cpp=)

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: all
	@failed=0; \
	for t in $(BINS); do \
	  ./$$t || failed=$$((failed + 1)); \
	done; \
	if [ $$failed -eq 0 ]; then echo "All tests passed."; else echo "$$failed test(s) failed."; fi; \
	exit $$failed

clean:
	rm -f $(BINS)

.PHONY: all run clean
