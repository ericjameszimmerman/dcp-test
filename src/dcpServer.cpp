#include "dcpServer.h"
#include "pf_includes.h"
#include <string.h>

namespace dcpservice {

static const size_t MAX_NAME_SIZE = 32;


#if PNET_MAX_PHYSICAL_PORTS == 1
#define APP_DEFAULT_ETHERNET_INTERFACE "eth0"
#else
#define APP_DEFAULT_ETHERNET_INTERFACE "eth0"
#endif

#define APP_LOOP_RATE_US               50 * 1000
#define APP_MAIN_SLEEPTIME_US          5000 * 1000
#define APP_ETH_THREAD_PRIORITY        10
#define APP_ETH_THREAD_STACKSIZE       4096 /* bytes */
#define APP_BG_WORKER_THREAD_PRIORITY  5
#define APP_BG_WORKER_THREAD_STACKSIZE 4096 /* bytes */

static pnet_t * g_net = NULL;
static pnet_cfg_t pnet_cfg = {0};

DcpServer::DcpServer()
{
  enabled_ = false;
}

DcpServer::~DcpServer()
{
  if (g_net != NULL)
  {
    free (g_net);
    g_net = NULL;
  }
}

int DcpServer::execute(serviceOptions_t& options)
{
  int result;

  if ((result = startService()) == 0)
  {
    executeService();
  }

  shutdownService();

  return result;
}

int DcpServer::startService()
{
  int result = 0;

  LOG_DEBUG (PNET_LOG, "starting dcpd server");

  
   /* Prepare configuration */
   strcpy (pnet_cfg.station_name, "erictest");
   /*
   ret = app_utils_pnet_cfg_init_netifs (
      app_args.eth_interfaces,
      &netif_name_list,
      &number_of_ports,
      &netif_cfg);
   if (ret != 0)
   {
      exit (EXIT_FAILURE);
   }
   */
   //pnet_cfg.if_cfg = netif_cfg;
   //pnet_cfg.num_physical_ports = number_of_ports;

   /* Operating system specific settings */
   pnet_cfg.pnal_cfg.eth_recv_thread.prio = APP_ETH_THREAD_PRIORITY;
   pnet_cfg.pnal_cfg.eth_recv_thread.stack_size = APP_ETH_THREAD_STACKSIZE;
   pnet_cfg.pnal_cfg.bg_worker_thread.prio = APP_BG_WORKER_THREAD_PRIORITY;
   pnet_cfg.pnal_cfg.bg_worker_thread.stack_size =
      APP_BG_WORKER_THREAD_STACKSIZE;

   LOG_DEBUG (PNET_LOG, "API(%d): Application calls pnet_init()\n", __LINE__);

   g_net = (pnet_t *)os_malloc (sizeof (*g_net));

  memset (g_net, 0, sizeof (*g_net));

   g_net->cmdev_initialized = false; /* TODO How to handle that pf_cmdev_exit()
                                      is used before pf_cmdev_init()? */

   pf_scheduler_init (g_net, pnet_cfg.tick_us);
   if (pf_eth_init (g_net, &pnet_cfg) != 0)
   {
      LOG_ERROR (
         PNET_LOG,
         "API(%d): Failed to initialise network interfaces\n",
         __LINE__);
      return -1;
   }

   pf_bg_worker_init (g_net);
   pf_cmina_init (g_net); /* Read from permanent pool */

   pf_dcp_exit (g_net); /* Prepare for re-init. */
   pf_dcp_init (g_net); /* Start DCP */
   pf_port_init (g_net);
   pf_port_main_interface_init (g_net);
   pf_lldp_init (g_net);
   pf_pdport_init (g_net);

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
    os_usleep(APP_LOOP_RATE_US);
  }
}


void DcpServer::shutdownService()
{
  LOG_DEBUG (PNET_LOG, "dcpd stopping...\n");
  enabled_ = false;
  LOG_DEBUG (PNET_LOG, "dcpd stopped");
}


}

