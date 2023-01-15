CPPFLAGS := $(basecppflags)
CFLAGS := $(basecflags)
LDFLAGS := $(baseldflags)

.PHONY: all-2015

year := 2015
days := \
	01 \
	02 \
	03

selfdir := 2015/

day_srcs = src/$(day)/main.c $(patsubst %,src/$(day)/%,$(day$(day)_src))
day_objs = $(patsubst src/$(day)/%.c,$(year_objdir)/$(day)/%.o,$(day_srcs))

$(eval $(foreach day,$(days),$(call year_test,$(year),$(day))))

all-2015: $(year_exes)

test-2015: all-2015 $(year_tests)

$(eval $(call genrules))

