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


#ifndef my_sched
#define my_sched

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ucontext.h>

int active_sched;

ucontext_t signal_context;

void my_thread_chsched(int new_sched);

void run_threads();

void my_sched_round_robin();

void sched_sort(); //Scheduler de Sorteo

void my_sched_real_time(); //Scheduler de Tiempo real

void timer_interrupt(); //Crea el context segun el tipo de scheduler

#endif
