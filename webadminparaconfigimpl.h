#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTimer.h>
#include <Wt/WIconPair.h>
#include <Wt/WTree.h>
#include <Wt/WTreeTable.h>
#include <Wt/WTreeTableNode.h>

#include "boost/variant.hpp"

#include <map>
#include <memory>
#include <thread>
#include <string>
#include <functional>

using namespace Wt;

typedef boost::variant<double*,float*, bool*, int32_t*, int64_t*, std::string*, uint32_t*, uint64_t*> ParameterRefType;
typedef boost::variant<double,float, bool, int32_t, int64_t,std::string, uint32_t, uint64_t> ParameterType;

struct WebRegisterPara
{
    std::string name;
    ParameterRefType value;
    bool isReadOnly;
    std::function<void(ParameterType)> setter;
};


class WebAdminServer;

class WebAdminParaConfigImpl
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
        registerPropert(name, ParameterRefType(val), [=](ParameterType value)
            {
                *val = boost::get<T>(value);
                //            LoggerInfo << "Set Prop " <<  name << " --> " << *val ;
            }
        );
    }

    template<typename T>
    void registerPropertRW(const std::string& name, T* val, std::function<void(T)> setter)
    {
        registerPropert(name, ParameterRefType(val), [=](ParameterType value)
            {
                T temp = boost::get<T>(value);
                setter(temp);
            });
    }

    void registerPropert(const std::string& name, ParameterRefType value);
    void registerPropert(const std::string& name, ParameterRefType value, std::function<void(ParameterType)>  setCaller);
    void removePropert(const std::string& name);
    std::map<std::string, WebRegisterPara*>& getPropertList();
    int getVersion();


    static WebAdminParaConfigImpl& getInstance();
private:
    WebAdminParaConfigImpl();
    int updateVersion;
    std::map<std::string, WebRegisterPara*>  list;
};



//class TreeTableExample : public Wt::WApplication
//{


//public:



//    explicit TreeTableExample(const Wt::WEnvironment& env)
//        : WApplication(env)
//    {



////        auto group = cpp14::make_unique<WTreeTableNode>("Upper Management");
////        WTreeTableNode *group_ = group.get();

////        treeTable->treeRoot()->addChildNode(std::move(group));
////        addNode(group_, "Chief Anything Officer", "-2.8");
////        addNode(group_, "Vice President of Parties", "13.57");
////        addNode(group_, "Vice President of Staplery", "3.42");

////        group = cpp14::make_unique<WTreeTableNode>("Middle management");
////        group_ = group.get();

////        treeTable->treeRoot()->addChildNode(std::move(group));
////        addNode(group_, "Boss of the house", "9.78");
////        addNode(group_, "Xena caretaker", "8.66");

////        group = cpp14::make_unique<WTreeTableNode>("Actual Workforce");
////        group_ = group.get();

////        treeTable->treeRoot()->addChildNode(std::move(group));
////        addNode(group_, "The Dork Vice", "9.78");
////        addNode(group_, "The Stud", "8.66");
////        addNode(group_, "The Ugly", "13.0");
////        treeTable->treeRoot()->expand();
//    }


//};



class WebAdminServer : public Wt::WApplication
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

    WTreeTableNode* tableroot;

    WTreeTableNode *addNode(WTreeTableNode *parent, const std::string&  name,
                            const std::string& value, bool isReadOnly) {
        std::cout << "Add Table Node " << name << "\n";
        auto node = cpp14::make_unique<WTreeTableNode>(name);
        auto node_ = node.get();
        parent->addChildNode(std::move(node));
        auto v =   cpp14::make_unique<WText>(value);
        node_->setColumnWidget(1, std::move(v));
        if(!isReadOnly)
        {
            node_->setColumnWidget(2, cpp14::make_unique<WLineEdit>(value));
            node_->setColumnWidget(3, Wt::cpp14::make_unique<Wt::WPushButton>("Set"));
        }
        return node_;
    }
private:
    void initTable();
};
