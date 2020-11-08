CC=g++
OUT_DIR=./out

h2b64: hex_to_base64.cpp
	if [ ! -d "./out/" ]; then mkdir $(OUT_DIR); fi
	$(CC) -o $(OUT_DIR)/h2b64 hex_to_base64.cpp

clean:
	rm -rf $(OUT_DIR)/*
