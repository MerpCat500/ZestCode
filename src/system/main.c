/**
 * \file system/main.c
 *
 * Contains the main startup code for PROS 3.0. main is called from vexStartup
 * code. Our main() initializes data structures and starts the FreeRTOS
 * scheduler.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>

#include "ifi/v5_api.h"
#include "kapi.h"

extern void rtos_initialize();
extern void vfs_initialize();
extern void system_daemon_initialize();
// extern void graphical_context_daemon_initialize(void);
extern void display_initialize(void);
extern void rtos_sched_start();
extern void registry_init();

// XXX: pros_init happens inside __libc_init_array, and before any global
// C++ constructors are invoked. This is accomplished by instructing
// GCC to include this function in the __init_array. The 101 argument
// gives the compiler instructions on the priority of the constructor,
// from 0-~65k. The first 0-100 priorities are reserved for language
// implementation.
__attribute__((constructor(101))) static void pros_init(void) {
	rtos_initialize();

	vfs_initialize();

	registry_init();

	system_daemon_initialize();

	display_initialize();
}

int main() {
	rtos_sched_start();

	vexDisplayPrintf(10, 60, 1, "failed to start scheduler\n");

	printf("Failed to start Scheduler\n");
	for (;;)
		;
}
