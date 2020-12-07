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

#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <linux/sched.h>

#include "my_parser.h"

void my_parser(){

	/* 
	Funcion que se encarga de procesar el archivo de configuracion
	e implementar los structs destinados a manejar los datos de configuracion
	que se van a utilizar en el sistema
	Entradas: Ninguna
	Requerimientos: Archivo de configuracion abierto correctamente
	Salidas: Structs con configuraciones asignadas
	*/

	// Ruta del archivo (estatica)
	FILE *ptofile = fopen("/home/natanfdecastro/Documents/tecnologico-de-costa-rica/ingenieria-computacion-411/ic-411-ii-semestre-2020/ic-6600-principios-de-sistemas-operativos/mypthreads-schedulers-p1-ic-6600/src/main/resources/config.txt", "r");
	
	if(ptofile == NULL) 
		printf("ERROR AL ABRIR ARCHIVO\n");

	int line = 0;

	char input[64];

	// Se inicia el struct de manejo de datos de configuracion
	configuration = (config *) malloc(sizeof(config));

	//configuration->tiempo_de_inicio = atoi(fgets(input, 64, ptofile));
	//configuration->tiempo_de_fin = atoi(fgets(input, 64, ptofile));

	// Se obtiene el protocolo a utilizar
	configuration->protocolo = (char *) malloc(sizeof(char));
	strcpy(configuration->protocolo, strtok(fgets(input, 64, ptofile), "\n"));

	// Se obtiene el numero de monitores a utilizar
	configuration->numero_monitores = atoi(fgets(input, 64, ptofile));

	// Se inicializan las configuraciones que lleva el struct de monitor
	configuration->monitors_list = (monitor_queue *) malloc(sizeof(monitor_queue));
	configuration->monitors_list->size = 0;
	configuration->monitors_list->head = NULL;
	configuration->monitors_list->tail = NULL;

	// Se itera por cada monitor que hay definido en el archivo de configuraciones
	for(int i=configuration->numero_monitores; i>0; i--){


		monitor_info *tmp_monitor = (monitor_info *) malloc(sizeof(monitor_info));

		// Se obtiene el id del monitor a utilizar
		tmp_monitor->id = atoi(strtok(fgets(input, 64, ptofile), "-"));

		// Ancho de monitor a utilizar
		tmp_monitor->width_canvas_size = atoi(strtok(NULL, "-"));

		// Largo del monitor a utilizar
		tmp_monitor->height_canvas_size = atoi(strtok(NULL, "\n"));

		// Variable de tipo window inicializada en NULL
		tmp_monitor->canvas_window = NULL;

		// Inicializa la lista enlazada para monitores
		if(configuration->monitors_list->head == NULL){
			tmp_monitor->prev = NULL;
			tmp_monitor->next = NULL;

			configuration->monitors_list->head = tmp_monitor;
			configuration->monitors_list->tail = tmp_monitor;
		}else{

			tmp_monitor->prev = configuration->monitors_list->tail;
			configuration->monitors_list->tail->next = tmp_monitor;
			configuration->monitors_list->tail = tmp_monitor;
		}
		configuration->monitors_list->size += 1;
	}

	if(strcmp(strtok(fgets(input, 64, ptofile), "\n"), "inicio") == 0){

	int index = 0;

	// Itera para obtener la informacion de cada figura
	while(1){

		fgets(input, 64, ptofile);
		if(strcmp(strtok(input, "\n"), "fin") == 0){
			break;
		}else if(strcmp(strtok(input, "\n"), "-") == 0){
			continue;
		}
		else{

			item_info *tmp_item = (item_info *) malloc(sizeof(item_info));
			tmp_item->monitor_id = atoi(strtok(input, "\n"));

			// Se obtiene el algoritmo de scheduling a utilizar
			tmp_item->scheduler = atoi(strtok(fgets(input, 64, ptofile), "\n"));
			
			// Se obtiene el inicio del tiempo de ejecucion
			tmp_item->tiempo_de_inicio = atoi(fgets(input, 64, ptofile)) + time(0);

			// Se obtiene el final del tiempo de ejecucion
			tmp_item->tiempo_de_fin = atoi(strtok(NULL, "-")) + time(0);
			for(int i = 0; i<5; i++){
				tmp_item->ascii_item[i] = (char *) malloc(sizeof(char)+1);
			}

			// Se obtienen los caracteres ASCII de cada figura
			strcpy(tmp_item->ascii_item[0], strtok(fgets(input, 64, ptofile), "\n"));
			strcpy(tmp_item->ascii_item[1], strtok(fgets(input, 64, ptofile), "\n"));
			strcpy(tmp_item->ascii_item[2], strtok(fgets(input, 64, ptofile), "\n"));
			strcpy(tmp_item->ascii_item[3], strtok(fgets(input, 64, ptofile), "\n"));
			strcpy(tmp_item->ascii_item[4], strtok(fgets(input, 64, ptofile), "\n"));

			// Se obtiene la posicion inicial en x de la figura
			tmp_item->posicion_inicial_x = atoi(strtok(fgets(input, 64, ptofile), "-"));

			// Se obtiene la posicion inicial en y de la figura
			tmp_item->posicion_inicial_y = atoi(strtok(NULL, "\n"));

			// Se obtiene la posicion final en x de la figura
			tmp_item->posicion_final_x = atoi(strtok(fgets(input, 64, ptofile), "-"));

			// Se obtiene la posicion final en y de la figura
			tmp_item->posicion_final_y = atoi(strtok(NULL, "\n"));

			// Se obtiene el angulo de rotacion de la figura
			tmp_item->angulo = atoi(fgets(input, 64, ptofile));
			configuration->item_list[index] = (item_info *) malloc(sizeof(item_info));
			configuration->item_list[index] = tmp_item;
			index ++;
		}
	}
}
	
	// Se obtiene el espacio entre figuras
	configuration->espacio_entre_objetos = atoi(fgets(input, 64, ptofile));

	printf("PROCESAMIENTO EXITOSO\n");

	fclose(ptofile);


}
