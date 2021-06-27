# CC=g++
CC=clang++
OUT_DIR=./out
CFLAGS=-Wall -std=c++11
CPPUTEST_HOME=../cpputest-3.8
CPPUTEST_FLAGS=-I$(CPPUTEST_HOME)/include
OPENSSL_CPP_INCLUDE=-I/usr/local/opt/openssl@1.1/include
OPENSSL_LD_LIBRARIES=-L/usr/local/opt/openssl@1.1/lib/
OPENSSL_CRYPTO_LIB=-lcrypto
CPPUTEST_LD_LIBRARIES=-L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

dir:
	if [ ! -d "./out/" ]; then mkdir $(OUT_DIR); fi

c1: dir common.cpp c1.cpp
	$(CC) -o $(OUT_DIR)/c1 common.cpp c1.cpp

c2: dir common.cpp c2.cpp
	$(CC) -o $(OUT_DIR)/c2 common.cpp c2.cpp

c3: dir common.cpp single_byte_xor.cpp c3.cpp
	$(CC) -o $(OUT_DIR)/c3 common.cpp single_byte_xor.cpp c3.cpp

c4: dir common.cpp single_byte_xor.cpp c4.cpp
	$(CC) -o $(OUT_DIR)/c4 common.cpp single_byte_xor.cpp c4.cpp

c5: dir common.cpp c5.cpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/c5 common.cpp c5.cpp

c6: dir common.cpp single_byte_xor.cpp c6.cpp
	$(CC) -o $(OUT_DIR)/c6 common.cpp single_byte_xor.cpp c6.cpp

c7: dir common.cpp c7.cpp
	$(CC) -o $(OUT_DIR)/c7 common.cpp c7.cpp $(OPENSSL_CPP_INCLUDE) $(OPENSSL_LD_LIBRARIES) $(OPENSSL_CRYPTO_LIB)

test: dir common.cpp test_common.cpp
	$(CC) -o $(OUT_DIR)/test common.cpp test_common.cpp $(CPPUTEST_FLAGS) $(CPPUTEST_LD_LIBRARIES)

clean:
	rm -rf $(OUT_DIR)/*
