CC = gcc
CFLAGS = -Wall -Wextra -pthread
LDFLAGS = -lm
DEPS = stPipeline.h queue.h ActiveObject.h
OBJ = stPipeline.o queue.o ActiveObject.o
EXEC = st_pipeline

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXEC)
