#GCC     = gcc -O3 -ansi
GCC     = gcc -g -Wall

angcor :	   	angcor-main.o  Clebsch_Gordan.o angcor-BF.o
			${GCC} angcor-main.o Clebsch_Gordan.o angcor-BF.o -lm -o ../bin/angcor

angcor-main.o :		angcor-main.c shell.h 
		       	${GCC} -c angcor-main.c

Clebsch_Gordan.o :	Clebsch_Gordan.c shell.h 
	        	${GCC} -c Clebsch_Gordan.c

angcor-BF.o :		angcor-BF.c shell.h 
	        	${GCC} -c angcor-BF.c
