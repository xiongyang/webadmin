#ifndef WEBADMINPARACONFIG_H_
#define WEBADMINPARACONFIG_H_
#include <cstdint>
#include <string>
#include <functional>
class WebAdminParaConfigImpl;
class WebAdminParaConfig
{
public:

	static WebAdminParaConfig& getInstance();
	void startServer(int port);

	//for pack it to library and remove depency of boost include.
	void registerPropertRW(const std::string& name, double* value, std::function<void(double)>);
	void registerPropertRW(const std::string& name, double* value);
	void registerPropertRO(const std::string& name, double* value);

	void registerPropertRW(const std::string& name, float* value, std::function<void(float)>);
	void registerPropertRW(const std::string& name, float* value);
	void registerPropertRO(const std::string& name, float* value);

	void registerPropertRW(const std::string& name, bool* value, std::function<void(bool)>);
	void registerPropertRW(const std::string& name, bool* value);
	void registerPropertRO(const std::string& name, bool* value);


	void registerPropertRW(const std::string& name, int32_t* value, std::function<void(int32_t)>);
	void registerPropertRW(const std::string& name, int32_t* value);
	void registerPropertRO(const std::string& name, int32_t* value);

	void registerPropertRW(const std::string& name, int64_t* value, std::function<void(int64_t)>);
	void registerPropertRW(const std::string& name, int64_t* value);
	void registerPropertRO(const std::string& name, int64_t* value);

	void registerPropertRW(const std::string& name, uint32_t* value, std::function<void(uint32_t)>);
	void registerPropertRW(const std::string& name, uint32_t* value);
	void registerPropertRO(const std::string& name, uint32_t* value);

	void registerPropertRW(const std::string& name, uint64_t* value, std::function<void(uint64_t)>);
	void registerPropertRW(const std::string& name, uint64_t* value);
	void registerPropertRO(const std::string& name, uint64_t* value);

	void registerPropertRW(const std::string& name, std::string* value, std::function<void(std::string)>);
	void registerPropertRW(const std::string& name, std::string* value);
	void registerPropertRO(const std::string& name, std::string* value);

};
#endif  // WEBADMINPARACONFIG_H_