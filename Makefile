##
# Raycasting test.
#
# @file
# @version 0.1
#

NAME = raycaster
CC = g++
LIB = -g -lraylib
FILES = \
		RayCamera.cpp \
		Map.cpp \
		RayCaster.cpp \
		raycastTest.cpp

all: $(NAME)

$(NAME):
	$(CC) $(LIB) $(FILES) -o $(NAME)

clean:
	rm $(NAME)

re: clean all

test: all
	./$(NAME)

# end
