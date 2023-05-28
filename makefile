CC = gcc
CFLAGS = -Wall -Wextra -pthread
LDFLAGS = -lm
DEPS = stPipeline.h queue.h ActiveObject.h
OBJ = stPipeline.o queue.o ActiveObject.o
EXEC = st_pipeline

all: $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean all

clean:
	rm -f $(OBJ) $(EXEC)
