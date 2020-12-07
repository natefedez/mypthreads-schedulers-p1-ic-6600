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


void my_mutex_init(int *lock){

    /*
    Funcion que se encarga de inicializar el lock
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Valor del lock modificado
    */

    lock = 0;
}

int atomic_xchg(int *lock){

    /*
    Funcion que se encarga de realizar guardar un nuevo valor en la variable deseada
    y lo retorna atomicamente seguro
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Valor del lock invertido 
    https://stackoverflow.com/questions/28968552/spin-lock-using-xchg
    */

    unsigned int  tmp = 1;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
    return tmp;
}

int test_and_set(int *lock){

    /*
    Funcion que se encarga de llamar a la funcion de atomic_exchange
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Llamada a funcion atomic_exchange
    */

    return atomic_xchg(lock);
}


void my_mutex_destroy(int *lock) {

    /*
    Funcion que se encarga de destruir el mutex
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Memoria ocupada por el lock liberada
    */

    free(lock);
}

void my_mutex_lock(int *lock) {

    /*
    Funcion que se encarga de que solo el thread que llama a esta funcion
    pueda usar las variables hasta que se desbloquee
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Valor del lock cambiado
    */

    while (*lock){
        sleep(1);
    }
    test_and_set(lock);
}

void my_mutex_unlock(int *lock) {

    /*
    Funcion que se encarga de que el thread que habia llamado a la funcion de
    lock ya no tenga acceso exclusivo a las variables
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Valor del lock atomicamente invertido
    https://stackoverflow.com/questions/28968552/spin-lock-using-xchg
    */

    unsigned int  tmp = 0;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
}

void my_mutex_trylock(int *lock) {

    /*
    Funcion que se encarga de olo el thread que llama a esta funcion
    pueda usar las variables hasta que se desbloquee pero de manera menos 
    prolongada
    Entradas: Puntero al lock que se va a utilizar
    Restricciones: Ninguna
    Salidas: Valor del lock cambiado
    */

    while (*lock){
        usleep(1000);
    }
    test_and_set(lock);
}
