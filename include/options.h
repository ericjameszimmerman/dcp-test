#ifndef OPTIONS_H
#define OPTIONS_H

#define PNET_EXPORT
#define PNET_MAX_PHYSICAL_PORTS          1
#define PNET_MAX_LOG_BOOK_ENTRIES   16
#define PNET_MAX_SESSION_BUFFER_SIZE 4500
#define PNET_MAX_DIRECTORYPATH_SIZE 240
#define PNET_MAX_FILENAME_SIZE 30
#define PNET_MAX_PORT_DESCRIPTION_SIZE 60
#define PNET_MAX_DIAG_MANUF_DATA_SIZE 16
#define PNET_MAX_ALARM_PAYLOAD_DATA_SIZE 28
#define PNET_MAX_ALARMS             6
#define PNET_MAX_ALARM_PAYLOAD_DATA_SIZE 28
#define PNET_MAX_AR                 1
#define PNET_MAX_API                1
#define PNET_MAX_CR                 2
#define PNET_MAX_SLOTS            5
#define PNET_MAX_SUBSLOTS         3
#define PNET_MAX_DFP_IOCR           2
#define PNET_MAX_DIAG_ITEMS         200

#define CC_PACKED_BEGIN
#define CC_PACKED_END
#define CC_PACKED __attribute__ ((packed))

#define CC_FORMAT(str, arg) __attribute__ ((format (printf, str, arg)))

#ifdef __cplusplus
#define CC_STATIC_ASSERT(exp) static_assert (exp, "")
#else
#define CC_STATIC_ASSERT(exp) _Static_assert(exp, "")
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <assert.h>

#define OS_THREAD
#define OS_MUTEX
#define OS_SEM
#define OS_EVENT
#define OS_MBOX
#define OS_TIMER
#define OS_TICK


#ifdef __cplusplus
extern "C" {
#endif

typedef pthread_t os_thread_t;
typedef pthread_mutex_t os_mutex_t;

static inline void cc_assert (int exp)
{
   assert (exp); // LCOV_EXCL_LINE
}

#define CC_ASSERT(exp) cc_assert (exp)


#if BYTE_ORDER == LITTLE_ENDIAN
#define CC_TO_LE16(x)   ((uint16_t)(x))
#define CC_TO_LE32(x)   ((uint32_t)(x))
#define CC_TO_LE64(x)   ((uint64_t)(x))
#define CC_FROM_LE16(x) ((uint16_t)(x))
#define CC_FROM_LE32(x) ((uint32_t)(x))
#define CC_FROM_LE64(x) ((uint64_t)(x))
#define CC_TO_BE16(x)   ((uint16_t)__builtin_bswap16 (x))
#define CC_TO_BE32(x)   ((uint32_t)__builtin_bswap32 (x))
#define CC_TO_BE64(x)   ((uint64_t)__builtin_bswap64 (x))
#define CC_FROM_BE16(x) ((uint16_t)__builtin_bswap16 (x))
#define CC_FROM_BE32(x) ((uint32_t)__builtin_bswap32 (x))
#define CC_FROM_BE64(x) ((uint64_t)__builtin_bswap64 (x))
#else
#define CC_TO_LE16(x)   ((uint16_t)__builtin_bswap16 (x))
#define CC_TO_LE32(x)   ((uint32_t)__builtin_bswap32 (x))
#define CC_TO_LE64(x)   ((uint64_t)__builtin_bswap64 (x))
#define CC_FROM_LE16(x) ((uint16_t)__builtin_bswap16 (x))
#define CC_FROM_LE32(x) ((uint32_t)__builtin_bswap32 (x))
#define CC_FROM_LE64(x) ((uint64_t)__builtin_bswap64 (x))
#define CC_TO_BE16(x)   ((uint16_t)(x))
#define CC_TO_BE32(x)   ((uint32_t)(x))
#define CC_TO_BE64(x)   ((uint64_t)(x))
#define CC_FROM_BE16(x) ((uint16_t)(x))
#define CC_FROM_BE32(x) ((uint32_t)(x))
#define CC_FROM_BE64(x) ((uint64_t)(x))
#endif

#define CC_ATOMIC_GET8(p)  __atomic_load_n ((p), __ATOMIC_SEQ_CST)
#define CC_ATOMIC_GET16(p) __atomic_load_n ((p), __ATOMIC_SEQ_CST)
#define CC_ATOMIC_GET32(p) __atomic_load_n ((p), __ATOMIC_SEQ_CST)
#define CC_ATOMIC_GET64(p) __atomic_load_n ((p), __ATOMIC_SEQ_CST)

#define CC_ATOMIC_SET8(p, v)  __atomic_store_n ((p), (v), __ATOMIC_SEQ_CST)
#define CC_ATOMIC_SET16(p, v) __atomic_store_n ((p), (v), __ATOMIC_SEQ_CST)
#define CC_ATOMIC_SET32(p, v) __atomic_store_n ((p), (v), __ATOMIC_SEQ_CST)
#define CC_ATOMIC_SET64(p, v) __atomic_store_n ((p), (v), __ATOMIC_SEQ_CST)


typedef struct os_sem
{
   pthread_cond_t cond;
   pthread_mutex_t mutex;
   size_t count;
} os_sem_t;

typedef struct os_event
{
   pthread_cond_t cond;
   pthread_mutex_t mutex;
   uint32_t flags;
} os_event_t;

typedef struct os_mbox
{
   pthread_cond_t cond;
   pthread_mutex_t mutex;
   size_t r;
   size_t w;
   size_t count;
   size_t size;
   void * msg[];
} os_mbox_t;

typedef struct os_timer
{
   timer_t timerid;
   os_thread_t * thread;
   pid_t thread_id;
   bool exit;
   void (*fn) (struct os_timer *, void * arg);
   void * arg;
   uint32_t us;
   bool oneshot;
} os_timer_t;

typedef uint64_t os_tick_t;


#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef BIT
#define BIT(n) (1U << (n))
#endif

#ifndef NELEMENTS
#define NELEMENTS(a) (sizeof (a) / sizeof ((a)[0]))
#endif

#ifndef OS_WAIT_FOREVER
#define OS_WAIT_FOREVER 0xFFFFFFFF
#endif

#ifndef OS_MAIN
#define OS_MAIN int main
#endif

#ifndef OS_MUTEX
typedef void os_mutex_t;
#endif

#ifndef OS_SEM
typedef void os_sem_t;
#endif

#ifndef OS_THREAD
typedef void os_thread_t;
#endif

#ifndef OS_EVENT
typedef void os_event_t;
#endif

#ifndef OS_MBOX
typedef void os_mbox_t;
#endif

#ifndef OS_TIMER
typedef void os_timer_t;
#endif

#ifndef OS_TICK
typedef void os_tick_t;
#endif

void * os_malloc (size_t size);
void os_free (void * ptr);

void os_usleep (uint32_t us);
uint32_t os_get_current_time_us (void);

os_tick_t os_tick_current (void);
os_tick_t os_tick_from_us (uint32_t us);
void      os_tick_sleep (os_tick_t tick);

os_thread_t * os_thread_create (
   const char * name,
   uint32_t priority,
   size_t stacksize,
   void (*entry) (void * arg),
   void * arg);

os_mutex_t * os_mutex_create (void);
void os_mutex_lock (os_mutex_t * mutex);
void os_mutex_unlock (os_mutex_t * mutex);
void os_mutex_destroy (os_mutex_t * mutex);

os_sem_t * os_sem_create (size_t count);
bool os_sem_wait (os_sem_t * sem, uint32_t time);
void os_sem_signal (os_sem_t * sem);
void os_sem_destroy (os_sem_t * sem);

os_event_t * os_event_create (void);
bool os_event_wait (
   os_event_t * event,
   uint32_t mask,
   uint32_t * value,
   uint32_t time);
void os_event_set (os_event_t * event, uint32_t value);
void os_event_clr (os_event_t * event, uint32_t value);
void os_event_destroy (os_event_t * event);

os_mbox_t * os_mbox_create (size_t size);
bool os_mbox_fetch (os_mbox_t * mbox, void ** msg, uint32_t time);
bool os_mbox_post (os_mbox_t * mbox, void * msg, uint32_t time);
void os_mbox_destroy (os_mbox_t * mbox);

os_timer_t * os_timer_create (
   uint32_t us,
   void (*fn) (os_timer_t * timer, void * arg),
   void * arg,
   bool oneshot);
void os_timer_set (os_timer_t * timer, uint32_t us);
void os_timer_start (os_timer_t * timer);
void os_timer_stop (os_timer_t * timer);
void os_timer_destroy (os_timer_t * timer);

/* Log levels */
#define LOG_LEVEL_DEBUG   0x00
#define LOG_LEVEL_INFO    0x01
#define LOG_LEVEL_WARNING 0x02
#define LOG_LEVEL_ERROR   0x03
#define LOG_LEVEL_FATAL   0x04
#define LOG_LEVEL_MASK    0x07
#define LOG_LEVEL_GET(t)  (t & LOG_LEVEL_MASK)

/* Log states */
#define LOG_STATE_ON  0x80
#define LOG_STATE_OFF 0x00

#define LOG_ENABLED(type)                                                      \
   ((LOG_LEVEL_GET (type) >= LOG_LEVEL) && (type & LOG_STATE_ON))

/** Log a message if it is enabled */
#define LOG(type, ...)                                                         \
   do                                                                          \
   {                                                                           \
      if (LOG_ENABLED (type))                                                  \
      {                                                                        \
         os_log (type, __VA_ARGS__);                                           \
      }                                                                        \
   } while (0)

/** Log debug messages */
#define LOG_DEBUG(type, ...) LOG ((LOG_LEVEL_DEBUG | type), __VA_ARGS__)

/** Log informational messages */
#define LOG_INFO(type, ...) LOG ((LOG_LEVEL_INFO | type), __VA_ARGS__)

/** Log warning messages */
#define LOG_WARNING(type, ...) LOG ((LOG_LEVEL_WARNING | type), __VA_ARGS__)

/** Log error messages */
#define LOG_ERROR(type, ...) LOG ((LOG_LEVEL_ERROR | type), __VA_ARGS__)

/** Log fatal messages */
#define LOG_FATAL(type, ...) LOG ((LOG_LEVEL_FATAL | type), __VA_ARGS__)

#define LOG_DEBUG_ENABLED(type)   LOG_ENABLED (LOG_LEVEL_DEBUG | type)
#define LOG_INFO_ENABLED(type)    LOG_ENABLED (LOG_LEVEL_INFO | type)
#define LOG_WARNING_ENABLED(type) LOG_ENABLED (LOG_LEVEL_WARNING | type)
#define LOG_ERROR_ENABLED(type)   LOG_ENABLED (LOG_LEVEL_ERROR | type)
#define LOG_FATAL_ENABLED(type)   LOG_ENABLED (LOG_LEVEL_FATAL | type)

void os_log (uint8_t type, const char * fmt, ...) CC_FORMAT (2, 3);


#ifdef __cplusplus
}
#endif

#define PNET_LOG LOG_STATE_ON
#define PF_DCP_LOG LOG_STATE_ON
#define PF_ETH_LOG LOG_STATE_ON
#define PF_LLDP_LOG LOG_STATE_ON
#define PF_PNAL_LOG LOG_STATE_ON
#define PF_RPC_LOG LOG_STATE_ON

#define LOG_LEVEL LOG_LEVEL_DEBUG

#include "pnal_config.h"

#endif