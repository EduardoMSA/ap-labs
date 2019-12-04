package main

import (
	"./snake"
	"fmt"
	)

func main() {
	/*
	if len(os.Args)==2{
		if fN,err := strconv.Atoi(os.Args[1]); err!=nil{
			fmt.Println(err)
		} else{
			snake.NewGame(fN).Start()
		}

	} else{
		fmt.Println("Specify the food quantity")
		fmt.Println("./SNAKES ##")
	}*/

	var fN int
	fmt.Println("Enter Food Quantity : ")
  _, err := fmt.Scanf("%d", &fN)
	if err != nil {
  	fmt.Println(err)
  }
	snake.NewGame(fN).Start()


}
