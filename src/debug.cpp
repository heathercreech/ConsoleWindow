#include "debug.h"

ApplicationDebug::ApplicationDebug() : tag_map(){
	tag_length = 10;
	debug = true;
	
	setupTag("info", "[INFO]");
	setupTag("error", "[ERROR]");
}

void ApplicationDebug::setDebug(bool d){
	debug = d;
}

void ApplicationDebug::setupTag(std::string tag_name, std::string tag_content){
	std::string new_tag_content = tag_content;

	while(new_tag_content.length() < tag_length){
		new_tag_content += " ";
	}
	tag_map[tag_name] = new_tag_content;
}


void ApplicationDebug::setTagLength(int length){
	tag_length = length;
}

std::string ApplicationDebug::vformat(const char* fmt, va_list ap){
	size_t size = 1024;
	char buf[size];
	
	va_list apcopy;
	va_copy(apcopy, ap);
	unsigned int needed = vsnprintf(&buf[0], size, fmt, ap);
	
	if(needed <= size && needed >= 0){
		return std::string (&buf[0]);
	}else{
		std::vector<char> buf;
		size = needed;
		buf.resize(size);
		needed = vsnprintf(&buf[0], size, fmt, apcopy);
		return std::string (&buf[0]);
	}
}

void ApplicationDebug::log(std::string tag, const char* content, ...){
	if(debug){
		va_list ap;
		va_start(ap, content);
		
		std::string buffer = vformat(content, ap);
		va_end(ap);
		
		std::string printed_string = tag_map[tag] + buffer + "\n";
		
		std::cout << printed_string;
	}
}

void ApplicationDebug::log_info(const char* content, ...){
	va_list ap;
	va_start(ap, content);
	
	log("info", content, ap);
	va_end(ap);
}

void ApplicationDebug::log_error(const char* content, ...){
	va_list ap;
	va_start(ap, content);
	
	log("error", content, ap);
	va_end(ap);
}