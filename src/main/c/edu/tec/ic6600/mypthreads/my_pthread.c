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

void my_thread_end {

	dead_threads[current_context] = 1;
    total_tickets-=tickets[current_context];
    active_threads_aux--;
    
    //timer_interrupt();

}


void my_thread_yield {

	//timer_interrupt();
}

void run_threads(){

    current_thread = &threads[0];
    
    setcontext(&threads[0]);

}

static void execute_exit_context(){
    
    boolean_dead_threads[current_context] = 1;
    total_tickets -= tickets[current_context];
    active_threads_aux--;
    
    timer_interrupt();
    
    while(1);
}

static void set_exit_context() {

	static int exit_context_created;

    if(!exit_context_created){

        getcontext(&exitContext);

        exitContext.uc_link = 0;
        exitContext.uc_stack.ss_sp = malloc(STACK_SIZE);
        exitContext.uc_stack.ss_size = STACK_SIZE;
        exitContext.uc_stack.ss_flags= 0;
        
        makecontext(&exitContext, (void (*) (void))&execute_exit_context, 0);
        
        exit_context_created = 1;
    }

}

void set_thread_context {

	int i;

	// Inicializa en 0 los dead_threads
    for(i = 0; i < NUM_THREADS; i++)
        dead_threads[i] = 0;
    
    set_exit_context();
    
    struct itimerval it;
    
    signal_stack = malloc(STACK_SIZE);
    
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = INTERVAL * 1000;
    it.it_value = it.it_interval;
    
    setitimer(ITIMER_REAL, &it, NULL);
    
    struct sigaction act;
    act.sa_sigaction = timer_interrupt;
    
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    
    sigemptyset(&set);
    
    sigaddset(&set, SIGALRM);
    
    sigaction(SIGALRM, &act, NULL);

}

// TODO
void my_thread_join {

	return 0;
}

// TODO
void my_thread_detach {


	return 0;
}

void my_thread_create(void *dont_kill_the_funk, void *args, int tickets, int priority){

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
	ucontext_threadontext_t *ucontext_threadontext_thread = &threads[active_threads];
    getcontext(ucontext_thread);tickets_sched

    // Asigna memoria a context
    stack = malloc(STACK_SIZE);

    // Asigna valores por defecto
    ucontext_thread -> ucontext_thread_stack.ss_sp = stack;
    ucontext_thread -> ucontext_thread_stack.ss_size = STACK_SIZE;
    ucontext_thread -> ucontext_thread_stack.ss_flags = 0;
    ucontext_thread -> ucontext_thread_link = &exitContext;

    // Inicializa y vacia un signal set
    sigemptyset(&ucontext_thread -> ucontext_thread_sigmask);
    
    // Se manda la funcion al context 
    makecontext(ucontext_thread, function, 1, args);

    tickets[active_threads] = tickets_sched;
    priority[active_threads] = priority_sched;
    total_tickets += tickets_sched;
    active_threads++;
    active_threads_aux++;

}