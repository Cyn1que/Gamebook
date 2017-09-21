CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb 
CORE=../
OBJ=../bin/obj/
GAME=../
MANAGERS=../
OBJECTS=$(OBJ)main.o $(OBJ)GameApp.o $(OBJ)GameInstance.o $(OBJ)GameMenu.o $(OBJ)World.o $(OBJ)Character.o $(OBJ)Location.o $(OBJ)Player.o $(OBJ)Object.o $(OBJ)Actor.o $(OBJ)Enemy.o $(OBJ)Item.o $(OBJ)Inventory.o $(OBJ)NonPlayerChar.o $(OBJ)Lootbag.o $(OBJ)InputManager.o $(OBJ)RenderManager.o $(OBJ)DataManager.o

BIN=./gamebook

all: $(BIN)
	make compile
	make doc

compile: $(BIN)

run: $(BIN)
	$(BIN)

clean:
	rm -rf bin doc $(BIN)

doc: Doxyfile src/*
	doxygen Doxyfile

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN) 

$(OBJ)main.o: src/main.cpp $(OBJ)GameApp.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(CORE)main.cpp -o $(OBJ)main.o

$(OBJ)GameApp.o: $(CORE)GameApp.cpp $(OBJ)GameMenu.o $(OBJ)GameInstance.o $(OBJ)RenderManager.o  $(OBJ)InputManager.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(CORE)GameApp.cpp -o $(OBJ)GameApp.o

$(OBJ)GameInstance.o: $(CORE)GameInstance.cpp $(OBJ)World.o $(OBJ)RenderManager.o $(OBJ)InputManager.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(CORE)GameInstance.cpp -o $(OBJ)GameInstance.o

$(OBJ)GameMenu.o: $(CORE)GameMenu.cpp $(OBJ)RenderManager.o  $(OBJ)InputManager.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(CORE)GameMenu.cpp -o $(OBJ)GameMenu.o

$(OBJ)World.o: $(GAME)World.cpp $(OBJ)Location.o $(OBJ)Player.o $(OBJ)DataManager.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)World.cpp -o $(OBJ)World.o

$(OBJ)Location.o: $(GAME)Location.cpp $(OBJ)Object.o $(OBJ)InputManager.o $(OBJ)RenderManager.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Location.cpp -o $(OBJ)Location.o

$(OBJ)Character.o: $(GAME)Character.cpp $(OBJ)Actor.o
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Character.cpp -o $(OBJ)Character.o

$(OBJ)Player.o: $(GAME)Player.cpp $(OBJ)Location.o $(OBJ)Object.o $(OBJ)Inventory.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Player.cpp -o $(OBJ)Player.o

$(OBJ)Object.o: $(GAME)Object.cpp
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Object.cpp -o $(OBJ)Object.o

$(OBJ)Actor.o: $(GAME)Actor.cpp $(OBJ)Object.o
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Actor.cpp -o $(OBJ)Actor.o

$(OBJ)Enemy.o: $(GAME)Enemy.cpp $(OBJ)NonPlayerChar.o $(OBJ)Player.o $(OBJ)InputManager.o $(OBJ)RenderManager.o 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Enemy.cpp -o $(OBJ)Enemy.o

$(OBJ)Item.o: $(GAME)Item.cpp 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Item.cpp -o $(OBJ)Item.o

$(OBJ)Inventory.o: $(GAME)Inventory.cpp $(OBJ)Item.o $(OBJ)InputManager.o $(OBJ)RenderManager.o
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Inventory.cpp -o $(OBJ)Inventory.o

$(OBJ)NonPlayerChar.o: $(GAME)NonPlayerChar.cpp $(OBJ)Lootbag.o $(OBJ)Character.o $(OBJ)Player.o $(OBJ)InputManager.o $(OBJ)RenderManager.o
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)NonPlayerChar.cpp -o $(OBJ)NonPlayerChar.o

$(OBJ)Lootbag.o: $(GAME)Lootbag.cpp $(OBJ)Object.o $(OBJ)Player.o $(OBJ)Item.o $(OBJ)InputManager.o $(OBJ)RenderManager.o
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(GAME)Lootbag.cpp -o $(OBJ)Lootbag.o

$(OBJ)InputManager.o: $(MANAGERS)InputManager.cpp 
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(MANAGERS)InputManager.cpp -o $(OBJ)InputManager.o

$(OBJ)RenderManager.o: $(MANAGERS)RenderManager.cpp
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(MANAGERS)RenderManager.cpp -o $(OBJ)RenderManager.o

$(OBJ)DataManager.o: $(MANAGERS)DataManager.cpp $(OBJ)Player.o $(OBJ)Location.o $(OBJ)Enemy.o $(OBJ)Item.o $(OBJ)Lootbag.o
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(MANAGERS)DataManager.cpp -o $(OBJ)DataManager.o



