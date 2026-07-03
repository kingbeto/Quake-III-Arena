#
# Quake III Arena - macOS arm64 build
#

ARCH ?= arm64
BUILD_DIR ?= build
ifeq ($(ARCH),x86_64)
MIN_OS_VERSION = 10.13
else
MIN_OS_VERSION = 11.0
endif
CODE_DIR = ..
APP_NAME = Quake3
APP_BUNDLE = $(BUILD_DIR)/$(APP_NAME).app
APP_BIN = $(APP_BUNDLE)/Contents/MacOS/$(APP_NAME)

CC = clang
CXX = clang++
ARCH_FLAGS = -arch $(ARCH)

CFLAGS = $(ARCH_FLAGS) -O2 -Wall -Wno-unknown-pragmas -Wno-four-char-constants \
	-Wno-deprecated-declarations -Wno-unused-value -Wno-logical-op-parentheses \
	-Wno-pointer-sign -Wno-implicit-int -Wno-deprecated-non-prototype \
	-DMACOS_X -DBOTLIB -DMISSIONPACK -DSMP

OBJCFLAGS = $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LDFLAGS = $(ARCH_FLAGS) -Wl,-headerpad_max_install_names
BUNDLE_LDFLAGS = $(ARCH_FLAGS) -bundle -undefined dynamic_lookup
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework CoreAudio \
	-framework AudioToolbox -framework IOKit -framework ApplicationServices \
	-framework CoreFoundation -framework CoreServices

INCLUDES = -I$(CODE_DIR)/qcommon -I$(CODE_DIR)/client -I$(CODE_DIR)/server \
	-I$(CODE_DIR)/renderer -I$(CODE_DIR)/botlib -I$(CODE_DIR)/game \
	-I$(CODE_DIR)/cgame -I$(CODE_DIR)/ui -I$(CODE_DIR)/q3_ui \
	-I$(CODE_DIR)/jpeg-6 -I$(CODE_DIR)/splines -I.

# Engine (no game modules — those are separate bundles)
ENGINE_C_DIRS = client server renderer qcommon botlib
ENGINE_C_SRCS = $(foreach d,$(ENGINE_C_DIRS),$(wildcard $(CODE_DIR)/$(d)/*.c))
ENGINE_C_SRCS += $(CODE_DIR)/game/q_math.c $(CODE_DIR)/game/q_shared.c
ENGINE_C_SRCS := $(filter-out %/vm_x86.c %/vm_ppc.c %/vm_ppc_new.c %/sv_rankings.c %/vm_interpreted.c,$(ENGINE_C_SRCS))
ENGINE_C_SRCS += $(CODE_DIR)/qcommon/vm_interpreted.c
ENGINE_C_SRCS += $(CODE_DIR)/unix/unix_net.c $(CODE_DIR)/unix/unix_shared.c
ENGINE_C_SRCS += \
	$(CODE_DIR)/jpeg-6/jcapimin.c \
	$(CODE_DIR)/jpeg-6/jchuff.c \
	$(CODE_DIR)/jpeg-6/jcinit.c \
	$(CODE_DIR)/jpeg-6/jccoefct.c \
	$(CODE_DIR)/jpeg-6/jccolor.c \
	$(CODE_DIR)/jpeg-6/jfdctflt.c \
	$(CODE_DIR)/jpeg-6/jcdctmgr.c \
	$(CODE_DIR)/jpeg-6/jcmainct.c \
	$(CODE_DIR)/jpeg-6/jcmarker.c \
	$(CODE_DIR)/jpeg-6/jcmaster.c \
	$(CODE_DIR)/jpeg-6/jcomapi.c \
	$(CODE_DIR)/jpeg-6/jcparam.c \
	$(CODE_DIR)/jpeg-6/jcprepct.c \
	$(CODE_DIR)/jpeg-6/jcsample.c \
	$(CODE_DIR)/jpeg-6/jctrans.c \
	$(CODE_DIR)/jpeg-6/jdapimin.c \
	$(CODE_DIR)/jpeg-6/jdapistd.c \
	$(CODE_DIR)/jpeg-6/jdatasrc.c \
	$(CODE_DIR)/jpeg-6/jdatadst.c \
	$(CODE_DIR)/jpeg-6/jdcoefct.c \
	$(CODE_DIR)/jpeg-6/jdcolor.c \
	$(CODE_DIR)/jpeg-6/jcphuff.c \
	$(CODE_DIR)/jpeg-6/jddctmgr.c \
	$(CODE_DIR)/jpeg-6/jdhuff.c \
	$(CODE_DIR)/jpeg-6/jdinput.c \
	$(CODE_DIR)/jpeg-6/jdmainct.c \
	$(CODE_DIR)/jpeg-6/jdmarker.c \
	$(CODE_DIR)/jpeg-6/jdmaster.c \
	$(CODE_DIR)/jpeg-6/jdpostct.c \
	$(CODE_DIR)/jpeg-6/jdsample.c \
	$(CODE_DIR)/jpeg-6/jdtrans.c \
	$(CODE_DIR)/jpeg-6/jerror.c \
	$(CODE_DIR)/jpeg-6/jidctflt.c \
	$(CODE_DIR)/jpeg-6/jmemmgr.c \
	$(CODE_DIR)/jpeg-6/jmemnobs.c \
	$(CODE_DIR)/jpeg-6/jutils.c

ENGINE_CXX_SRCS = $(filter-out %/q_shared.cpp,$(wildcard $(CODE_DIR)/splines/*.cpp))

OBJC_SRCS = \
	macosx_sys.m \
	macosx_glimp.m \
	macosx_display.m \
	macosx_input.m \
	macosx_sndcore.m \
	macosx_timers.m \
	macosx_glsmp_mutex.m \
	Q3Controller.m
# macosx_glsmp_ports.m is unused; SMP uses the mutex-based GL backend above.

MACOSX_C_SRCS = growlist.c

GAME_CFLAGS = $(CFLAGS) -DQAGAME
CGAME_CFLAGS = $(CFLAGS) -DCGAME
UI_CFLAGS = $(CFLAGS) -DUI

GAME_SRCS = $(filter-out %/g_rankings.c,$(wildcard $(CODE_DIR)/game/*.c))
CGAME_SRCS = $(filter-out %/cg_particles.c,$(wildcard $(CODE_DIR)/cgame/*.c))
UI_Q3UI_SRCS = $(filter-out %/ui_rankings.c %/ui_rankstatus.c %/ui_signup.c %/ui_login.c %/ui_specifyleague.c,$(wildcard $(CODE_DIR)/q3_ui/*.c))
UI_GAME_SRCS = $(CODE_DIR)/game/bg_misc.c $(CODE_DIR)/game/bg_lib.c $(CODE_DIR)/game/q_math.c

ENGINE_C_OBJS = $(patsubst $(CODE_DIR)/%.c,$(BUILD_DIR)/%.o,$(ENGINE_C_SRCS))
ENGINE_CXX_OBJS = $(patsubst $(CODE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(ENGINE_CXX_SRCS))
OBJC_OBJS = $(patsubst %.m,$(BUILD_DIR)/macosx/%.o,$(OBJC_SRCS))
MACOSX_C_OBJS = $(patsubst %.c,$(BUILD_DIR)/macosx/%.o,$(MACOSX_C_SRCS))

GAME_OBJS = $(patsubst $(CODE_DIR)/game/%.c,$(BUILD_DIR)/game/%.o,$(GAME_SRCS))
CGAME_OBJS = $(patsubst $(CODE_DIR)/cgame/%.c,$(BUILD_DIR)/cgame/%.o,$(CGAME_SRCS))
UI_OBJS = $(patsubst $(CODE_DIR)/q3_ui/%.c,$(BUILD_DIR)/q3_ui/%.o,$(UI_Q3UI_SRCS))
UI_OBJS += $(patsubst $(CODE_DIR)/game/%.c,$(BUILD_DIR)/ui/game/%.o,$(UI_GAME_SRCS))
UI_OBJS += $(BUILD_DIR)/ui/ui_syscalls.o

QAGAME_BUNDLE = $(BUILD_DIR)/qagame.bundle
CGAME_BUNDLE = $(BUILD_DIR)/cgame.bundle
UI_BUNDLE = $(BUILD_DIR)/ui.bundle

.PHONY: all clean install

all: $(APP_BIN) $(QAGAME_BUNDLE) $(CGAME_BUNDLE) $(UI_BUNDLE)
	@mkdir -p $(APP_BUNDLE)/Contents/MacOS
	cp -R $(QAGAME_BUNDLE) $(CGAME_BUNDLE) $(UI_BUNDLE) $(APP_BUNDLE)/Contents/MacOS/
	@if [ -d baseq3 ]; then mkdir -p $(BUILD_DIR)/baseq3 && cp -n baseq3/*.pk3 $(BUILD_DIR)/baseq3/ 2>/dev/null || cp baseq3/*.pk3 $(BUILD_DIR)/baseq3/; fi
	@echo "Built $(APP_BUNDLE) with game bundles"

$(APP_BIN): $(ENGINE_C_OBJS) $(ENGINE_CXX_OBJS) $(OBJC_OBJS) $(MACOSX_C_OBJS) Info.plist
	@mkdir -p $(APP_BUNDLE)/Contents/MacOS
	@mkdir -p $(APP_BUNDLE)/Contents/Resources
	$(CC) $(LDFLAGS) -o $@ $(ENGINE_C_OBJS) $(ENGINE_CXX_OBJS) $(OBJC_OBJS) $(MACOSX_C_OBJS) $(FRAMEWORKS) -lc++
	sed -e 's/@ARCH@/$(ARCH)/g' -e 's/@MIN_OS@/$(MIN_OS_VERSION)/g' Info.plist > $(APP_BUNDLE)/Contents/Info.plist

$(QAGAME_BUNDLE): $(GAME_OBJS)
	@mkdir -p $(QAGAME_BUNDLE)/Contents/MacOS
	$(CC) $(BUNDLE_LDFLAGS) -o $(QAGAME_BUNDLE)/Contents/MacOS/qagame $(GAME_OBJS)
	cp qagame.bundle.plist $(QAGAME_BUNDLE)/Contents/Info.plist

$(CGAME_BUNDLE): $(CGAME_OBJS)
	@mkdir -p $(CGAME_BUNDLE)/Contents/MacOS
	$(CC) $(BUNDLE_LDFLAGS) -o $(CGAME_BUNDLE)/Contents/MacOS/cgame $(CGAME_OBJS)
	cp cgame.bundle.plist $(CGAME_BUNDLE)/Contents/Info.plist

$(UI_BUNDLE): $(UI_OBJS)
	@mkdir -p $(UI_BUNDLE)/Contents/MacOS
	$(CC) $(BUNDLE_LDFLAGS) -o $(UI_BUNDLE)/Contents/MacOS/ui $(UI_OBJS)
	cp ui.bundle.plist $(UI_BUNDLE)/Contents/Info.plist

$(BUILD_DIR)/%.o: $(CODE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(CODE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/macosx/%.o: %.m
	@mkdir -p $(dir $@)
	$(CC) $(OBJCFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/macosx/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/game/%.o: $(CODE_DIR)/game/%.c
	@mkdir -p $(dir $@)
	$(CC) $(GAME_CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/cgame/%.o: $(CODE_DIR)/cgame/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CGAME_CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/q3_ui/%.o: $(CODE_DIR)/q3_ui/%.c
	@mkdir -p $(dir $@)
	$(CC) $(UI_CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/ui/game/%.o: $(CODE_DIR)/game/%.c
	@mkdir -p $(dir $@)
	$(CC) $(UI_CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/ui/ui_syscalls.o: $(CODE_DIR)/ui/ui_syscalls.c
	@mkdir -p $(dir $@)
	$(CC) $(UI_CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

install: all
	@echo "Place baseq3/ with pak files beside $(APP_BUNDLE)"
