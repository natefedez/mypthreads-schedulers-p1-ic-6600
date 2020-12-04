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

#include "my_pthreads.h"
#include "my_mutex.h"
#include "my_sched.h"

my_mutex field_lock;

my_animation(){

    int x_axis_size = 0, int y_axis_size = 0;
    int initial_time = 0; int ending_time = 0;

    printf(">>> Digite ancho y largo del canvas: ");
    scanf("%d %d", x_axis_size, y_axis_size);

    printf(">>> Digite tiempo inicial y final: ");
    scanf("%d %d", initial_time, ending_time);
    
}
