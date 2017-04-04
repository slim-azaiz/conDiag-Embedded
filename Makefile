CROSS_COMPILE=$(TOOLROOT)/bin/arm-TiVo-linux-gnueabi
CC=$(CROSS_COMPILE)-gcc

DESTDIR=$(TOOLROOT)/../dev-arm/tivo_root/bin/
TR69= $(SANDBOX)/../sdt_sagemcom/TR69
CFLAGS += -g -W -Wall -Wextra -fPIC -rdynamic  
CFLAGS += -I$(TR69)/dbus 
CFLAGS += -I$(TR69)/sc-bus/include 

LDFLAGS += -L$(TR69)/libCommon 
LDFLAGS += -ldbus-1
LDFLAGS += -lsc_bus
#LDFLAGS = 


SOURCES=$(wildcard src/data/*.c src/my_server.c src/mongoose/*.c src/cjson/*)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

PROG = bin/myGather

all: $(PROG)


$(PROG): $(SOURCES)
	  $(CC) $(SOURCES) -o $@ $(CFLAGS) $(LDFLAGS)


# The Cleaner
clean:
	rm -f  $(EXEC) $(PROG)
	rm -rf build $(OBJECTS)

# The Install
install: all
	#	install -d $(DESTDIR)/$(PREFIX)/lib/
		cp $(EXEC) $(PROG) $(DESTDIR)


# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
