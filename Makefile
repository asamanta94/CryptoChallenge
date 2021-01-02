CC=g++
OUT_DIR=./out

dir:
	if [ ! -d "./out/" ]; then mkdir $(OUT_DIR); fi

h2b64: dir common.cpp hex_to_base64.cpp
	$(CC) -o $(OUT_DIR)/h2b64 common.cpp hex_to_base64.cpp

fxor: dir common.cpp fixed_xor.cpp fixed_xor_run.cpp
	$(CC) -o $(OUT_DIR)/fxor common.cpp fixed_xor.cpp fixed_xor_run.cpp

c3: dir common.cpp single_byte_xor.cpp c3.cpp
	$(CC) -o $(OUT_DIR)/c3 common.cpp single_byte_xor.cpp c3.cpp

c4: dir common.cpp single_byte_xor.cpp c4.cpp
	$(CC) -o $(OUT_DIR)/c4 common.cpp single_byte_xor.cpp c4.cpp

clean:
	rm -rf $(OUT_DIR)/*
