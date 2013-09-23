# (c) Tudor Dumitras, 2006-2007

MY_LIB_NAME     = libinterceptor.so.1

CC 	= gcc
CXX	= g++
CFLAGS 	= -fpic -shared  	\
	  -O3                   \
	  -Wwrite-strings -Wall \
	  -Winline              \
	  -pedantic
LDFLAGS = -Wl,-h -Wl,$(MY_LIB_NAME) 
LDLIBS	= -ldl


all: $(MY_LIB_NAME) trace_logger

$(MY_LIB_NAME): modified_fun.cpp function_pointers.cpp interceptorstate.cpp tracec.cpp interc_defs.h interceptor.h tracec.h Makefile
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ modified_fun.cpp function_pointers.cpp interceptorstate.cpp tracec.cpp $(LDLIBS)

trace_logger: trace_logger.cpp tracec.h interc_defs.h Makefile
	$(CXX) -O3 -o $@ trace_logger.cpp

clean:
	rm $(MY_LIB_NAME)
	rm trace_logger
	rm *~
