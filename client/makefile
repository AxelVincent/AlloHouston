CC = gcc
CFLAGS = -Iheaders
SRCS =   ./sources/main.c
OBJS = $(SRCS:.c=.o)
EXEC = AlloHoustonClient

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	rm $(OBJS)
	@echo "MAKE - CLI : On efface les fichiers objets"

clean :
	rm $(OBJS)
	@echo "MAKE - CLI : On efface les fichiers objets"
