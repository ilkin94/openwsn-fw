/**
\brief Declaration of the "opentimers" driver.

\author Xavi Vilajosana <xvilajosana@eecs.berkeley.edu>, March 2012.
*/

#ifndef __OPENTIMERS_H
#define __OPENTIMERS_H

#include "openwsn.h"
#include "bsp_timer.h"

//=========================== define ==========================================

/// The number of timer that can run concurrently
#define MAX_NUM_TIMERS            10
#define MAX_TICKS_IN_SINGLE_CLOCK 65535

#define TOO_MANY_TIMERS_ERROR     255

#define opentimer_id_t uint8_t

typedef void (*opentimers_cbt)(void);

//=========================== typedef =========================================

typedef enum {
   TIMER_PERIODIC,
   TIMER_ONESHOT,
}timer_type_t;

/*the time can be in tics or in ms*/
typedef enum {
   TIME_MS,
   TIME_TICS,
}time_type_t;



typedef struct {
   uint32_t             period_ticks;       // total number of clock ticks
   PORT_TIMER_WIDTH     ticks_remaining;    // ticks remaining before elapses
   uint16_t             wraps_remaining;    // the clock register is 16 bit, and can't count beyond 32k...
                                            // so period_ticks = wraps_remaining*(32k or uint16_t)
   timer_type_t         type;               // periodic or one-shot
   bool                 isrunning;          // is running?
   opentimers_cbt       callback;           // function to call when elapses
   bool                 hasExpired;         // whether the callback has to be called
   PORT_TIMER_WIDTH     init_time;          // time when this timer was started (in tics of the counter)
} opentimers_t;

//=========================== prototypes ======================================

void           opentimers_init();
opentimer_id_t opentimers_start(uint32_t       duration,
                                timer_type_t   type,
                                time_type_t timetype,
                                opentimers_cbt callback);
void           opentimers_setPeriod(opentimer_id_t id,time_type_t timetype, uint32_t       newPeriod);
void           opentimers_stop(opentimer_id_t id);
void           opentimers_restart(opentimer_id_t id);

uint32_t       opentimers_get_currentValue(opentimer_id_t id,time_type_t typet);

#endif
