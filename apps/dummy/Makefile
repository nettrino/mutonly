#
# General
#
#
CC=clang-4.0
CXX=clang++-4.0

SRC_DIR=../..

# Use local copy of Fuzzer
LIBFUZZER_SRC=$(SRC_DIR)/Fuzzer
LIBFUZZER_LIB=$(LIBFUZZER_SRC)/libFuzzer.a

DBGFLAGS=-g -ggdb3
CXXFLAGS=-O2 -Wall -std=c++11 -Wno-unused-variable $(DBGFLAGS)
COV_FLAGS=-fsanitize=address \
		  -fsanitize-coverage=edge,indirect-calls,8bit-counters

TARGET=driver
TARGET_SRC=driver.cpp

.PHONY:all
all: prelim $(TARGET)

prelim:
	rm -f $(TARGET)

# make our modified version of the Fuzzer
fuzzer:
	$(CXX) -c -g -O2 -std=c++11 $(LIBFUZZER_SRC)/*.cpp \
			-I$(LIBFUZZER_SRC)
	ar rv $(LIBFUZZER_SRC)/libFuzzer.a Fuzzer*.o
	rm Fuzzer*.o

$(TARGET): $(TARGET_SRC)
	$(CXX) $(CXXFLAGS) $(COV_FLAGS) $< $(LIBFUZZER_LIB) -o $@

.PHONY: test
test:
	rm -rf corpus && mkdir -p corpus out && echo "21312421412412" > corpus/1 \
		&& ASAN_OPTIONS=halt_on_error=0 ./$(TARGET) corpus/ \
	-artifact_prefix=out/ -print_final_stats=1 \
	-detect_leaks=0 -rss_limit_mb=100000 \
	-runs=10 -max_len=38000 -mut_only=1

.PHONY:clean
clean:
	rm -rf *.o *.a $(TARGET) qtable.bin

.PHONY:cleanf
cleanf:
	rm $(LIBFUZZER_LIB)
