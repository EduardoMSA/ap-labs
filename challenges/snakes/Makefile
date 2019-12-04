default: run

build:
	go get -u github.com/nsf/termbox-go
	go get github.com/mattn/go-runewidth
	go build -v -o ./SNAKES

run: build
	./SNAKES

clean:
	$(RM) SNAKES
