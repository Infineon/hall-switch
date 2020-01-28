NAME := App_hall_switch

GLOBAL_DEFINES   := HALL_SWITCH_WICED_PLATFORM_ENABLED

$(NAME)_INCLUDES :=  hall-switch/src/common 								\
					 hall-switch/src/pal/cypress/wiced-43xxx

$(NAME)_SOURCES := 	hall_switch.cpp													\
					hall-switch/src/common/hall-switch.cpp						    \
					hall-switch/src/pal/cypress/wiced-43xxx/hall-switch-wiced.cpp	

VALID_PLATFORMS	:= CYW943907AEVAL1F