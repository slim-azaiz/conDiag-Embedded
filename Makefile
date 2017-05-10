CROSS_COMPILE=$(TOOLROOT)/bin/arm-TiVo-linux-gnueabi
CC=$(CROSS_COMPILE)-gcc

DESTDIR=$(TOOLROOT)/../dev-arm/tivo_root/bin/
DESTDIR1= ../sc_rootfs/scbin
TR69= $(SANDBOX)/../sdt_sagemcom/TR69
LIBCAP_DIR=$(TR69)/libcap-2.25

CFLAGS += -g -W -Wall -Wextra -fPIC -rdynamic 
CFLAGS += -I$(TR69)/dbus 
CFLAGS += -I$(TR69)/sc-bus/include 
CFLAGS += -I$(LIBCAP_DIR)/libcap/include/
CFLAGS += -I$(LIBCAP_DIR)/libcap/

LDFLAGS += -L$(TR69)/libCommon 
LDFLAGS += -ldbus-1
LDFLAGS += -lsc_bus
LDFLAGS += -L$(LIBCAP_DIR)/libcap/
LDFLAGS += -lcap
#LDFLAGS = 


SOURCES=$(wildcard src/data/*.c src/my_server.c src/mongoose/*.c src/cjson/* src/utils/*.c )
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

PROG = bin/conDiag

all: $(PROG)


$(PROG): $(SOURCES)
	  $(CC) $(SOURCES) -o $@ $(CFLAGS) $(LDFLAGS)

		cp $(EXEC) $(PROG) $(DESTDIR)
		cp $(EXEC) $(PROG) $(DESTDIR1)

# The Cleaner
clean:
	rm -f  $(EXEC) $(PROG)
	rm -rf build $(OBJECTS)

# The Install
install: all
	#	install -d $(DESTDIR)/$(PREFIX)/lib/
		cp $(EXEC) $(PROG) $(DESTDIR)
		cp $(EXEC) $(PROG) $(DESTDIR1)


# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
