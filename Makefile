# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Bolt_Graphics_config = debug
  Bolt_imgui_config = debug
  Bolt_Core_config = debug
  Bolt_Test_config = debug
  Bolt_Hermite_config = debug
  Bolt_Pong_config = debug
endif
ifeq ($(config),release)
  Bolt_Graphics_config = release
  Bolt_imgui_config = release
  Bolt_Core_config = release
  Bolt_Test_config = release
  Bolt_Hermite_config = release
  Bolt_Pong_config = release
endif

PROJECTS := Bolt-Graphics Bolt-imgui Bolt-Core Bolt-Test Bolt-Hermite Bolt-Pong

.PHONY: all clean help $(PROJECTS) Bolt-Core Bolt-Graphics Bolt-Hermite Bolt-Pong Bolt-Test Bolt-imgui

all: $(PROJECTS)

Bolt-Core: Bolt-Core

Bolt-Graphics: Bolt-Graphics

Bolt-Hermite: Bolt-Hermite

Bolt-Pong: Bolt-Pong

Bolt-Test: Bolt-Test

Bolt-imgui: Bolt-imgui

Bolt-Graphics:
ifneq (,$(Bolt_Graphics_config))
	@echo "==== Building Bolt-Graphics ($(Bolt_Graphics_config)) ===="
	@${MAKE} --no-print-directory -C Bolt-Graphics -f Makefile config=$(Bolt_Graphics_config)
endif

Bolt-imgui:
ifneq (,$(Bolt_imgui_config))
	@echo "==== Building Bolt-imgui ($(Bolt_imgui_config)) ===="
	@${MAKE} --no-print-directory -C Bolt-imgui -f Makefile config=$(Bolt_imgui_config)
endif

Bolt-Core: Bolt-Graphics Bolt-imgui
ifneq (,$(Bolt_Core_config))
	@echo "==== Building Bolt-Core ($(Bolt_Core_config)) ===="
	@${MAKE} --no-print-directory -C Bolt-Core -f Makefile config=$(Bolt_Core_config)
endif

Bolt-Test: Bolt-Core Bolt-imgui
ifneq (,$(Bolt_Test_config))
	@echo "==== Building Bolt-Test ($(Bolt_Test_config)) ===="
	@${MAKE} --no-print-directory -C Bolt-Test -f Makefile config=$(Bolt_Test_config)
endif

Bolt-Hermite: Bolt-Core Bolt-imgui
ifneq (,$(Bolt_Hermite_config))
	@echo "==== Building Bolt-Hermite ($(Bolt_Hermite_config)) ===="
	@${MAKE} --no-print-directory -C Bolt-Hermite -f Makefile config=$(Bolt_Hermite_config)
endif

Bolt-Pong: Bolt-Core Bolt-imgui
ifneq (,$(Bolt_Pong_config))
	@echo "==== Building Bolt-Pong ($(Bolt_Pong_config)) ===="
	@${MAKE} --no-print-directory -C Bolt-Pong -f Makefile config=$(Bolt_Pong_config)
endif

clean:
	@${MAKE} --no-print-directory -C Bolt-Graphics -f Makefile clean
	@${MAKE} --no-print-directory -C Bolt-imgui -f Makefile clean
	@${MAKE} --no-print-directory -C Bolt-Core -f Makefile clean
	@${MAKE} --no-print-directory -C Bolt-Test -f Makefile clean
	@${MAKE} --no-print-directory -C Bolt-Hermite -f Makefile clean
	@${MAKE} --no-print-directory -C Bolt-Pong -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Bolt-Graphics"
	@echo "   Bolt-imgui"
	@echo "   Bolt-Core"
	@echo "   Bolt-Test"
	@echo "   Bolt-Hermite"
	@echo "   Bolt-Pong"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"