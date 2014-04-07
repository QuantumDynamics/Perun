include ../shared.settings.mk

flash: all
	$(OPENOCD) -f .\flash.cfg
	
