package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
)

func pathWalk(root string) []string {
	// Kevin O. Cabrera 
	var files []string
	err := filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
		files = append(files, path)
		return nil
	})
	if err != nil {
		panic(err)
	}

	return files
}

func scanDir(root string) error {
	// Kevin O. Cabrera 
	files := pathWalk(root)
	dirsLen := 0
	permissionDeniedFiles := 0
	symlinks := 0
	otherFiles := 0
	for i, file := range files {
		if i == 0 {
			continue
		}
		_, err := os.Readlink(file)
		if err == nil {
			symlinks++
			continue
		}

		_, err = ioutil.ReadFile(file)
		if err != nil {
			switch err {
			case os.ErrPermission:
				permissionDeniedFiles++
				continue
			}
		}
		file, err := os.Stat(file)
		if err == nil {
			switch mode := file.Mode(); {
			case mode.IsDir():
				dirsLen++
				continue
			}
		}

		otherFiles++
	}

	fmt.Println("Directory Scanner tool")
	fmt.Println("----------------------------")
	fmt.Printf("Path %s\n", root)
	fmt.Println("----------------------------")
	fmt.Printf("Directories %d\n", dirsLen)
	fmt.Println("----------------------------")
	fmt.Printf("permission Denied Files %d\n", permissionDeniedFiles)
	fmt.Println("----------------------------")
	fmt.Printf("Symbolic Links %d\n", symlinks)
	fmt.Println("----------------------------")
	fmt.Printf("Other files %d", otherFiles)

	return nil
}

func main() {
	// Kevin O. Cabrera 
	if len(os.Args) < 2 {
		fmt.Println("Input string is required")
		os.Exit(1)
	}

	input := os.Args[1]
	fmt.Println(scanDir(input))
}
