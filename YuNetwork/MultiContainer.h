#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace YuNetwork {


enum class MultiTypes {

	INT,
	DOUBLE,
	FLOAT,
	STRING,
	BOOL

};

class MultiContainer
{
public:
	MultiContainer() {
	}

	~MultiContainer(void) {

	}


	void reset() {
		parsingMap.clear();
		intValues.clear();
		doubleValues.clear();
		floatValues.clear();
		stringValues.clear();
		boolValues.clear();
	}


	void addBoolVar(const char* str) {
		parsingMap[str] = MultiTypes::BOOL;
		boolValues[str] = false;
	}
	void addIntVar(const char* str) {
		parsingMap[str] = MultiTypes::INT;
		intValues[str] = 0;
	}
	void addDoubleVar(const char* str) {
		parsingMap[str] = MultiTypes::DOUBLE;
		doubleValues[str] = 0;
	}
	void addFloatVar(const char* str) {
		parsingMap[str] = MultiTypes::FLOAT;
		floatValues[str] = 0;
	}
	void addStringVar(const char* str) {
		parsingMap[str] = MultiTypes::STRING;
		stringValues[str] = ":)";
	}

	void setVar(const char* str, bool flag) {
		if(boolValues.find(str) != boolValues.end()) {
			boolValues[str] = flag;
		}
	}
	void setVar(const char* str, int value) {
		if(intValues.find(str) != intValues.end()) {
			intValues[str] = value;
		}
	}
	void setVar(const char* str, double value) {
		if(doubleValues.find(str) != doubleValues.end()) {
			doubleValues[str] = value;
		}
	}
	void setVar(const char* str, float value) {
		if(floatValues.find(str) != floatValues.end()) {
			floatValues[str] = value;
		}
	}
	void setStringVar(const char* str, std::string &value) {
		if(stringValues.find(str) != stringValues.end()) {
			stringValues[str] = value;
		}
	}

	bool getBoolVar(const char* str) {
		return boolValues[str];
	}
	int getIntVar(const char* str) {
		return intValues[str];
	}
	double getDoubleVar(const char* str) {
		return doubleValues[str];
	}
	float getFloatVar(const char* str) {
		return floatValues[str];
	}
	std::string getStringVar(const char* str) {
		return stringValues[str];
	}

	std::map<std::string, MultiTypes>* getParsingMap() {

		return &parsingMap;
	}

private:
	std::map<std::string,MultiTypes> parsingMap;
	//std::vector<std::pair<std::string, std::string>> parsingMap;
	std::map<std::string, int> intValues;
	std::map<std::string, double> doubleValues;
	std::map<std::string, float> floatValues;
	std::map<std::string, bool> boolValues;
	std::map<std::string, std::string> stringValues;

};

}