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

common: dir common.cpp
	$(CC) -c common.cpp -o $(OUT_DIR)/common

crypto_func: dir crypto_func.cpp
	$(CC) -c crypto_func.cpp -o $(OUT_DIR)/crypto_func $(OPENSSL_CPP_INCLUDE)

c1: dir common c1.cpp
	$(CC) -o $(OUT_DIR)/c1 $(OUT_DIR)/common c1.cpp

c2: dir common c2.cpp
	$(CC) -o $(OUT_DIR)/c2 $(OUT_DIR)/common c2.cpp

c3: dir common single_byte_xor.cpp c3.cpp
	$(CC) -o $(OUT_DIR)/c3 $(OUT_DIR)/common single_byte_xor.cpp c3.cpp

c4: dir common single_byte_xor.cpp c4.cpp
	$(CC) -o $(OUT_DIR)/c4 $(OUT_DIR)/common single_byte_xor.cpp c4.cpp

c5: dir common c5.cpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/c5 $(OUT_DIR)/common c5.cpp

c6: dir common single_byte_xor.cpp c6.cpp
	$(CC) -o $(OUT_DIR)/c6 $(OUT_DIR)/common single_byte_xor.cpp c6.cpp

c7: dir common crypto_func c7.cpp
	$(CC) -o $(OUT_DIR)/c7 $(OUT_DIR)/common $(OUT_DIR)/crypto_func c7.cpp $(OPENSSL_LD_LIBRARIES) $(OPENSSL_CRYPTO_LIB)

c8: dir common c8.cpp
	$(CC) -o $(OUT_DIR)/c8 $(OUT_DIR)/common c8.cpp

c9: dir common crypto_func c9.cpp
	$(CC) -o $(OUT_DIR)/c9 $(OUT_DIR)/common $(OUT_DIR)/crypto_func c9.cpp

c10: dir common crypto_func c10.cpp
	$(CC) -o $(OUT_DIR)/c10 $(OUT_DIR)/common $(OUT_DIR)/crypto_func c10.cpp

test: dir common crypto_func test_common.cpp test_challenges.cpp
	$(CC) -o $(OUT_DIR)/test $(OUT_DIR)/common test_common.cpp $(CPPUTEST_FLAGS) $(CPPUTEST_LD_LIBRARIES)
	$(CC) -o $(OUT_DIR)/test_2 $(OUT_DIR)/common $(OUT_DIR)/crypto_func test_challenges.cpp $(CPPUTEST_FLAGS) $(CPPUTEST_LD_LIBRARIES)

clean:
	rm -rf $(OUT_DIR)/*
