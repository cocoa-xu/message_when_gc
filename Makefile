PRIV_DIR = $(MIX_APP_PATH)/priv
NIF_SO = $(PRIV_DIR)/message_when_gc.so

C_SRC = $(shell pwd)/c_src
CPPFLAGS += -shared -std=c11 -O3 -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fPIC
CPPFLAGS += -I$(ERTS_INCLUDE_DIR)

UNAME_S := $(shell uname -s)
ifndef TARGET_ABI
ifeq ($(UNAME_S),Darwin)
	TARGET_ABI = darwin
endif
endif

ifeq ($(TARGET_ABI),darwin)
	CPPFLAGS += -undefined dynamic_lookup -flat_namespace -Wno-unused-function
endif

.DEFAULT_GLOBAL := build

build: $(NIF_SO)
	@ echo > /dev/null

$(NIF_SO):
	@ mkdir -p $(PRIV_DIR)
	$(CC) $(CPPFLAGS) $(C_SRC)/message_when_gc.c -o $(NIF_SO)
