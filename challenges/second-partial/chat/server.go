// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"time"
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

type user struct {
name string
ip string
isAdmin bool
chann  client
connec net.Conn
}

type msj struct {
msg string
chann  client
name string
}

var (
	entering = make(chan user)
	leaving  = make(chan user)
	messages = make(chan msj)
)

var usersNum int = 0

func broadcaster() {
	clients := make(map[string]user)
	for {
		select {
		case msg := <-messages:
			text := strings.Split(msg.msg, " ")
			if text[2]=="/users"{
				names := make([]string, 0, len(clients))
				for name := range clients {
					names = append(names, name)
  				}
				msg.chann <- strings.Join(names, ", ")
			}else if text[1]=="/msg" {
				if len(text)>3{
					if dest, exists := clients[text[2]]; !exists {
						msg.chann <- "irc-server > No Such User"
					} else{
            dest.chann <- "@" + msg.name + ": " + strings.Join(text[3:], " ")
					}
				}
			}else if text[1]=="/time"{
				_, e := time.LoadLocation("America/Mexico_City")
				if e != nil {
					log.Fatal(e)
				}
				msg.chann <- "irc-server > Local Time: " + time.Now().Format("01-02-2006 15:04:05")
			} else if text[1]=="/user"{
				if len(text)==3{
					if dest, exists := clients[text[2]]; !exists {
						msg.chann <- "irc-server > No Such User"
					}else{
            msg.chann <- "irc-server > username: " + dest.name + ", IP: " + dest.ip

					}
				}
			}else if text[1]=="/kick"{
				if clients[msg.name].isAdmin{
					if len(text)==3{
						if dest, exists := clients[text[2]]; exists {
							log.Printf("[%s] was kicked", dest.name)
							dest.chann <- "irc-server > You're kicked from this channel"
							dest.connec.Close()
							for _, client := range clients {
								client.chann <- "irc-server > [" + dest.name + "] was kicked from channel"
							}
						}else{
							msg.chann <- "irc-server > No Such User"
						}
					}
				}else{
					msg.chann <- "irc-server > Not Admin"
				}
			}else{
				for _, client := range clients {
					if msg.name!=client.name{
						client.chann <- msg.msg
					}
				}
			}

		case cli := <-entering:
			if _,exists := clients[cli.name]; exists {
				cli.chann <- "irc-server > Username already taken"
				cli.connec.Close()
			}else{
				cli.chann <- "irc-server > User [" + cli.name + "] successfully logged"
				msg := "irc-server > " + cli.name + " has arrived"
				for _, client := range clients {
					client.chann <- msg
				}
				clients[cli.name] = cli
			}

		case cli := <-leaving:
      usersNum--
			close(cli.chann)
			cli.connec.Close()
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	buffer := make([]byte, 1400)
	dataSize, err := conn.Read(buffer)
	if err != nil {
		log.Fatal(err)
	}
	who := string(buffer[:dataSize])

	ch <- "irc-server > Welcome to the Simple IRC Server"
  isAdm:= usersNum == 0
	entering <- user{name: who, ip: conn.RemoteAddr().String(), isAdmin: isAdm, chann: ch, connec: conn}
  usersNum++

  if isAdm {
		ch <- "Congrats, you were the first user."
		ch <- "You're the new IRC Server ADMIN"
	}

	input := bufio.NewScanner(conn)
	for input.Scan() {
		messages <- msj{who + ": " + input.Text(), ch, who}
	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- user{name: who, ip: conn.RemoteAddr().String(), isAdmin: isAdm, chann: ch, connec: conn}
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {


  if(len(os.Args)!=5){
    fmt.Println("Not enough arguments")
  }

  host := os.Args[2]
  port := os.Args[4]


	listener, err := net.Listen("tcp", host + ":" + port)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Simple IRC Server started at ", host)
	fmt.Println("Ready for receiving new clients")
	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main
