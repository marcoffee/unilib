include Makefile.builtem

include ../unilib/Makefile.include

TESTS = $(foreach test,compile conversion normalization strip ucd,test_$(test))
UNICODE = 13.0.0

.PHONY: all compile test
all: compile
compile: $(call exe,$(TESTS))
test: $(addprefix run_,$(TESTS))

run_test_compile: $(call exe,test_compile)
run_test_conversion: $(call exe,test_conversion)
	python3 test_conversion_input.py | ./$<
run_test_normalization: $(call exe,test_normalization)
	python3 test_normalization_input.py ../gen/data/NormalizationTest-$(UNICODE).txt.xz | ./$<
run_test_strip: $(call exe,test_strip)
	./$<
run_test_ucd: $(call exe,test_ucd)
	python3 test_ucd_input.py ../gen/data/UnicodeData-$(UNICODE).txt.xz | ./$<

C_FLAGS += $(call include_dir,../unilib)
$(call exe,test_compile): $(call obj,$(addprefix ../unilib/,$(UNILIB_OBJECTS)))
$(call exe,test_conversion): $(call obj,$(addprefix ../unilib/,unicode utf8 utf16))
$(call exe,test_normalization): $(call obj,$(addprefix ../unilib/,uninorms))
$(call exe,test_strip): $(call obj,$(addprefix ../unilib/,unicode uninorms unistrip))
$(call exe,test_ucd): $(call obj,$(addprefix ../unilib/,unicode))
$(call exe,$(TESTS)):$(call exe,%): $$(call obj,%)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

.PHONY: clean
clean:
	$(call rm,.build $(call all_exe,$(TESTS)))
