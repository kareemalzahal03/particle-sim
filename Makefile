EXEC_NAME := prog
COMPILER := g++
ARCH := /usr/bin/arch -x86_64

SRC = src/*
INCLUDE = -I include/

SFML_INCLUDE := -I /usr/local/Cellar/sfml/2.6.1/include
SFML_LIBPATH := -L /usr/local/Cellar/sfml/2.6.1/lib
SFML_LIBLINK := -l sfml-graphics -l sfml-window -l sfml-system

${EXEC_NAME}: 
	${ARCH} ${COMPILER} ${SRC} ${INCLUDE} ${SFML_INCLUDE} ${SFML_LIBPATH} ${SFML_LIBLINK}