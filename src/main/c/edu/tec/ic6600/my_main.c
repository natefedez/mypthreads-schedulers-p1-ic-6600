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

#include "config/my_parser.h"
#include "animation/my_canvas.h"
#include "animation/animation.h"
#include "mypthreads/my_pthread.h"

#include <stdio.h>
#include <stdlib.h>

config* configuration;

int main() {

	my_parser();

	int i = 0;

	//create_canvas();

	//printf("%s\n", configuration->protocolo);
  //printf("%d\n", configuration->monitors_list->head->id);
	//printf("%d\n", configuration->monitors_list->head->width_canvas_size);

	/*
	monitor_info *temp_monitor = (monitor_info *) malloc(sizeof(monitor_info));
  temp_monitor = configuration -> monitors_list -> head;

	printf("error1");

	while(temp_monitor != NULL){
		*temp_monitor -> canvas_window = create_canvas(temp_monitor -> width_canvas_size, temp_monitor -> height_canvas_size);
		temp_monitor = temp_monitor -> next;
	}
	*/
	while(configuration->item_list[i] != NULL){
		printf("va crear un hilo\n");
		my_thread_create(initialize_canvas, NULL , 5, 5);
		i++;
	}
	//initialize_canvas();

	return 0;

}
