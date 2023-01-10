CPPFLAGS := $(basecppflags)
CFLAGS := $(basecflags)
LDFLAGS := $(baseldflags)

.PHONY: all-2022

year := 2022
days := \
	01 \
	02

selfdir := 2022/

day_srcs = src/$(day)/main.c $(patsubst %,src/$(day)/%,$(day$(day)_src))
day_objs = $(patsubst src/$(day)/%.c,$(year_objdir)/$(day)/%.o,$(day_srcs))

$(eval $(foreach day,$(days),$(call year_test,$(year),$(day))))

all-2022: $(year_exes)

test-2022: all-2022 $(year_tests)

$(eval $(call genrules))

