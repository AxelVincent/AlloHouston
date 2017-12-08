CC = gcc
CFLAGS = -Iheaders
SRCS = ./sources/main.c ./sources/service.c ./sources/train.c ./sources/outils.c ./sources/temps.c ./sources/requetes.c
OBJS = $(SRCS:.c=.o)
EXEC = ./bin/AlloHoustonServer

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	rm $(OBJS)
	@echo "MAKE - SER : On efface les fichiers objets"

clean :
	rm $(OBJS)
	@echo "MAKE - SER : On efface les fichiers objets"
