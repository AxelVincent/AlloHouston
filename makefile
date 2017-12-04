CC = gcc
CFLAGS = -Iheaders
SRCS =   ./serveur/sources/main.c
OBJS = $(SRCS:.c=.o)
EXEC = AlloHuston

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	rm $(OBJS)
	@echo "On efface les fichiers objets"

clean :
	rm $(OBJS)
	@echo "On efface les fichiers objets"