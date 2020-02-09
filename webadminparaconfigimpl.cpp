#include "webadminparaconfigimpl.h"
#include <cstdint>
#include <boost/algorithm/string.hpp>
#include <Wt/WTreeNode.h>
using namespace Wt;

void WebAdminParaConfigImpl::startServer(int port)
{
    static char buf[32];        // because it sim the argc. it shoule keep valid for whole lift of program
    sprintf(buf, "--http-port=%d", port);

    const char* httpArgv[] =
    {
        "wt"  ,   "--http-address=0.0.0.0", buf  , "--docroot=."
    };

    auto httpthreadfun = [=]()
    {
        int argc = sizeof(httpArgv) / 8;
        Wt::WRun(argc, (char**)httpArgv, [&](const Wt::WEnvironment &env) {
            /*
                 * You could read information from the environment to decide whether
                 * the user has permission to start a new application
                 */

            return  Wt::cpp14::make_unique<WebAdminServer>(env);
            });
    };

    std::thread httpthread(httpthreadfun);
    httpthread.detach();
}

void WebAdminParaConfigImpl::registerPropert(const std::string &name, ParameterRefType value)
{
    auto p = new WebRegisterPara;
    p->name = name;
    p->value = value;
    p->isReadOnly = true;
    list[name] = p;
    updateVersion++;
}

void WebAdminParaConfigImpl::registerPropert(const std::string &name, ParameterRefType value, std::function<void(ParameterType)> setCaller)
{
    auto p = new WebRegisterPara;
    p->name = name;
    p->value = value;
    p->setter = setCaller;
    p->isReadOnly = false;
    list[name] = p;
    updateVersion++;
}

void WebAdminParaConfigImpl::removePropert(const std::string &name)
{
    list.erase(name);
    updateVersion++;
}

std::map<std::string, WebRegisterPara *> &WebAdminParaConfigImpl::getPropertList() {
    return list;
}

int WebAdminParaConfigImpl::getVersion()
{
    return updateVersion;
}

WebAdminParaConfigImpl &WebAdminParaConfigImpl::getInstance()
{
    static WebAdminParaConfigImpl inst;
    return inst;
}

WebAdminParaConfigImpl::WebAdminParaConfigImpl()
{
    updateVersion = 0;
}

void WebAdminServer::initTable()
{
    auto treeTable  =  root()->addWidget(Wt::cpp14::make_unique<Wt::WTreeTable>());

   // treeTable->resize(650, 200);
    treeTable->setWidth(650);
    treeTable->tree()->setSelectionMode(SelectionMode::Extended);
    treeTable->addColumn("Value", 125);
    treeTable->addColumn("NewValue", 125);
    treeTable->addColumn("Set", 125);

    auto root = cpp14::make_unique<WTreeTableNode>("All");
    tableroot =  root.get();
    treeTable->setTreeRoot(std::move(root), "Config Table");
}

WebAdminServer::WebAdminServer(const Wt::WEnvironment &env)
    : WApplication(env)
{
    setTitle("WebAdminSever");

    currentVersion = -1;

    timer_ = Wt::cpp14::make_unique<Wt::WTimer>();
    timer_->setInterval(std::chrono::seconds(1));
    timer_->timeout().connect(this, &WebAdminServer::updateDisplay);
    timer_->start();


    initTable();
   // std::cout << " =====================    Start WebAdmin Server " << std::endl;
}

void WebAdminServer::clenaAllWidget()
{
    root()->clear();
    initTable();

    for (auto& each : para_list)
    {
        WebAdminPara& para = *each;
        delete each;
    }
    para_list.clear();
}

void WebAdminServer::updatePropert()
{
    if (currentVersion < WebAdminParaConfigImpl::getInstance().getVersion())
    {
        currentVersion = WebAdminParaConfigImpl::getInstance().getVersion();
        clenaAllWidget();
        //copy avoid thread race
        std::map<std::string, WebRegisterPara*>  list = WebAdminParaConfigImpl::getInstance().getPropertList();
        for (auto& eachPair : list)
        {
            auto each = eachPair.second;
            registerPropert(each);
        }
    }
}

std::string WebAdminServer::getCurrentValString(WebRegisterPara *regPar)
{
    std::string ValString;

    if (regPar->value.type() == typeid (int32_t*))
    {
        ValString = std::to_string(*boost::get<int32_t*>(regPar->value));
    }
    else if (regPar->value.type() == typeid (int64_t*))
    {
        ValString = std::to_string(*boost::get<int64_t*>(regPar->value));
    }
    else if (regPar->value.type() == typeid (double*))
    {
        ValString = std::to_string(*boost::get<double*>(regPar->value));
    }
    else if (regPar->value.type() == typeid (float*))
    {
        ValString = std::to_string(*boost::get<float*>(regPar->value));
    }
    else if (regPar->value.type() == typeid (bool*))
    {
        ValString = std::to_string(*boost::get<bool*>(regPar->value));
    }
    else if (regPar->value.type() == typeid (uint32_t*))
    {
        ValString = std::to_string(*boost::get<uint32_t*>(regPar->value));
    }
    else if (regPar->value.type() == typeid (uint64_t*))
    {
        ValString = std::to_string(*boost::get<uint64_t*>(regPar->value));
    }

    else if (regPar->value.type() == typeid (std::string*))
    {
        ValString = *boost::get<std::string*>(regPar->value);
    }
    return ValString;
}

ParameterType WebAdminServer::getSetVal(const std::string &newValStr, ParameterRefType &setValue)
{
    ParameterType ret;
    if (setValue.type() == typeid (int32_t*))
    {
        int32_t v = std::stoi(newValStr);
        ret = v;
    }
    else if (setValue.type() == typeid (uint32_t*))
    {
        uint32_t v = std::stoul(newValStr);
        ret = v;
    }
    else if (setValue.type() == typeid (int64_t*))
    {
        int64_t v = std::stoll(newValStr);
        ret = v;
    }
    else if (setValue.type() == typeid (uint64_t*))
    {
        uint64_t v = std::stoull(newValStr);
        ret = v;
    }
    else if (setValue.type() == typeid (double*))
    {
        ret = std::stod(newValStr);
    }
    else if (setValue.type() == typeid (float*))
    {
        float v = std::stod(newValStr);
        ret = v;
    }
    else if (setValue.type() == typeid (bool*))
    {
        ret = bool(std::stoi(newValStr));
    }
    else if (setValue.type() == typeid (std::string*))
    {
        ret = newValStr;
    }
    return ret;
}

void WebAdminServer::registerPropert(WebRegisterPara *regPar)
{
    WebAdminPara* p = new WebAdminPara;
    WebAdminPara& para = *p;
    para.regPara = *regPar;

    std::string valString = getCurrentValString(regPar);

    std::vector<std::string> nameFields;
    boost::algorithm::split(nameFields,para.regPara.name, boost::is_any_of("."));
    if(nameFields.size() == 0)
    {
         //std::cout << " =====================   NodeAdd With Error Name " << para.regPara.name << "\n";

        //emptry nothing to do;
    }
    else if(nameFields.size() == 1)
    {
        //direct child;
       // std::cout << "===================== NodeAdd With Global Name " << para.regPara.name << "\n";
        auto tableItem = addNode(tableroot,para.regPara.name, valString, para.regPara.isReadOnly);
        para.displayValue = valString;
        para.currentVal = (Wt::WText*)tableItem->columnWidget(1);
        if(!para.regPara.isReadOnly)
        {
            para.setButtion = (Wt::WPushButton*)tableItem->columnWidget(3);
            para.newVal = (Wt::WLineEdit*)tableItem->columnWidget(2);

            para.setButtion->clicked().connect([=]() {
                std::string newVal = p->newVal->text().narrow();
                //std::cout << "Update " << p->regPara.name << " To " << newVal;
                ParameterType newValue = getSetVal(newVal, regPar->value);
                p->regPara.setter(newValue);
            }
            );
        }
    }
    else
    {
      //  std::cout << "===================== NodeAdd With SubNode Name " << para.regPara.name << "\n";
        WTreeTableNode* currentParent = tableroot;
        for(std::size_t i = 0; i != nameFields.size() - 1; ++i)
        {
            const std::string& subNodeName = nameFields[i];

            WTreeTableNode* child = nullptr;
            auto childnodes = currentParent->childNodes();
            for (auto each : childnodes) {
            //    std::cout << " =======================  SubObjec Name " << each->objectName() << "\n";
                if(each->objectName() == subNodeName)
                {
                    child = (WTreeTableNode*)each;
                    break;
                }
            }

            if(child == nullptr)
            {
                auto newnode = cpp14::make_unique<WTreeTableNode>(subNodeName);
                child = newnode.get();
                child->setObjectName(subNodeName);
                currentParent->addChildNode(std::move(newnode));
            }
            currentParent = ( WTreeTableNode*)child;
        }

        const std::string& leafName = nameFields[nameFields.size() - 1];

        auto tableItem = addNode(currentParent, leafName, valString,para.regPara.isReadOnly);
        para.displayValue = valString;
        para.currentVal = (Wt::WText*)tableItem->columnWidget(1);
        if(!para.regPara.isReadOnly)
        {
            para.setButtion = (Wt::WPushButton*)tableItem->columnWidget(3);
            para.newVal = (Wt::WLineEdit*)tableItem->columnWidget(2);

            para.setButtion->clicked().connect([=]() {
                std::string newVal = p->newVal->text().narrow();
                //std::cout << "Update " << p->regPara.name << " To " << newVal;
                ParameterType newValue = getSetVal(newVal, regPar->value);
                p->regPara.setter(newValue);
            }
            );
        }
    }


    para_list.push_back(p);
}

void WebAdminServer::updateDisplay()
{
    updatePropert();
    //  std::cout  << "update Display \n" ;
    for (auto& each : para_list)
    {
        std::string valString = getCurrentValString(&each->regPara);
        if (valString != each->displayValue)
        {
            //std::cout << " Set Text display " << *each->value << "\n";
            each->currentVal->setText(valString);
            each->displayValue = valString;
        }
    }
}
