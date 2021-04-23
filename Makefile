# CC=g++
CC=clang++
OUT_DIR=./out
CFLAGS=-Wall -std=c++11

dir:
	if [ ! -d "./out/" ]; then mkdir $(OUT_DIR); fi

h2b64: dir common.cpp hex_to_base64.cpp
	$(CC) -o $(OUT_DIR)/h2b64 common.cpp hex_to_base64.cpp

b642h: dir common.cpp base64_to_hex.cpp b642h.cpp
	$(CC) -o $(OUT_DIR)/b642h common.cpp base64_to_hex.cpp b642h.cpp

fxor: dir common.cpp fixed_xor.cpp fixed_xor_run.cpp
	$(CC) -o $(OUT_DIR)/fxor common.cpp fixed_xor.cpp fixed_xor_run.cpp

c3: dir common.cpp single_byte_xor.cpp c3.cpp
	$(CC) -o $(OUT_DIR)/c3 common.cpp single_byte_xor.cpp c3.cpp

c4: dir common.cpp single_byte_xor.cpp c4.cpp
	$(CC) -o $(OUT_DIR)/c4 common.cpp single_byte_xor.cpp c4.cpp

c5: dir common.cpp repeat_key_xor.cpp c5.cpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/c5 common.cpp repeat_key_xor.cpp c5.cpp

c6_hamm: dir common.cpp hamming_distance.cpp c6_hamm.cpp
	$(CC) $(CFLAGS) -o $(OUT_DIR)/c6_hamm common.cpp hamming_distance.cpp c6_hamm.cpp

c6: dir common.cpp base64_to_hex.cpp c6.cpp
	$(CC) -o $(OUT_DIR)/c6 common.cpp base64_to_hex.cpp c6.cpp

clean:
	rm -rf $(OUT_DIR)/*
