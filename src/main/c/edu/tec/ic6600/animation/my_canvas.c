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
int i, j;

void create_canvas(){


  // Inicializacion de ncurses (necesario)
  int x = 0, y = 0;
  
  initscr();
  
  noecho();
  
  curs_set(FALSE);

  // Puntero temporal que nos ayudara a recorrer la lista de monitores
  monitor_info *temp_monitor = (monitor_info *) malloc(sizeof(monitor_info));
  temp_monitor = configuration -> monitors_list -> head;

  // Se recorre la lista de monitores en config
	while(temp_monitor != NULL){

      // Se crea un nuevo window por cada monitor y se guarda en la estructura
      temp_monitor -> canvas_window = newwin(temp_monitor -> height_canvas_size,temp_monitor -> width_canvas_size, y, x);
      
      // Se posicionan en la terminal segun el ancho de cada uno
      x += temp_monitor -> width_canvas_size;
      
      //y+=temp_monitor -> height_canvas_size;
      
      // Funcion de ncurses para pintar los bordes del window
      box(temp_monitor -> canvas_window, 0, 0);
      
      // Es necesario para mostrar los cambios hechos en window
      wrefresh(temp_monitor-> canvas_window);
		  
      // Se mueve al siguiente
      temp_monitor = temp_monitor -> next;
	}


  //printf("se ha creado el canvas con %d filas y %d columnas\n",height_canvas_size, width_canvas_size);
}

/*
void clear_windows(){
  monitor_info *temp_monitor = (monitor_info *) malloc(sizeof(monitor_info));
  temp_monitor = configuration -> monitors_list -> head;

	while(temp_monitor != NULL){
		wclear(temp_monitor -> canvas_window);
		temp_monitor = temp_monitor -> next;
	}
}*/
