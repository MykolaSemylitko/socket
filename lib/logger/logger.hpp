#ifndef  __MY_LOGGER_HPP__
#define __MY_LOGGER_HPP__

#include <mutex>
#include <string>
#include <stdio.h>

namespace my
{
	namespace logger
	{
		class Logger
		{
		private:
			static std::mutex locker;
			const std::string name;

		public:
			Logger(std::string _name) : name(_name)
			{
			}

			Logger(Logger&& other) = delete;
			Logger(const Logger& other) = delete;
			Logger& operator= (Logger&& other) = delete;
			Logger& operator= (const Logger& other) = delete;

			template<typename... Args> void info(const char* f, Args... args)
			{
				std::unique_lock<std::mutex> lock(locker);
				printf("%s: Info: ", name.c_str());
				printf(f, args...);
			}

			template<typename... Args> void error(const char* f, Args... args)
			{
				std::unique_lock<std::mutex> lock(locker);
				printf("%s: Error: ", name.c_str());
				printf(f, args...);
			}

			template<typename... Args> void debug(const char* f, Args... args)
			{
				std::unique_lock<std::mutex> lock(locker);
				printf("%s: Debug: ", name.c_str());
				printf(f, args...);
			}

			template<typename... Args> void critical(const char* f, Args... args)
			{
				std::unique_lock<std::mutex> lock(locker);
				printf("%s: Critical: ", name.c_str());
				printf(f, args...);
			}

		};
	}
}

#endif // ! _MY_LOGGER_HPP_
