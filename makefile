OBJS = scanner.o node.o bst.o avl.o queue.o trees.o
OPTS = -Wall -g -std=c99

trees : $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees -lm

trees.o : trees.c avl.h bst.h queue.h scanner.h node.h
	gcc $(OPTS) -c trees.c

scanner.o : scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

node.o : node.c node.h
	gcc $(OPTS) -c node.c

bst.o : bst.c node.h
	gcc $(OPTS) -c bst.c

avl.o : avl.c node.h
	gcc $(OPTS) -c avl.c

queue.o : queue.c node.h
	gcc $(OPTS) -c queue.c

clean :
	rm -f $(OBJS) trees

test :
	@echo TESTING BST TREE
	@echo trees -b s.txt command.txt
	@echo ###############################
	trees -b s.txt command.txt
	@echo ###############################
	@echo TESTING AVL TREE
	@echo trees -a s.txt command.txt
	@echo ###############################
	trees -a s.txt command.txt
	@echo ###############################
