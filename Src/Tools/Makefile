

EXECUTABLE := main    # 可执行文件名
STATICLIB := Tools.a
LIBDIR :=              # 静态库目录
LIBS :=   pthread            # 静态库文件名
INCLUDES:=../          # 头文件目录
SRCDIR:=../           # 除了当前目录外，其他的源代码文件目录
#
# # Now alter any implicit rules' variables if you like, e.g.:

CROSS_DIR =
CROSS_COMPILE	= $(CROSS_DIR)

CC :=  $(CROSS_COMPILE)g++
CCP=  $(CROSS_COMPILE)g++
LD =  $(CROSS_COMPILE)ld
STRIP=$(CROSS_COMPILE)strip
AR =  $(CROSS_COMPILE)ar
AS =  $(CROSS_COMPILE)as
CFLAGS := #-g -Wall -O3
CPPFLAGS := $(CFLAGS)
CPPFLAGS += $(addprefix -I,$(INCLUDES))
CPPFLAGS += #-MMD
#
# # The next bit checks to see whether rm is in your djgpp bin
# # directory; if not it uses del instead, but this can cause (harmless)
# # `File not found' error messages. If you are not using DOS at all,
# # set the variable to something which will unquestioningly remove
# # files.
#

RM-F := rm -f


# # You shouldn't need to change anything below this point.
#
SRCS := $(wildcard *.cpp) $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cpp,$(MISSING_DEPS)))


.PHONY : all deps objs clean veryclean rebuild info

all: $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
	@$(RM-F) *.o
	@$(RM-F) *.d
	@$(RM-F) *.a
veryclean: clean
	@$(RM-F) $(EXECUTABLE)
	@$(RM-F) *.a

rebuild: veryclean all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM-F) $(patsubst %.d,%.o,$@)
endif
-include $(DEPS)
$(EXECUTABLE) : $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
	
staticlibs: $(OBJS)
	$(AR) -rc $(STATICLIB) $(OBJS)

info:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(MISSING_DEPS)
	@echo $(MISSING_DEPS_SOURCES)