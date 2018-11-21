default: all
.PHONY : default 

static:
	$(MAKE) -f libapev.mk

shared:
	$(MAKE) -f libapev_shared.mk

example:
	$(MAKE) -f example.mk

all:
	$(MAKE) -f libapev.mk
	$(MAKE) -f libapev_shared.mk
	$(MAKE) -f example.mk

clean : 
	$(MAKE) -f libapev.mk clean
	$(MAKE) -f libapev_shared.mk clean
	$(MAKE) -f example.mk clean

.PHONY : all static shared example clean
