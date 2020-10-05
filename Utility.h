#pragma once
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
class Utility
{
public:
	Utility();
	~Utility();

	static const std::string generateUUID()
	{
		boost::uuids::uuid uid = boost::uuids::random_generator()();
		const std::string uid_str = boost::uuids::to_string(uid);
		return uid_str;
	}
};
