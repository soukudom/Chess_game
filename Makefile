#
# Chess game makefile
#

#object file
OBJ=src/CBishop.o src/CBoard.o src/CGame.o src/CKing.o src/CKnight.o src/CPawn.o src/CQueen.o src/CRook.o src/main.o

#g++ option parameters
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb

#Name of chess game
NAME = soukudom


all: 	${NAME} doc 

compile: ${OBJ} 
	g++ $^ -o ${NAME} ${CXXFLAGS}

clean:
	rm -r doc  ${NAME} src/*.o

run:  ${NAME} 
	./${NAME}
doc:
	 doxygen Doxyfile

${NAME}: ${OBJ}
	g++ $^ -o $@ ${CXXFLAGS}

%.o: %.cpp
	g++ $(CXXFLAGS) -c -o $@ $<	

CBishop.o: src/CBishop.cpp src/CBishop.h src/CPiece.h
CBoard.o: src/CBoard.cpp src/CBoard.h src/CPiece.h src/CRook.h \
 src/CBishop.h src/CKing.h src/CKnight.h src/CQueen.h src/CPawn.h
CGame.o: src/CGame.cpp src/CGame.h src/CBoard.h src/CPiece.h
CKing.o: src/CKing.cpp src/CKing.h src/CPiece.h
CKnight.o: src/CKnight.cpp src/CKnight.h src/CPiece.h
CPawn.o: src/CPawn.cpp src/CPawn.h src/CPiece.h
CQueen.o: src/CQueen.cpp src/CQueen.h src/CPiece.h
CRook.o: src/CRook.cpp src/CRook.h src/CPiece.h
main.o: src/main.cpp src/CPawn.h src/CPiece.h src/CKing.h src/CBishop.h \
 src/CRook.h src/CQueen.h src/CKnight.h src/CBoard.h src/CGame.h
