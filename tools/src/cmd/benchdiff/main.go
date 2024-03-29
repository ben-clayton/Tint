// Copyright 2022 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// benchdiff is a tool that compares two Google benchmark results and displays
// sorted performance differences.
package main

import (
	"errors"
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"time"

	"dawn.googlesource.com/tint/tools/src/bench"
)

var (
	minDiff    = flag.Duration("min-diff", time.Microsecond*10, "Filter away time diffs less than this duration")
	minRelDiff = flag.Float64("min-rel-diff", 0.01, "Filter away absolute relative diffs between [1, 1+x]")
)

func main() {
	flag.ErrHelp = errors.New("benchdiff is a tool to compare two benchmark results")
	flag.Parse()
	flag.Usage = func() {
		fmt.Fprintln(os.Stderr, "benchdiff <benchmark-a> <benchmark-b>")
		flag.PrintDefaults()
	}

	args := flag.Args()
	if len(args) < 2 {
		flag.Usage()
		os.Exit(1)
	}

	pathA, pathB := args[0], args[1]

	if err := run(pathA, pathB); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(-1)
	}
}

func run(pathA, pathB string) error {
	fileA, err := ioutil.ReadFile(pathA)
	if err != nil {
		return err
	}
	benchA, err := bench.Parse(string(fileA))
	if err != nil {
		return err
	}

	fileB, err := ioutil.ReadFile(pathB)
	if err != nil {
		return err
	}
	benchB, err := bench.Parse(string(fileB))
	if err != nil {
		return err
	}

	cmp := bench.Compare(benchA.Benchmarks, benchB.Benchmarks, *minDiff, *minRelDiff)
	diff := cmp.Format(bench.DiffFormat{
		TestName:        true,
		Delta:           true,
		PercentChangeAB: true,
		TimeA:           true,
		TimeB:           true,
	})

	fmt.Println("A:", pathA, "  B:", pathB)
	fmt.Println()
	fmt.Println(diff)

	return nil
}

func fileName(path string) string {
	_, name := filepath.Split(path)
	return name
}
