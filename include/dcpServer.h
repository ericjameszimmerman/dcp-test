#ifndef DCPSERVICE_dcpServer_H
#define DCPSERVICE_dcpServer_H

#include <unordered_map>
#include <memory>
#include <mutex>

namespace dcpservice {

typedef struct serviceOptions
{
  int verbose;
  int debugMode;

  serviceOptions()
  {
    verbose = 0;
    debugMode = 0;
  }

} serviceOptions_t;

class DcpServer
{
public:
  DcpServer();

  int execute(serviceOptions_t& options);
  
private:
  void periodic();
  int startService();
  void executeService();
  void shutdownService();
  void onBackgroundInterval();
};

} // namespace dcpservice

#endif
