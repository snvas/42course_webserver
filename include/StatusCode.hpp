#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include "CommonLibs.hpp"

class StatusCode {
      public:
	StatusCode();
	~StatusCode();
	std::string getStatusCode(int code);
	void setStatusCode(int code, const std::string& message);
	StatusCode& operator=(const StatusCode& other);
	StatusCode(const StatusCode &other);

      private:
	std::map<int, std::string> _statusCode;
};

#endif
