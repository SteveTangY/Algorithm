objects = test_main.o  avl_tree.o
CC = g++
CC_options =

avl_tree : $(objects)
	$(CC) $(objects) -o avl_tree $(CC_options)

test_main.o : test_main.cpp
	$(CC) -c test_main.cpp $(CC_options)

avl_tree.o : avl_tree.h avl_tree.cpp
	$(CC) -c avl_tree.cpp $(CC_options)

.PHONY : clean
	rm $(objects)