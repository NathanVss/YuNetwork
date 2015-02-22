#pragma once

#include <string>

namespace YuNetwork {

class StringStream
{
public:
	StringStream(void) {
		offset = 0;
	}
	~StringStream(void) {

	}

	void add(int value) {
		stream += ';' + std::to_string(value);
	}
	void add(float value) {
		stream += ';' + std::to_string(value);
	}
	void add(double value) {
		stream += ';' + std::to_string(value);
	}
	void add(std::string str) {
		stream += ';' + str;
	}

	int readInt() {
		return std::stoi(readToNext());
	}
	bool readBool() {
		return (bool)std::stoi(readToNext());
	}
	double readDouble() {
		return std::stod(readToNext());
	}
	float readFloat() {
		return std::stof(readToNext());
	}
	std::string readString() {
		return readToNext();
	}

	std::string readToNext() {
		std::string msg;

		int k = offset + 1;

		if(k == stream.size()) {
			return "0";
		}

		while(k != stream.size() && stream[k] != ';') {

			
			msg.push_back(stream[k]);
			k++;
		}
		offset = k;

		int b = 0;

		return msg;
	}
	std::string& getStream() {
		return stream;
	}
	void setStream(std::string &str) {
		stream = str;
	}
private:
	int offset;
	std::string stream;
};


}