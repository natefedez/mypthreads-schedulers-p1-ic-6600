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
#include "my_mutex.h"


void my_mutex_init(my_mutex *lock){

    lock = 0;
}

int atomic_xchg(my_mutex *lock){

    // https://stackoverflow.com/questions/28968552/spin-lock-using-xchg

    unsigned int  tmp = 1;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
    return tmp; 
}

int test_and_set(my_mutex *lock){

    return atomic_xchg(lock);
}


void my_mutex_destroy(my_mutex *lock) {

    //free(lock);
}

void my_mutex_lock(my_mutex *lock) {

    while (*lock){
        sleep(1);
    }
    test_and_set(lock);
}

void my_mutex_unlock(my_mutex *lock) {

    // https://stackoverflow.com/questions/28968552/spin-lock-using-xchg

    unsigned int  tmp = 0;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
}

void my_mutex_trylock(my_mutex *lock) {

    while (*lock){
        usleep(1000);
    }
    test_and_set(lock);
}