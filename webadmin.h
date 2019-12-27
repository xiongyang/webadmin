#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTimer.h>

#include "boost/variant.hpp"

#include <map>
#include <memory>
#include <thread>


typedef boost::variant<double*,bool*,int*,std::string*, uint32_t*,uint64_t*> ParameterRefType;
typedef boost::variant<double,bool,int,std::string,uint32_t, uint64_t> ParameterType;

struct WebRegisterPara
{
    int index{0};
    std::string name;
    ParameterRefType value;
    bool isReadOnly;
    std::function<void(ParameterType)> setter;
};


class WebAdminServer;

class WebAdminParaConfig
{
public:

    void startServer(int port);
    template<typename T>
    void registerPropertRO(const std::string& name, T* val)
    {
        registerPropert(name, ParameterRefType(val));
    }

    template<typename T>
    void registerPropertRW(const std::string& name, T* val)
    {
        registerPropert(name, ParameterRefType(val),   [=](ParameterType value)
        {
            *val = boost::get<T>(value);
//            LoggerInfo << "Set Prop " <<  name << " --> " << *val ;
        }
       );
    }

    void registerPropert(const std::string& name, ParameterRefType value);
    void registerPropert(const std::string& name, ParameterRefType value, std::function<void(ParameterType)>  setCaller);
    void removePropert(const std::string& name);
    std::map<std::string, WebRegisterPara*>& getPropertList();
    int getVersion();


    static WebAdminParaConfig& getInstance();
private:
    WebAdminParaConfig();
    int updateVersion;
    std::map<std::string, WebRegisterPara*>  list;


};



class WebAdminServer: public Wt::WApplication
{
public:
    struct WebAdminPara
    {
        WebRegisterPara regPara;
        Wt::WBreak* startBreak;
        Wt::WText * name;
        Wt::WText * currentVal;
        Wt::WLineEdit * newVal;
        Wt::WPushButton* setButtion;
        std::string displayValue;
    };


    WebAdminServer(const Wt::WEnvironment& env);


    void clenaAllWidget();

    void updatePropert();


    std::string getCurrentValString(WebRegisterPara* regPar);

    ParameterType getSetVal(const std::string& newValStr, ParameterRefType& setValue);

    void registerPropert(WebRegisterPara* regPar);

    void updateDisplay();

    std::vector<WebAdminPara*>  para_list;
    std::unique_ptr<Wt::WTimer> timer_;
    int currentVersion;

};
