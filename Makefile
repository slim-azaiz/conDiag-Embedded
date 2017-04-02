CROSS_COMPILE=$(TOOLROOT)/bin/arm-TiVo-linux-gnueabi
CC=$(CROSS_COMPILE)-gcc
CC=gcc

TR69= $(SANDBOX)/../sdt_sagemcom/TR69
CFLAGS += -g -W -Wall -Wextra -fPIC -rdynamic  
CFLAGS += -I$(TR69)/dbus 
CFLAGS += -I$(TR69)/sc-bus/include 

LDFLAGS += -L$(TR69)/libCommon 
LDFLAGS += -ldbus-1
LDFLAGS += -lsc_bus
LDFLAGS = 


SOURCES = src/simplest_web_server.c src/mongoose.c
#SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

EXEC=bin/gather
PROG = bin/server

all: $(EXEC) $(PROG)

#gather
bin/gather: src/get_data.o
		gcc  -o bin/gather  src/get_data.o $(CFLAGS) $(LDFLAGS) 

get_data.o: src/get_data.c src/get_data.h
		gcc -o src/get_data.o -c src/get_data.c $(CFLAGS) 
#server

$(PROG): $(SOURCES)
	  $(CC) $(SOURCES) -o $@ $(CFLAGS)


#bin/server: src/simplest_web_server.o
#		gcc $(CFLAGS) -o bin/server  src/simplest_web_server.o $(LDFLAGS) 

#src/simplest_web_server.o: src/mongoose.o
#		gcc $(CFLAGS) -o bin/server  src/mongoose.o $(LDFLAGS) 

#mongoose.o: src/mongoose.c src/mongoose.h
#		gcc -o src/mongoose.o -c src/mongoose.c $(CFLAGS) 




# The Cleaner
clean:
	rm -f *.o $(EXEC) $(PROG)
	rm -rf build $(OBJECTS)

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/


# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
