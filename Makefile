# Compiler

$(CC) = g++

# Object files

$(OBJ) = programs/game.o modules/Classes.o

# Executable file

$(EXEC) = di_rpg

$(EXEC): $(OBJ)
  $(CC) -o $(EXEC) $(OBJ)
  
run: $(EXEC)
  ./$(EXEC)
  
valgrind: $(EXEC)
  valgrind ./$(EXEC)
  
clean:
  rm -f $(OBJ)
