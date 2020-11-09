LDFLAGS=$(shell pkg-config --libs libupnp)
CFLAGS=$(shell pkg-config --cflags libupnp)

all: upli
