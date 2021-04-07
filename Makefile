# Compiler

CC = g++

# Include path

INCLUDE = include

# Object files

OBJ = programs/game.o modules/Classes.o 

# Compilation flags

CFLAGS = -g -I$(INCLUDE) 

# Executable file

EXEC = di_rpg

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(EXEC) 
  
run: $(EXEC)
  ./$(EXEC)
  
valgrind: $(EXEC)
  valgrind ./$(EXEC)
  
clean:
  rm -f $(OBJ) $(EXEC)
  clear
