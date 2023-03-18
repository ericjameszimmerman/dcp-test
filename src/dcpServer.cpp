#include "dcpServer.h"

namespace dcpservice {

static const milliseconds_t LOOP_RATE = 50;
static const size_t MAX_NAME_SIZE = 32;

DcpServer::DcpServer()
{
  enabled_ = false;
}

err_t DcpServer::execute(serviceOptions_t& options)
{
  err_t result;

  if ((result = startService()) == ERR_OK)
  {
    executeService();
  }

  shutdownService();

  return result;
}

err_t DcpServer::startService()
{
  err_t result = ERR_OK;

  platform::log("starting dcpd server");

  return result;
}

void DcpServer::periodic()
{
  
}
  
void DcpServer::executeService()
{
  // sleep forever until process is manually killed
  while(enabled_)
  {
    periodic();
    platform::msleep(LOOP_RATE);  // FUTURE: adjust base rate as needed
  }
}


void DcpServer::shutdownService()
{
  platform::log("dcpd stopping...");
  enabled_ = false;
  platform::log("dcpd stopped");
}


}

