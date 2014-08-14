ifeq ($(OPT),1)
apple = apple red
banana = banana $(apple) yellow
apple = apple red again
endif

ifeq ($(OPT),2)
apple := apple red
banana := banana $(apple) yellow
apple := apple red again
endif

ifeq ($(OPT),3)
apple ?= apple red
banana ?= banana $(apple) yellow
apple ?= apple red again
endif

ifeq ($(OPT),4)
apple += apple red
banana += banana $(apple) yellow
apple += apple red again
endif

all:
	@echo $(apple)
	@echo $(banana)
