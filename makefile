CC=g++
WIN=x86_64-w64-mingw32-g++
CFLAGS=-Wall

TARGET=trade
P=Builds/

#Linux compilation
trade: Utils.o
	$(CC) --static -o $(P)$(TARGET) main.cpp Utils.o

Utils.o: Utils.h Utils.cpp
	$(CC) --static -c -o Utils.o Utils.cpp

#Windows compilation
win: win-Utils.o
	$(WIN) --static -o $(P)$(TARGET).exe main.cpp win-Utils.o

win-Utils.o: Utils.h Utils.cpp
	$(WIN) --static -c -o win-Utils.o Utils.cpp

clean:
	$(RM) $(TARGET)
