#include "webadminparaconfig.h"
#include "webadminParaConfigImpl.h"

WebAdminParaConfig & WebAdminParaConfig::getInstance()
{
	static WebAdminParaConfig inst;
	return inst;
}

void WebAdminParaConfig::startServer(int port)
{
	WebAdminParaConfigImpl::getInstance().startServer(port);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, double * value, std::function<void(double)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, double * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, double * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, float * value, std::function<void(float)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, float * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, float * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, bool * value, std::function<void(bool)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, bool * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, bool * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, int32_t * value, std::function<void(int32_t)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, int32_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, int32_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}


void WebAdminParaConfig::registerPropertRW(const std::string & name, uint32_t * value, std::function<void(uint32_t)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, uint32_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, uint32_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, uint64_t * value, std::function<void(uint64_t)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, uint64_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, uint64_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, int64_t * value, std::function<void(int64_t)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, int64_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, int64_t * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, std::string * value, std::function<void(std::string)> setter)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value, setter);
}

void WebAdminParaConfig::registerPropertRW(const std::string & name, std::string * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRW(name, value);
}

void WebAdminParaConfig::registerPropertRO(const std::string & name, std::string * value)
{
	WebAdminParaConfigImpl::getInstance().registerPropertRO(name, value);
}
