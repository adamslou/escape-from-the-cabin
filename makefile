# Program name: makefile
# Author: Louis Adams
# Date: 2019-06-04
# Description: This is the makefile for the Final Project.
# Adapted from: Week 1 Module, Lecture: Makefiles

CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
LDFLAGS = -lboost_date_time

EXECUTABLES = main

OBJECTS = ${SOURCES:.cpp=.o} 

SOURCES = main.cpp Game.cpp Space.cpp Loft.cpp Kitchen.cpp LivingRoom.cpp BoatShed.cpp Shore.cpp ToolShed.cpp Campfire.cpp Dock.cpp getInteger.cpp menu.cpp 

HEADERS = Game.hpp Space.hpp Loft.hpp Kitchen.hpp LivingRoom.hpp BoatShed.hpp Shore.hpp ToolShed.hpp Campfire.hpp Dock.hpp getInteger.hpp menu.hpp Item.hpp Name.hpp

${EXECUTABLES}: ${OBJECTS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJECTS} -o ${EXECUTABLES}

${OBJECTS}: ${SOURCES}
	${CXX} ${CXXFLAGS} -c ${SOURCES}

clean:
	rm *.o ${EXECUTABLES}

zip:
	zip -D Final_Project_Adams_Louis.zip *.cpp *.hpp *.pdf makefile

val:
	valgrind ${EXECUTABLES} --leak-check=full./${EXECUTABLES}
