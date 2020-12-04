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

void initialize_canvas(){

  for(int i = 0; i < ITEMS_COUNT; i++){

    if(configuration->item_list[i] == NULL) break;

    printf("%d\n", configuration->item_list[i]->posicion_inicial_x);
    printf("%d\n", configuration->item_list[i]->posicion_inicial_y);
    printf("%d\n", configuration->item_list[i]->posicion_final_x);
    printf("%d\n", configuration->item_list[i]->posicion_final_y);
    printf("%d\n", configuration->item_list[i]->angulo);

    configuration->item_list[i]->posicion_actual_x = configuration->item_list[i]->posicion_inicial_x;
    configuration->item_list[i]->posicion_actual_y = configuration->item_list[i]->posicion_inicial_y;

  }


  int x = 0, y = 0;
  initscr();
  noecho();
  curs_set(FALSE);



  while(1) {
    clear(); // Clear the screen of all
    // previously-printed characters

  for(int i = 0; i < ITEMS_COUNT; i++){
    if(configuration->item_list[i] == NULL) break;

        mvprintw(configuration->item_list[i]->posicion_actual_y-2, configuration->item_list[i]->posicion_actual_x, configuration->item_list[i]->ascii_item[0]);
        mvprintw(configuration->item_list[i]->posicion_actual_y-1, configuration->item_list[i]->posicion_actual_x, configuration->item_list[i]->ascii_item[1]);
        mvprintw(configuration->item_list[i]->posicion_actual_y, configuration->item_list[i]->posicion_actual_x, configuration->item_list[i]->ascii_item[2]);
        mvprintw(configuration->item_list[i]->posicion_actual_y+1, configuration->item_list[i]->posicion_actual_x, configuration->item_list[i]->ascii_item[3]);
        mvprintw(configuration->item_list[i]->posicion_actual_y+2, configuration->item_list[i]->posicion_actual_x, configuration->item_list[i]->ascii_item[4]);

        if(configuration->item_list[i]->posicion_actual_y < configuration->item_list[i]->posicion_final_y)
          configuration->item_list[i]->posicion_actual_y++;
        if(configuration->item_list[i]->posicion_actual_x < configuration->item_list[i]->posicion_final_x)
          configuration->item_list[i]->posicion_actual_x++;

        if(configuration->item_list[i]->posicion_actual_y > configuration->item_list[i]->posicion_final_y)
          configuration->item_list[i]->posicion_actual_y--;
        if(configuration->item_list[i]->posicion_actual_x > configuration->item_list[i]->posicion_final_x)
          configuration->item_list[i]->posicion_actual_x--;

  }
  
    refresh();

    usleep(900000); // Shorter delay between movements
    x++; // Advance the ball to the right
    y++;
  }


}
