#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger {
public:
	static void Init(const char* appName);
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return Instance; }
private:
	static std::shared_ptr<spdlog::logger> Instance;
};

#define LOGGER_TRACE(...) ::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOGGER_INFO(...) ::Logger::GetLogger()->info(__VA_ARGS__)
#define LOGGER_WARN(...) ::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOGGER_ERROR(...) ::Logger::GetLogger()->error(__VA_ARGS__)