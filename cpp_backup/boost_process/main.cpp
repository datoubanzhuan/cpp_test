#include <pthread.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <boost/process/group.hpp>
#include <boost/process.hpp>
#include <thread>

namespace bp = boost::process;
using namespace boost::process;
int main (int argc, char *argv[])
{
   bp::group g;
   bp::pid_t cpid;
   {
      bp::child c("./run.sh");
      // std::cout << "wait for terminate, child id: " << c.id() << ", current id: " << boost::this_process::get_id() << std::endl;
      // if not exit, then terminate
      std::cout << "detach" << std::endl;

      c.detach();
      cpid = c.id();
   }
   // bp::child c(cpid);
   // std::cout << "add" << std::endl;

   // g.add(c);
   std::cout << "start terminate" << std::endl;
   // g.terminate();
   std::cout << "have terminate" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(7));
   // c.wait();
   std::this_thread::sleep_for(std::chrono::seconds(1000));
}
