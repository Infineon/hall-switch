#############################################
# Makefile for CYPRESS WICED WICED 43xxx ####
#############################################
# Include library folder in "libraries/drivers/sensors".
# Add lib to demo or snipped to the makefile
# variable $(NAME)_COMPONENTS += libraries/drivers/sensors

NAME := Lib_hall_switch

GLOBAL_DEFINES   := HALL_SWITCH_WICED_PLATFORM_ENABLED

GLOBAL_INCLUDES  := src/common 				\
					src/pal/cypress/wiced-43xxx

$(NAME)_SOURCES  := src/common/hall-switch.cpp						    \
					src/pal/cypress/wiced-43xxx/hall-switch-wiced.cpp	

VALID_PLATFORMS	 := CYW943907AEVAL1F