package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	var nDir, nFile, nSymb, nDev, nSoc, nPipe int

	var walkFunc = func(path string, info os.FileInfo, err error) error {

		if err != nil {
			fmt.Printf("error %v at %q\n", err, path)
			return err
		}

		switch mode:=info.Mode();{
		case mode.IsDir():
			nDir = nDir+1
		case mode.IsRegular():
			nFile = nFile+1
		case mode&os.ModeSymlink != 0:
			nSymb = nSymb+1
		case mode&os.ModeNamedPipe != 0:
			nPipe = nPipe+1
		case mode&os.ModeDevice != 0:
			nDev = nDev +1
		case mode&os.ModeSocket != 0:
			nSoc = nSoc+1
		}
		return nil
	}
	err1 := filepath.Walk(dir, walkFunc)

	if err1 != nil {
		fmt.Printf("error %v at %q\n",err1,dir)
	}

	fmt.Printf("+----------------------+-----------+\n")
	fmt.Printf("| Path                 | %-10s|\n", dir)
	fmt.Printf("+----------------------+-----------+\n")
	fmt.Printf("| Directories          | %-10d|\n",nDir)
	fmt.Printf("| Symbolic Links       | %-10d|\n",nSymb)
	fmt.Printf("| Devices              | %-10d|\n",nDev)
	fmt.Printf("| Sockets              | %-10d|\n",nSoc)
	fmt.Printf("| Named Pipes          | %-10d|\n",nPipe)
	fmt.Printf("| Other files          | %-10d|\n",nFile)
	fmt.Printf("+----------------------+-----------+\n")

	return nil
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}
