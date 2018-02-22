CC = bcc32
ILINK = ilink32
SRC = ..\src
INC = ..\h
OBJ = obj
BIN = bin
RES = ..\res
CFLAGS = -I$(INC) -P -O2 -w

$(BIN)\keep_isp.exe: directories $(OBJ)\keep_isp.obj $(OBJ)\keep_isp.res
		$(ILINK) c0w32.obj $(OBJ)\keep_isp.obj,$(BIN)\keep_isp.exe,$(BIN)\keep_isp,cw32.lib import32.lib,,$(OBJ)\keep_isp.res

$(OBJ)\keep_isp.obj: $(SRC)\keep_isp.cpp
		$(CC) $(CFLAGS) -c -o$(OBJ)\keep_isp.obj $(SRC)\keep_isp.cpp

$(OBJ)\keep_isp.res: $(RES)\keep_isp.rc $(INC)\keep_isp.h $(RES)\keep_isp.ico
		brc32 -r -32 -i$(INC);$(RES) -fo$(OBJ)\keep_isp.res $(RES)\keep_isp.rc

directories:
		if not exist $(BIN) mkdir $(BIN)
		if not exist $(OBJ) mkdir $(OBJ)

clean:
		if exist $(BIN) rmdir /Q /S $(BIN)
		if exist $(OBJ) rmdir /Q /S $(OBJ)
