CC = gcc
CFLAGS = -Iheaders
SRCS =   ./sources/main.c ./sources/service.c
OBJS = $(SRCS:.c=.o)
EXEC = AlloHoustonServer

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	rm $(OBJS)
	@echo "MAKE - SER : On efface les fichiers objets"

clean :
	rm $(OBJS)
	@echo "MAKE - SER : On efface les fichiers objets"
