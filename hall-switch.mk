#############################################
# Makefile for CYPRESS WICED WICED 43xxx ####
#############################################
# Include library folder in "libraries/drivers/sensors".
# Add lib to demo or snipped to the makefile
# variable $(NAME)_COMPONENTS += libraries/drivers/sensors

NAME := Lib_hall_switch

GLOBAL_DEFINES   := HALL_SWITCH_FRAMEWORK=HALL_SWITCH_FRMWK_WICED

GLOBAL_INCLUDES  := src/config							\
					src/corelib 				  		\
					src/pal								\
					src/framework/wiced-43xxx/pal 		\
					src/framework/wiced-43xxx/wrapper

$(NAME)_SOURCES  := src/corelib/hall-switch.cpp						    	\
					src/corelib/hall-switch-int.cpp							\
					src/framework/wiced-43xxx/pal/hall-pal-wiced.cpp		\
					src/framework/wiced-43xxx/wrapper/hall-switch-wiced.cpp	\
					src/framework/wiced-43xxx/wrapper/hall-platf-wiced.cpp	

VALID_PLATFORMS	 := CYW943907AEVAL1F