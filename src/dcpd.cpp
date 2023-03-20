#include <signal.h>     /* signal, raise, sig_atomic_t */
#include "dcpServer.h"
#include <stdio.h> /* for printf */ 
#include <stdlib.h> /* for exit */ 
#include <getopt.h>
#include <sys/file.h>
#include <errno.h>
#include <unistd.h>
#include "dcpServer.h"

const char* APPLICATION_NAME = "dcpd";
const char* APPLICATION_VERSION = "0.1.0";
const char* APPLICATION_PID = "/run/dcpd.pid";

#define DEBUG_APP     (0)

using namespace dcpservice;

bool allowRun();
int runService(serviceOptions_t& options);

// **********************************************************************
/*!
  Prints the available options to the user
*/
// **********************************************************************
static void usage()
{
  fprintf(stderr, "Usage: %s [options]\n", APPLICATION_NAME);
  fprintf(stderr, "\n");
  fprintf(stderr, "Runs the Data Logger Service\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "options:\n");
  fprintf(stderr, "  --help       Show this usage and exit\n");
  fprintf(stderr, "  -d           includes debug prompt\n");
  fprintf(stderr, "  -V           Print version number and exit\n");
  fprintf(stderr, "  -v           Enables verbose output\n");
}

int main(int argc, char* const* argv)
{
  serviceOptions_t options;

  while (1) 
  { 
    int option_index = 0; 

    static struct option long_options[] = 
    { 
      /* These options set a flag. */
      {"debug",   no_argument,       &options.debugMode, 1},
      {"verbose", no_argument,       &options.verbose, 1},
      {"brief",   no_argument,       &options.verbose, 0},
      {"version", no_argument,       0,  'V' }, 
      {"help"   , no_argument,       0,  '?' }, 
      {0,         0,                 0,  0 } 
    };

    int c = getopt_long(argc, argv, "dvV", long_options, &option_index); 
    if (c == -1)
    {
      break;
    }

    switch (c) 
    { 
    case 'V': 
      fprintf(stderr, "%s version %s\n", APPLICATION_NAME, APPLICATION_VERSION);
      exit(EXIT_SUCCESS);
      break;

    case 'v':
      options.verbose = 1; 
      break;

    case 'd':
      options.debugMode = 1;
      break;

    case '?': 
    default: 
      usage();
      exit(EXIT_SUCCESS);
      break;
    } 
  }

#if DEBUG_APP
  if (optind < argc) 
  { 
    printf("non-option ARGV-elements: "); 
    while (optind < argc) 
    {
      printf("%s ", argv[optind++]); 
    }

    printf("\n"); 
  }
#endif

  int result = EXIT_FAILURE;

  if (allowRun())
  {
    result = runService(options);
  }

  return result;
}

bool allowRun()
{
  char buffer[100];
  bool result = false;
  int pid_file = open(APPLICATION_PID, O_CREAT | O_RDWR, 0666);
  int rc = flock(pid_file, LOCK_EX | LOCK_NB);

  if (rc == 0) 
  {
    // this is the first instance
    int count = snprintf(buffer, sizeof(buffer), "%d\n", getpid());
    if (count > 0 && static_cast<size_t>(count) < sizeof(buffer))
    {
      write(pid_file, buffer, (size_t)count);
    }

    result = true;
  }
  else
  {
    fprintf(stderr, "Another instance is already running...\n");
  }
  
  return result;
}

int runService(serviceOptions_t& options)
{
  DcpServer server;
  int result;

  // run
  result = server.execute(options);

  return result;
}
