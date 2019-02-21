.PHONY:all
all:server client
server:server.cc
	g++ -o $@ $^ -fpermissive -lpthread
client:client.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -f server client
