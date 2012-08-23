SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
OUT = witplayer

CFLAGS = -I.
LDFLAGS = -lpthread -lm

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFALGS) -o $@ $^ $(LDFLAGS) 

clean:
	@rm -rfv *.o $(OUT)
