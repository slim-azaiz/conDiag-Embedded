CROSS_COMPILE=$(TOOLROOT)/bin/arm-TiVo-linux-gnueabi
CC=$(CROSS_COMPILE)-gcc

DESTDIR= ../sc_rootfs/scbin
TR69_DIR= $(SANDBOX)/../sdt_sagemcom/TR69
LIBCAP_DIR=$(TR69_DIR)/libcap-2.25

CFLAGS += -Wall -O -O2 -fPIC -fstack-protector-all
CFLAGS += -I$(TR69_DIR)/dbus 
CFLAGS += -I$(TR69_DIR)/sc-bus/include 
CFLAGS += -I$(LIBCAP_DIR)/libcap/include/
CFLAGS += -I$(LIBCAP_DIR)/libcap/
CFLAGS += -Iinclude/

LDFLAGS += -L$(TR69_DIR)/libCommon 
LDFLAGS += -ldbus-1
LDFLAGS += -lsc_bus
LDFLAGS += -L$(LIBCAP_DIR)/libcap/
LDFLAGS += -lcap

SOURCES=$(wildcard src/data/*.c src/my_server.c src/mongoose/*.c src/cjson/* src/utils/*.c )
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

PROG = bin/conDiag

all: $(PROG)

$(PROG): $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(CFLAGS) $(LDFLAGS)
	cp $(EXEC) $(PROG) $(DESTDIR)

# The Cleaner
clean:
	rm -f  $(EXEC) $(PROG)
	rm -rf build $(OBJECTS)

# The Install
install: all
	cp $(EXEC) $(PROG) $(DESTDIR)


# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
