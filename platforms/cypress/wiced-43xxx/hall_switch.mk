NAME := App_hall_switch

$(NAME)_INCLUDES :=  hall-switch/src/hal 								\
					 hall-switch/platforms/cypress/wiced-43xxx

$(NAME)_SOURCES := 	hall_switch.cpp													\
					hall-switch/src/hal/hall-switch.cpp								\
					hall-switch/platforms/cypress/wiced-43xxx/hall-switch-wiced.cpp	