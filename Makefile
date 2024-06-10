CC=gcc
CFLAGS=-Wall -Werror

TARGET_EXEC := canyon-bomber
TAREGT_INSTALL := resources.tar.gz
	
SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
BIN_DIR := ./build/bin
OBJ_DIR := ./build/obj

PATH_ALLEGRO := /usr/lib/x86_64-linux-gnu
LIB_ALLEGRO := -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_primitives -lallegro_ttf -lallegro_video

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.c.o))
INC_FLAGS := $(addprefix -I,$(INCLUDE_DIR))
CPPFLAGS := $(INC_FLAGS)
ALFLAGS := -L $(PATH_ALLEGRO) $(LIB_ALLEGRO) 

$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	$(info Building finished)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJS) -o $@ $(ALFLAGS)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(info Building $@...)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(info Removing binaries/objects...)
	@rm -r $(BUILD_DIR)

.PHONY: install
install:
	$(info Installing resources...)
	@tar xf $(TAREGT_INSTALL) -C $(BUILD_DIR)
