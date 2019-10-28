// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 227.

// Netcat is a simple read/write client for TCP servers.
package main

import (
	"io"
	"fmt"
	"log"
	"net"
	"os"
)

//!+
func main() {
	var user, port string
	if len(os.Args)!=5 {
		fmt.Println(len(os.Args))
		fmt.Println("./ client --user xxxx --server xxxx")
		os.Exit(1)
	}

	if os.Args[1] != "-user" || os.Args[3] != "-server" {
		fmt.Println(os.Args[1] + " " + os.Args[3])
		fmt.Println("./ client --user xxxx --server xxxx")

		os.Exit(1)
	}


	user = os.Args[2]
	port = os.Args[4]

	conn, err := net.Dial("tcp", port)
	if err != nil {
		log.Fatal(err)
	}
	done := make(chan struct{})
	go func() {
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()

	_, err1 := conn.Write([]byte(user))
	if err1 != nil {
		log.Fatal(err)
	}

	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

//!-

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}
