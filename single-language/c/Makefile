debug ?= 1
years := $(wildcard 20*/)
basecflags := -std=gnu11 -MMD -MP
baseldflags :=
ifeq ($(debug),1)
basecflags += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Werror -ggdb3 -fsanitize=address
baseldflags += -fsanitize=address
else
basecflags += -O2
endif
basecppflags := -isystem include

.PHONY: all clean

year_exes = $(foreach day,$(days),$(year_bindir)/day$(day))
year_srcdir = $(year)/$(day)/src
year_bindir = bin/$(year)
year_objdir = obj/$(year)
obj :=
exe :=

define year_obj
$(year_objdir)/$(day)/$(1).o: $(year_srcdir)/$(1).c
obj += $(year_objdir)/$(day)/$(1).o

endef

libadvent := lib/libadvent.a

define year_exe
$(year_bindir)/day$(day): $(day_objs) $(libadvent)
exe += $(year_bindir)/day$(day)

endef

define year_test
.PHONY: test-$(1)-$(2)
test-$(1)-$(2): $(year_bindir)/day$(2)
	@echo TEST $(1)-$(2)-simple
	@$(year_bindir)/day$(2) $(1)/$(2)/simple.txt
	@echo TEST $(1)-$(2)-full
	@$(year_bindir)/day$(2) $(1)/$(2)/full.txt

endef

define genrules
$(foreach day,$(days),$(call year_exe))
$(foreach day,$(days),$(foreach src,$(join main,$(patsubst %.c,%,$(day$(day)_src))),$(call year_obj,$(src))))

endef

year_tests = $(foreach day,$(days),test-$(year)-$(day))

all: $(foreach year,$(years),all-$(year:/=))

test: $(foreach year,$(years),test-$(year:/=))

advent_src := $(wildcard src/*.c)
advent_obj := $(patsubst src/%.c,obj/advent/%.o,$(advent_src))

advent_ldflags := $(base_ldflags)

$(libadvent): $(advent_obj)
	@$(DIR_DUP)
	$(info AR $@)
	@$(AR) rcs $@ $^

define mkobj
obj/advent/$(1).o: src/$(1).c
obj += obj/advent/$(1).o

endef

$(foreach name,$(patsubst src/%.c,%,$(advent_src)),$(eval $(call mkobj,$(name))))

baseldflags += -L ./lib -l advent

include $(foreach year,$(years),$(join $(year),year.mak))
include utils.mak

$(obj): %.o:
	@$(DIR_DUP)
	$(info CC $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $^

-include $(obj:.o=.d)

$(exe): %:
	@$(DIR_DUP)
	$(info LD $@)
	@$(CC) $(LDFLAGS) $^ -o $@

clean:
	$(RM) -r bin obj

