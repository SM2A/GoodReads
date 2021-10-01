COMPILER=g++
COMPILE=-c
VERSION= -std=c++11
CC=${COMPILER} ${COMPILE} ${VERSION}

BUILD_DIR=Build
SOURCE_DIR=Source
CLASSES_DIR=Classes
INTERFACES_DIR=Interfaces

all: Goodreads.out

Goodreads.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/Authors.o ${BUILD_DIR}/Books.o ${BUILD_DIR}/Date.o ${BUILD_DIR}/GoodReads.o ${BUILD_DIR}/Reviews.o ${BUILD_DIR}/Users.o
	${COMPILER} ${VERSION} ${BUILD_DIR}/main.o ${BUILD_DIR}/Authors.o ${BUILD_DIR}/Books.o ${BUILD_DIR}/Date.o ${BUILD_DIR}/GoodReads.o ${BUILD_DIR}/Reviews.o ${BUILD_DIR}/Users.o -o Goodreads.out

${BUILD_DIR}/main.o: ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/GoodReads.hpp
	mkdir Build
	${CC} ${SOURCE_DIR}/main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/Authors.o: ${SOURCE_DIR}/${CLASSES_DIR}/Authors.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Authors.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Date.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Books.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Authors.cpp -o ${BUILD_DIR}/Authors.o

${BUILD_DIR}/Books.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Books.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Books.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Reviews.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Books.cpp -o ${BUILD_DIR}/Books.o

${BUILD_DIR}/Date.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Date.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Date.cpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Date.cpp -o ${BUILD_DIR}/Date.o

${BUILD_DIR}/GoodReads.o: ${SOURCE_DIR}/${CLASSES_DIR}/GoodReads.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/GoodReads.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Authors.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Reviews.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Books.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Users.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/GoodReads.cpp -o ${BUILD_DIR}/GoodReads.o

${BUILD_DIR}/Reviews.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Reviews.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Reviews.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Date.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Reviews.cpp -o ${BUILD_DIR}/Reviews.o

${BUILD_DIR}/Users.o: ${SOURCE_DIR}/${INTERFACES_DIR}/Users.hpp ${SOURCE_DIR}/${CLASSES_DIR}/Users.cpp ${SOURCE_DIR}/${INTERFACES_DIR}/Date.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Books.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Authors.hpp ${SOURCE_DIR}/${INTERFACES_DIR}/Reviews.hpp
	${CC} ${SOURCE_DIR}/${CLASSES_DIR}/Users.cpp -o ${BUILD_DIR}/Users.o

clean:
	rm Goodreads.out
	rm ${BUILD_DIR}/*.o
	rmdir Build