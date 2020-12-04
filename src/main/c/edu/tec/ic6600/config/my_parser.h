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

#define ITEMS_COUNT 10 


/* The monitor information for the animation */
typedef struct monitor_info {

  int id;  //monitor id
  int width_canvas_size; //monitor width_canvas_size
  int height_canvas_size; //monitor height_canvas_size
  struct monitor_info *prev, *next; 

}monitor_info;

/* The monitor information for the animation */
typedef struct monitor_queue {

  monitor_info *head;  //queue head node
  monitor_info *tail;  //queue tail node
  int size;  //queue size

}monitor_queue;

/* The monitor information for the animation */
typedef struct item_info {

  int scheduler;  //monitor id
  char *ascii_item[ITEMS_COUNT]; //list of items
  int posicion_actual_x;
  int posicion_actual_y;
  int posicion_inicial_x;
  int posicion_inicial_y;
  int posicion_final_x;
  int posicion_final_y;
  int angulo;

}item_info;

typedef struct config {

  int tiempo_de_inicio;
  int tiempo_de_fin;
  char *protocolo;
  int numero_monitores;
  monitor_queue *monitors_list;
  item_info *item_list[ITEMS_COUNT];
  int espacio_entre_objetos;
  
}config;

extern config *configuration;