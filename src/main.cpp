#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <string.h>
#include <stdlib.h> 
#include <iomanip>

template<typename T>
std::string int_to_hex(T i);

long encode(char character, std::time_t cts = std::time(nullptr), int salt = 0) {
	if (salt != 0) return (character + cts)*salt;
	else return (int)character+cts;
}

char decode(long encodedchar, std::time_t ts, int salt = 0) {
	if (salt != 0) return (char) ((encodedchar/salt) - ts);
	else return (char) encodedchar - ts;
}

std::vector<long> encode(std::string msg, std::time_t cts = std::time(nullptr), int salt = 0) {
	std::vector<long> vec;
	for (const char &c: msg) {
		vec.push_back(encode(c, cts, salt));
	}
	return vec;
}

std::string decode(std::vector<long> encodedmsg, std::time_t ts, int salt = 0) {
	std::string str;
	for (const long &l: encodedmsg) {
		str += decode(l, ts, salt);
	}
	return str;
}

void handle_args(int index, int argc, char **argv, std::time_t ts = std::time(nullptr), int salt = 0, bool h = false) {
	if (argc > 1) {
		if (strcmp("-h", argv[index])==0) {
			handle_args(index+1, argc, argv, ts, salt, true);
		} else if (strcmp("-s", argv[index])==0) {
			handle_args(index+2, argc, argv, ts, atoi(argv[index+1]), h);
		} else if (strcmp("-t", argv[index])==0) {
			handle_args(index+2, argc, argv, (std::time_t)atol(argv[index+1]), salt, h);
		} else if (strcmp("-e", argv[index])==0) {
			std::string msg;
			for (int i = index+1; i < argc; i++) {
				msg.append(argv[i]);
			}
			for (const long &l: encode(msg, ts, salt)) {
				if (h) std::cout << "0x" << std::hex << l << " ";
				else std::cout << l << " ";
			}
			std::cout << std::endl << "Encoded with timestamp: " << std::dec << ts << std::endl;
		} else if (strcmp("-d", argv[index])==0) {
			std::cout << "Decoding with timestamp: " << ts << std::endl;
			std::vector<long> encoded;
			for (int i = index+1; i < argc; i++) {
				if (h) encoded.push_back(strtol(argv[i], NULL, 16));
				else encoded.push_back(atol(argv[i]));
			}
			std::cout << decode(encoded, ts, salt) << std::endl;
		}
	}
}

int main(int argc, char **argv) {
	handle_args(1, argc, argv);
}
