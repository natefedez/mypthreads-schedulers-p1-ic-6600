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

#include "my_pthread.h"
#include "my_sched.h"

void my_thread_end(){

		boolean_dead_threads[current_context] = 1;
    total_tickets-=tickets[current_context];
    active_threads_aux--;

    sched_alternator();

}


void my_thread_yield(){

		sched_alternator();
}

void run_threads(){

    current_thread = &threads[0];

    setcontext(&threads[0]);

}

static void execute_exit_context(){

    boolean_dead_threads[current_context] = 1;
    total_tickets -= tickets[current_context];
    active_threads_aux--;

    sched_alternator();

    while(1);
}

static void set_exit_context() {

	static int exit_context_created;
    if(!exit_context_created){

        getcontext(&exit_context);

        exit_context.uc_link = 0;
        exit_context.uc_stack.ss_sp = malloc(STACK_SIZE);
        exit_context.uc_stack.ss_size = STACK_SIZE;
        exit_context.uc_stack.ss_flags= 0;

        makecontext(&exit_context, (void (*) (void))&execute_exit_context, 0);

        exit_context_created = 1;
    }
}

void set_thread_context(){

		int i;

	// Inicializa en 0 los dead_threads
    for(i = 0; i < NUM_THREADS; i++) boolean_dead_threads[i] = 0;

    set_exit_context();

    struct itimerval it;

    signal_stack = malloc(STACK_SIZE);

    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = INTERVAL * 1000;
    it.it_value = it.it_interval;

    setitimer(ITIMER_REAL, &it, NULL);

    struct sigaction act;
    act.sa_sigaction = sched_alternator;

    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;

    sigemptyset(&set);

    sigaddset(&set, SIGALRM);

    sigaction(SIGALRM, &act, NULL);

}

void my_thread_join(ucontext_t *active_thread,ucontext_t *waiting_thread){

		active_thread -> uc_link = waiting_thread;
		//setcontext(active_thread);

}


void my_thread_detach(ucontext_t *thread_to_detach){

		setcontext(thread_to_detach);
		free(thread_to_detach);

}

void my_thread_create(void (*dont_kill_the_funk) (), void *args, int tickets_s, int priority_s){

	/*
	Recibe:
	- Funcion a ejecutar en el thread
	- Argumentos de la funcion
	- Tickets (Scheduler Sorteo)
	- Prioridad (Scheduler de Tiempo Real)

	https://stackoverflow.com/questions/13283294/how-to-make-thread-in-c-without-using-posix-library-pthread-h
	*/

	// Es posible no usar el if?
	// https://www.unix.com/man-page/linux/7posix/ucontext.h/
		if (!init) {
			set_thread_context();
			init++;
		}

		// https://www.unix.com/man-page/linux/2/sigaltstack/

		void *stack; // para utilizar context

		// Crea objeto tipo context
		ucontext_t *thread = &threads[active_threads];
    getcontext(thread);

    // Asigna memoria a context
    stack = malloc(STACK_SIZE);

    // Asigna valores por defecto
    thread -> uc_stack.ss_sp = stack;
    thread -> uc_stack.ss_size = STACK_SIZE;
    thread -> uc_stack.ss_flags = 0;
    thread -> uc_link = &exit_context;

    // Inicializa y vacia un signal set
    sigemptyset(&thread -> uc_sigmask);

    // Se manda la funcion al context
    makecontext(thread,(void (*)(void))dont_kill_the_funk, 1, args);
    tickets[active_threads] = tickets_s;
    priority[active_threads] = priority_s;
    total_tickets += tickets_s;
    active_threads++;
    active_threads_aux++;

}
