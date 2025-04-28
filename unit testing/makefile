CC = gcc
CFLAGS = -Iinclude -Imock -Ihcsr -Iproximity

SRCS = main.c \
       hcsr/HCSR.c \
       proximity/Proximity.c \
       mock/mock_hal_gpio.c \
       mock/mock_hal_uart.c \
       mock/mock_hal_delay.c

OBJS = $(SRCS:.c=.o)
all: test_hcsr test_proximity

default: main test_hcsr test_proximity

main: $(OBJS)
	$(CC) -o main $(OBJS)

test_hcsr: test/test_hcsr.c hcsr/HCSR.c
	gcc -Iinclude -Imock -Ihcsr -Iproximity -o test_hcsr test/test_hcsr.c hcsr/HCSR.c mock/mock_hal_gpio.c mock/mock_hal_delay.c mock/mock_hal_uart.c


test_proximity: test/test_proximity.c hcsr/HCSR.c proximity/Proximity.c mock/mock_hal_gpio.c mock/mock_hal_delay.c mock/mock_hal_uart.c
    gcc -Iinclude -Imock -Ihcsr -Iproximity -o test_proximity test/test_proximity.c hcsr/HCSR.c proximity/Proximity.c mock/mock_hal_gpio.c mock/mock_hal_delay.c mock/mock_hal_uart.c


clean:
	rm -f $(OBJS) main test_hcsr test_proximity
	rm -f hcsr/*.o proximity/*.o mock/*.o test/*.o
	rm -f *.dSYM
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov