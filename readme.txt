webadmin库
给c++程序添加一个内置的网页服务器 实现对变量的显示与控制

依赖库
boost  只依赖头文件库   基于 1.68开发,最新的应该也没有问题
Wt库   https://www.webtoolkit.eu/wt/download    基于4.1.2开发 但是应该换成最新的也没问题
Wt库 下载后直接 configure & make & make install 安装到系统文件夹(或者在编译项目时设置对应的头文件和库)  
C++11 支持需要打开

Wt的编译:
wt要求 boost 1.50.0 GCC5.1 或者 clang3.3 以上 cmake3
centos 7 默认版本只有4.8.5 不满足要求,所以需要在编译wt之前安装更高的工具链
首先通过yum安装 gcc7
sudo yum install centos-release-scl-rh centos-release-scl scl scl-utils
sudo yum install  devtoolset-7-toolchain
source /opt/rh/devtoolset-7/enable      //这个命令启用gcc7工具链,只是本会话有效,如果需要长期有效,需要把它添加到 .bashrc里面

安装 cmake3
sudo yum install cmake3

然后解压源码包   tar xf wt-4.1.2.tar.gz
然后 cd wt-4.1.2 ;mkdir build; cd build;   cmake3  -DENABLE_SSL=OFF ../  ;make;make install     // (SSL 编译有问题,未解决)
编译安装完毕后,可以不再用 gcc7.  后续demo程序也不需要更高版本的glibc等
后续程序使用 gcc 4.8.5 可以正常编译使用.


重新登陆 切换回 gcc 4.8.5 例子程序编译命令  需要添加boost与 wt的头文件目录   并链接 wt wthttp
g++ test_main.cpp webadmin.cpp -std=c++11 -I/home/xiong/boost_1_68_0 -I/usr/local/include -lwt -lwthttp  

使用方法.

静态方法取得注册变量的实例, 最好在main函数,单线程部分做首次调用, 该单例方法未作线程保护
WebAdminParaConfig& cfg = WebAdminParaConfig::getInstance();


启动一个内置的web服务器,并监听47850端口  该方法不能重复调用
cfg.startServer(47850);


注册一个 ReadWrite 属性
    double var = 1;
    cfg.registerPropertRW("Var", &var);

注册一个 ReadOnly属性
     cfg.registerPropertRO("DemoClass Var2", &var2);

属性的种类目前支持   bool std::string double int, uint32_t, uint64_t
如果有新的属性种类,需要手动修改代码添加


所有属性注册时间没有限制. 可以在程序运行过程中动态添加属性和去掉属性

所有属性在页面上按照字典顺序排序
显示页面更新频率为1秒


默认的最大session为 10, 未作鉴权,所以只能在安全网络下使用

默认的客户端刷新机制为ajax, 可以通过改变 /etc/wt/wt_config.xml 中
<web-sockets>false</web-sockets>  为 true 启用 websocket 来提高效率.

做了一些基本简单的测试,基本满足需求,没有做更进一步的测试



编译链接库之后,如果不调用 cfg.startServer(47850);  不会产生开销
http服务器会启动自己的线程.  设置属性会从他自己的线程直接设置. 如果有必要,设置属性时可能需要加锁

这个时候可以调用
 void cfg::registerPropert(const std::string& name, ParameterRefType value, std::function<void(ParameterType)>  setCaller);
方法,设置更新函数对象 


