#include "def.h"
int usage(void)
{
	printf("USAGE: \n");
printf("Программа для манипуляции геометрическими объектами\n");
printf("на плоскости. \n\n       Допустимые команды и операции:\n");
printf( "ex_it, h_elp, def_ine, re_ad,  conv_ex,  area, simple\n");
printf( "выход  помощь описание чтение  проверка_условия выпукл_обол  площадь объем    центроид   добавл исключение\n");
printf("\n     Виды объектов:\n");
printf( "poi_nt, lin_e , segm_ent, circ_le,    polyg_one\n");
printf( "точка   прямая  отрезок   окружность  многоугольник \n");
printf( "\n\n Для получения справки об объектах и командах\n");
printf( "      Используйте команду \"help объект ;\" или \"help команда ;\"\n");
return 0;
}
