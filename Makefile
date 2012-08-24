SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
OUT = witplayer

CFLAGS = -I. -Wall `pkg-config gstreamer-0.10 --cflags`
LDFLAGS = -lpthread -lm `pkg-config gstreamer-0.10 --libs`

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFALGS) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rfv *.o $(OUT)
