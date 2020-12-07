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

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "my_pthread.h"
#include "my_sched.h"

// Documentar

int alternate;

void my_thread_chsched(int new_sched){

    if(new_sched == 0) active_sched = 0;

    if(new_sched == 1) active_sched = 1;

    if(new_sched == 2) active_sched = 2;
}

void my_sched_round_robin(){

    if(active_threads_aux > 0){

        current_context = (current_context + 1);

        if(boolean_dead_threads[current_context% active_threads]){

            while(boolean_dead_threads[current_context% active_threads]){
                current_context+=1;
            }
        }

        current_context = current_context % active_threads;
        current_thread = &threads[current_context];

        setcontext(current_thread);//activa el nuevo hilo
    }
}


void my_sched_sort(){

    srand(time(NULL));

    int aux;

    if(active_threads_aux > 0){

        int winner = rand()%(total_tickets+1);//saca el ganador del sorteo
        aux = winner;
        int i;

        for (i = 0; i < active_threads; i++) {//revisa quien es el ganador

            aux -= tickets[i];

            if(aux<=0){
                if(boolean_dead_threads[i% active_threads]){
                    while(boolean_dead_threads[i% active_threads]){
                        i+=1;
                    }
                }

                current_context = i;
                current_thread = &threads[current_context];
                break;
            }

            else{

                tickets[i]++;
                total_tickets++;
            }
        }
        setcontext(current_thread);//activa el nuevo hilo
    }


}

void my_sched_real_time(){

    int aux = -1;
    int last = current_context;
    int i;

    if(active_threads_aux > 0){

        for (i = 0; i < active_threads; i++) {//busca hilo de mayor prioridad que no haya terminado

            if(aux < priority[i] && !boolean_dead_threads[i] && !priority_aux[i]){

                current_context = i;
                aux = priority[i];
            }
        }

        if(aux == -1){

            for (i = 0; i < active_threads; i++) {

                priority_aux[i] = 0;
            }

            my_sched_real_time();

        }
        else{

            priority_aux[current_context] = 1;//pone el hilo como ya ejecutado para que no se encicle
            current_thread = &threads[current_context];//activa el nuevo hilo

            setcontext(current_thread);
        }
    }


}


void timer_interrupt(){

    alternate = 0;

    getcontext(&signal_context);

    signal_context.uc_stack.ss_sp = signal_stack;
    signal_context.uc_stack.ss_size = STACK_SIZE;
    signal_context.uc_stack.ss_flags = 0;

    sigemptyset(&signal_context.uc_sigmask);

    alternate = alternate^active_sched;

    my_thread_chsched(alternate);

    if(active_sched == 0) active_sched++;

    if(active_sched == 1) active_sched--;

    if(active_sched == 0){makecontext(&signal_context, my_sched_round_robin, 1);}

    if(active_sched == 1){makecontext(&signal_context, my_sched_sort, 1);}

    if(active_sched == 2){makecontext(&signal_context, my_sched_real_time, 1);}

    swapcontext(current_thread,&signal_context);

}
