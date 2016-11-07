INC_DIR = -I ./lib_ev3/source/ev3 -I ./robot/include
OBJ_DIR = obj/
C_FILES = $(wildcard robot/src/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR),$(notdir $(C_FILES:.c=.o)))


CFLAGS = $(INC_DIR) -Wall -O0 -g
LDFLAGS = -lm -lbluetooth -pthread

robot: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o run $^ lib_ev3/lib/libev3dev-c.a $(LDFLAGS)

obj/%.o: robot/src/%.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	rm -rf $(OBJ_DIR)
	rm -f robot
