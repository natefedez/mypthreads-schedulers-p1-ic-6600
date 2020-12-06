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
#include <curses.h>
#include "../config/my_parser.h"

config* configuration;

void *move_figure(void *arg){

   item_info *figure = (item_info *) arg;

   monitor_info *temp_monitor = (monitor_info *) malloc(sizeof(monitor_info));
   temp_monitor = configuration -> monitors_list -> head;

   while(temp_monitor -> id != figure -> monitor_id){
     temp_monitor = temp_monitor -> next;
   }

  while(figure -> posicion_actual_x != figure -> posicion_final_x && figure -> posicion_actual_y != figure -> posicion_final_y) {
    clear(); // Clear the screen of all
    // previously-printed characters

        wmove(temp_monitor -> canvas_window, figure -> posicion_actual_y-2,figure -> posicion_actual_x);
        waddstr(temp_monitor -> canvas_window, figure ->ascii_item[0]);
        wmove(temp_monitor -> canvas_window, figure -> posicion_actual_y-1, figure -> posicion_actual_x);
        waddstr(temp_monitor -> canvas_window, figure ->ascii_item[1]);
        wmove(temp_monitor -> canvas_window, figure -> posicion_actual_y, figure -> posicion_actual_x);
        waddstr(temp_monitor -> canvas_window, figure ->ascii_item[2]);
        wmove(temp_monitor -> canvas_window, figure -> posicion_actual_y+1, figure -> posicion_actual_x);
        waddstr(temp_monitor -> canvas_window, figure ->ascii_item[3]);
        wmove(temp_monitor -> canvas_window, figure -> posicion_actual_y+2, figure -> posicion_actual_x);
        waddstr(temp_monitor -> canvas_window, figure ->ascii_item[4]);

        if(figure ->posicion_actual_y < figure->posicion_final_y)
          figure ->posicion_actual_y++;
        if(figure ->posicion_actual_x < figure ->posicion_final_x)
          figure ->posicion_actual_x++;

        if(figure ->posicion_actual_y > figure ->posicion_final_y)
          figure ->posicion_actual_y--;
        if(figure ->posicion_actual_x > figure ->posicion_final_x)
          figure ->posicion_actual_x--;


    wrefresh(temp_monitor-> canvas_window);

    usleep(900000); // Shorter delay between movements
  }
}

/*
my_animation(){

    int x_axis_size = 0, int y_axis_size = 0;
    int initial_time = 0; int ending_time = 0;

    printf(">>> Digite ancho y largo del canvas: ");
    scanf("%d %d", x_axis_size, y_axis_size);

    printf(">>> Digite tiempo inicial y final: ");
    scanf("%d %d", initial_time, ending_time);

}
*/
