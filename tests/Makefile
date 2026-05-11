CXX      = g++
TESTS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
REPO_ROOT := $(abspath $(TESTS_DIR)/..)
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I$(TESTS_DIR) -I$(REPO_ROOT)

SRCS := $(shell find $(TESTS_DIR) -name 'test_*.cpp')
BINS := $(SRCS:.cpp=)

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: all
	@failed=0; \
	for t in $(BINS); do \
	  $$t || failed=$$((failed+1)); \
	done; \
	if [ $$failed -eq 0 ]; then echo "All tests passed."; else echo "$$failed test(s) failed."; fi; \
	exit $$failed

clean:
	find $(TESTS_DIR) -name 'test_*' ! -name '*.cpp' -delete

.PHONY: all run clean
