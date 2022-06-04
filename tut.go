package main

import (
	"C"
	"fmt"
	"os/exec"
)

func main() {
	res, err := exec.Command("./hola.exe").Output()
	if err != nil {
		panic(err)
	}
	fmt.Printf("OUTPUT: %s", res)
}
