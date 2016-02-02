#ifndef DEBUG_H
#define DEBUG_H


#include <map>
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdarg>
#include <vector>

class ApplicationDebug{
public:
	ApplicationDebug();
	void setTagLength(int);
	void setDebug(bool);
	void setupTag(std::string, std::string);
	
	void log(std::string, const char*, ...);
	void log_info(const char*, ...);
	void log_error(const char*, ...);
	
private:
	bool debug;
	unsigned int tag_length;
	std::map<std::string, std::string> tag_map;
	
	std::string vformat(const char*, va_list ap);
};

#endif