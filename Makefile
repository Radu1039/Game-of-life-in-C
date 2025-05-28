CC = gcc
CFLAGS = -O2 -Wall
SRC = GameofLife.c
OUT = a.out
FCT = functii.c

INPUT_FILES = $(wildcard InputData/data*.in)

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(FCT) -o $(OUT)

run: $(OUT)
	./$(OUT) InputData/data1.in OutputData/data1.out InputData/data2.in OutputData/data2.out InputData/data3.in OutputData/data3.out InputData/data4.in OutputData/data4.out InputData/data5.in OutputData/data5.out InputData/data6.in OutputData/data6.out InputData/data7.in OutputData/data7.out InputData/data8.in OutputData/data8.out InputData/data9.in OutputData/data9.out InputData/data10.in OutputData/data10.out InputData/data11.in OutputData/data11.out InputData/data12.in OutputData/data12.out InputData/data13.in OutputData/data13.out InputData/data14.in OutputData/data14.out InputData/data15.in OutputData/data15.out InputData/data16.in OutputData/data16.out InputData/data17.in OutputData/data17.out InputData/data18.in OutputData/data18.out InputData/data19.in OutputData/data19.out InputData/data20.in OutputData/data20.out

clean:
	rm -f $(OUT)
