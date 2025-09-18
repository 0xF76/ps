CC=gcc

all: srvv6 cliv6

allv4: srvv4 cliv4

srvv6: daytimetcpsrvv6.c 
	gcc -o srvv6 daytimetcpsrvv6.c 
srvv4: daytimetcpsrvv4.c 
	gcc -o srvv4 daytimetcpsrvv4.c

cliv6: daytimetcpcliv6.c 
	gcc -o cliv6 daytimetcpcliv6.c 
cliv4: daytimetcpcliv4.c 
	gcc -o cliv4 daytimetcpcliv4.c

clean:
	rm srvv6 cliv6
