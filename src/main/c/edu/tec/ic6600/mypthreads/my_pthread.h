/*======================================================================
Copyright (C) 2020 Natan & Kenny

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Instituto Tecnologico de Costa Rica
    Principios de Sistemas Operativos - IC-6600

    Remember Remember (mypthreads-schedulers-p1-ic-6600)
    Disponible en: https://github.com/natanfdecastro/mypthreads-schedulers-p1-ic-6600

    Natan Fernandez de Castro - 2017105774
    Kenneth Rodriguez Murillo - 2018132752
========================================================================*/

#define my_pthread_h

#include <stdio.h>
#include <stdlib.h>

#include <ucontext.h>
#include <sys/types.h> //https://www.unix.com/man-page/linux/3head/types.h/
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#define STACK_SIZE 10000
#define NUM_THREADS 1000
#define INTERVAL 1000



// Funciones a extender

void my_thread_create(void (*dont_kill_the_funk) (), void *args, int tickets, int priority);

void my_thread_end();

void my_thread_yield();

void my_thread_join();

void my_thread_detach();

void run_threads(); //Corre los hilos

void *signal_stack; //Signal stack

static void set_exit_context();

void set_thread_context();


// Variables a utilizar

sigset_t set;

// variables de contexto
ucontext_t threads[NUM_THREADS];
ucontext_t *current_thread;
ucontext_t exit_context;

int priority[NUM_THREADS];
int priority_aux[NUM_THREADS];
int tickets[NUM_THREADS];
int boolean_dead_threads[NUM_THREADS];
int current_context;
int init;
int active_threads;
int active_threads_aux;
int total_tickets;
