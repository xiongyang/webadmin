#include "webadmin.h"

#include <string>
#include <thread>
#include <functional>
#include <memory>
#include <iostream>
#include <vector>
#include <map>



struct DemoClass
{
    int var1;
    int var2;
    bool var3;
    std::string var4;
    double var5;

    DemoClass()
    {
        var1 = 0;
        var2 = 100;
        registerProperty();
    }
    void registerProperty()
    {
        WebAdminParaConfig& cfg = WebAdminParaConfig::getInstance();
        cfg.registerPropertRW("DemoClass Var1", &var1);
        cfg.registerPropertRO("DemoClass Var2", &var2);

        cfg.registerPropertRW("DemoClass Var3", &var3);
        cfg.registerPropertRW("DemoClass Var4", &var4);
        cfg.registerPropertRW("DemoClass Var5", &var5);
    }

    void updateVar()
    {
        var1 += 1;
         var2 += 1;
    }


};


int main(int argc , char** argv)
{
    bool g_isRunging = true;

    WebAdminParaConfig& cfg = WebAdminParaConfig::getInstance();
    // startServer at port
    cfg.startServer(47850);


    //register property

    DemoClass inst;


    double var = 1;
    cfg.registerPropertRW("Var", &var);


    std::string testdisplay("IC2003");
    cfg.registerPropertRW("Inst", &testdisplay);


    bool isStopEnter = true;
    cfg.registerPropertRW("iStopEnter", &isStopEnter);



    while(g_isRunging)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        inst.updateVar();
    }
    return 0;

}
